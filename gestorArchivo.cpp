#include <iostream>
using namespace std;
#include <cstdio>
#include <cstring>
#include "clsProducto.h"
#include "gestorArchivo.h"
#include "clsFecha.h"

GestorArchivos::GestorArchivos(const char* archivo)
{
    strncpy(nombreArchivo, archivo, sizeof(nombreArchivo)-1);
    nombreArchivo[sizeof(nombreArchivo)-1] = '\0';
}

///Escribir productos en el archivo pasandole el objeto
bool GestorArchivos::escribirProductoBINARIO(Producto& producto)
{
    //con fopen lo abro, usando el modo append*
    FILE* archivo = fopen(nombreArchivo, "ab"); //ab es append binary, para agregar al final en binario

    if (!archivo) //si el archivo no existe, error
    {
        cerr << "Error: fallo al escribir el producto" << endl;
        return false;
    }

    int nuevoID = cantidadRegistros() + 1;
    producto.setID(nuevoID);

    //directamente uso fwrite porque todos los valores de producto son pasables sin problema con esta funcion, le paso el objeto directamente mas facil!!!
    // size_t es para que devuelva un valor sin signo, que es lo que devuelve fwrite
    size_t element = fwrite(&producto, sizeof(Producto), 1, archivo);
    fclose(archivo);

    if (element != 1) // si no se escribio bien
    {
        cerr << "Error: fallo al escribir el producto" << endl;
        return false;
    }
    return true;
}

bool GestorArchivos::leerProductos()
{
    FILE* archivo = fopen(nombreArchivo, "rb");
    if (!archivo)
    {
        std::cerr << "Error: no se pudo leer el archivo ostias%s\n" << nombreArchivo << std::endl;
        return false;
    }

    printf("Contenido de %s\n", nombreArchivo);

    Producto producto;  // creo aca un producto para que no lo reciba la funcion al pedo, solo lo usa para mostrar
    while (fread(&producto, sizeof(Producto), 1, archivo) == 1)   //me falta ver que hace exactamente esta linea y pongo un mejor comentario
    {
        if (producto.getID() == -1) continue; // saltea productos eliminados
        {
            producto.MostrarP();
            cout << "---------------------\n";
        }
    }

    fclose(archivo);
    return true;
}

int GestorArchivos::cantidadRegistros()
{
    FILE* archivo = fopen(nombreArchivo, "rb");
    if (!archivo) return 0;


    int contadorRegistrosValidos = 0;
    Producto producto;

    while (fread(&producto, sizeof(Producto), 1, archivo) == 1)
    {
        // Solo cuenta si el ID no es -1
        if (producto.getID() != -1)
        {
            contadorRegistrosValidos++;
        }
    }

    fseek(archivo, 0, SEEK_END);       // Ir al final
    fclose(archivo);

    return contadorRegistrosValidos;    // Cantidad de registros
}

///Te solicita el id y borras el producto que coincida
bool GestorArchivos::eliminarProductoPorID(int idProducto)
{
    // Abre el archivo en modo lectura/escritura binario
    FILE* archivo = fopen(nombreArchivo, "r+b");
    if (!archivo)
    {
        cerr << "Error: no se pudo abrir el archivo " << nombreArchivo << endl;
        return false;
    }

    Producto producto;

    // Buscar producto por su ID
    while (fread(&producto, sizeof(Producto), 1, archivo) == 1)
    {
        if (producto.getID() == idProducto)
        {
            // Mover puntero al inicio del registro leído
            long posActual = ftell(archivo);        // posicion actual en el archivo
            long posRegistro = posActual - sizeof(Producto);
            fseek(archivo, posRegistro, SEEK_SET);  // mover puntero al inicio del registro

            // Narcar como eliminado
            producto.setID(-1);
            fwrite(&producto, sizeof(Producto), 1, archivo);

            fclose(archivo);
            return true; // Producto eliminado con mexito
        }
    }

    // si no se encontro
    cerr << "Error: producto con ID " << idProducto << " no encontrado." << endl;
    fclose(archivo);
    return false;
}


