#include <iostream>
using namespace std;
#include <cstdio>
#include <cstring>
#include "clsProducto.h"
#include "gestorArchivo.h"
#include "clsFecha.h"

GestorArchivos::GestorArchivos(const char* archivo){
    strncpy(nombreArchivo, archivo, sizeof(nombreArchivo)-1);
    nombreArchivo[sizeof(nombreArchivo)-1] = '\0';
}

///Escribir productos en el archivo pasandole el objeto
bool GestorArchivos::escribirProductoBINARIO(Producto& producto)
{
    //con fopen lo abro, usando el modo append*
    FILE* archivo = fopen(nombreArchivo, "ab"); //ab es append binary, para agregar al final en binario

    if (!archivo){ //si el archivo no existe, error
        cerr << "ERROR: FALLO AL ESCRIBIR EL PRODUCTO." << endl;
        return false;
    }

    int nuevoID = cantidadRegistros() + 1;
    producto.setID(static_cast<unsigned int>(nuevoID));
    producto.setEstado(true);

    //directamente uso fwrite porque todos los valores de producto son pasables sin problema con esta funcion, le paso el objeto directamente mas facil!!!
    // size_t es para que devuelva un valor sin signo, que es lo que devuelve fwrite
    size_t element = fwrite(&producto, sizeof(Producto), 1, archivo);
    fclose(archivo);

    if (element != 1) // si no se escribio bien
    {
        cerr << "ERROR: FALLO AL ESCRIBIR EL PRODUCTO." << endl;
        return false;
    }
    return true;
}

bool GestorArchivos::leerProductos()
{
    FILE* archivo = fopen(nombreArchivo, "rb");
    if (!archivo)
    {
        cerr << "ERROR: NO SE PUDO LEER EL ARCHIVO OSTIAS%s\n" << nombreArchivo << std::endl;
        return false;
    }

    printf("CONTENIDO DE %s\n", nombreArchivo);

    Producto producto;  // creo aca un producto para que no lo reciba la funcion al pedo, solo lo usa para mostrar
    bool activos = false;
    while (fread(&producto, sizeof(Producto), 1, archivo) == 1)   //me falta ver que hace exactamente esta linea y pongo un mejor comentario
    {
        if (producto.getEstado() == true) // saltea productos eliminados
        {
            producto.MostrarP();
            cout << "---------------------\n";
            activos = true;
        }
    }

    fclose(archivo);
    if(!activos) cout << "NO SE ENCONTRARON PRODUCTOS ACTIVOS." << endl;

    return true;
}

int GestorArchivos::cantidadRegistros()
{
    FILE* archivo = fopen(nombreArchivo, "rb");
    if (!archivo) return 0;

    Producto producto;

    fseek(archivo, 0, SEEK_END);
    long can = ftell(archivo);
    fclose(archivo);

    if (sizeof(Producto) == 0) return 0;
    return can / sizeof(Producto);    // Cantidad de registros
}

///Te solicita el id y borras el producto que coincida
bool GestorArchivos::eliminarProductoPorID(int idProducto){
    // Abre el archivo en modo lectura/escritura binario
    FILE* archivo = fopen(nombreArchivo, "r+b");
    if (!archivo){
        cerr << "ERROR: NO SE PUDO ABRIR EL ARCHIVO " << nombreArchivo << endl;
        return false;
    }

    Producto producto;
    int posRegistro = 0;
    // Buscar producto por su ID
    while (fread(&producto, sizeof(Producto), 1, archivo) == 1){
        if (producto.getID() == idProducto){
            fseek(archivo, posRegistro, SEEK_SET);  // mover puntero al inicio del registro

            // Narcar como eliminado
            producto.setEstado(false);
            
            if (fwrite(&producto, sizeof(Producto), 1, archivo) == 1){
                fclose(archivo);
                return true;
            }
            
            else{
                cerr << "ERROR: EL ESTADO DEL PRODUCTO CON ID " << idProducto << " NO SE PUDO ACTUALIZAR" << endl;
                fclose(archivo);
                return false;
            }
        }
        posRegistro = ftell(archivo);
    }

    // si no se encontro
    cerr << "ERROR: PRODUCTO CON ID " << idProducto << " NO ENCONTRADO." << endl;
    fclose(archivo);
    return false;
}


