// DEJEN DE COMENTARLO, SOLO COMENTEN LA LINEA 6 EN EL MAIN LA PUTA QUE LO PARIO
#include <iostream>

#include <cstdio>
#include <cstring> // strcpychaval
#include "clsProducto.h"
#include "gestorArchivo.h"
#include "clsFecha.h"


//HACER QUE LA FECHA SE ACTUALICE BIEN

GestorArchivos::GestorArchivos(const char* archivo)
{
    strncpy(nombreArchivo, archivo, sizeof(nombreArchivo)-1);
    nombreArchivo[sizeof(nombreArchivo)-1] = '\0';
}

bool GestorArchivos::escribirProductoBINARIO(Producto& producto)
{
    //con fopen lo abro, usando el modo append*
    FILE* archivo = fopen(nombreArchivo, "ab"); //ab es append binary, para agregar al final en binario

    if (!archivo) //si el archivo no existe, error
    {
        std::cerr << "Error: fallo al escribir el producto" << std::endl;
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
        std::cerr << "Error: fallo al escribir el producto" << std::endl;
        return false;
    }
    return true;
}

bool GestorArchivos::leerProductos()
{
    FILE* archivo = fopen(nombreArchivo, "rb");
    if (!archivo)
    {
        printf("Error: no se pudo leer el archivo ostias%s\n", nombreArchivo);
        return false;
    }

    printf("Contenido de %s\n", nombreArchivo);

    Producto producto;  // creo aca un producto para que no lo reciba la funcion al pedo, solo lo usa para mostrar
    while (fread(&producto, sizeof(Producto), 1, archivo) == 1) { //me falta ver que hace exactamente esta linea y pongo un mejor comentario
        producto.MostrarP();
        cout << "---------------------\n";
    }

    fclose(archivo);
    return true;
}

int GestorArchivos::cantidadRegistros() {
    FILE* archivo = fopen(nombreArchivo, "rb");
    if (!archivo) return 0;

    fseek(archivo, 0, SEEK_END);       // Ir al final
    long size = ftell(archivo);        // Tama�o total en bytes
    fclose(archivo);

    return size / sizeof(Producto);    // Cantidad de registros
}
