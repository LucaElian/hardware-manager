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

bool GestorArchivos::escribirProductoBINARIO(const Producto& producto)
{
//con fopen lo abro, usando el modo read
    FILE* archivo = fopen(nombreArchivo, "r+b");

    if (!archivo) //si el archivo no existe, con write creo otro
    {
        archivo = fopen(nombreArchivo, "wb");
        if (!archivo) return false;
    }

    //directamente uso fwrite porque todos los valores de producto son pasables sin problema con esta funcion, le paso el objeto directamente mas facil!!!
    fwrite(&producto, sizeof(Producto),1,archivo);

    fclose(archivo);
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
    long size = ftell(archivo);        // Tamaño total en bytes
    fclose(archivo);

    return size / sizeof(Producto);    // Cantidad de registros
}
