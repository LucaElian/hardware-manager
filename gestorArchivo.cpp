// DEJEN DE COMENTARLO, SOLO COMENTEN LA LINEA 6 EN EL MAIN LA PUTA QUE LO PARIO
#include <iostream>
#include <cstdio>
#include <cstring> // strcpychaval
#include "clsProducto.h"
#include "gestorArchivo.h"
#include "clsFecha.h"

GestorArchivos::GestorArchivos(const char* archivo)
{
    strncpy(nombreArchivo, archivo, sizeof(nombreArchivo)-1);
    nombreArchivo[sizeof(nombreArchivo)-1] = '\0';
}

///Que hace esta funcion?
/*bool GestorArchivos::escribirProductoTEXTO(const Producto& producto)
{
    //abre en modo append+ (lectura y escritura al final)
    FILE* archivo = fopen(nombreArchivo, "a+");
    if (!archivo)
    {
        printf("Error: no se pudo abrir/crear el archivo %s\n", nombreArchivo);
        return false;
    }

    // Velve al inicio para verificar si existe el ID
    rewind(archivo);

    char linea[256];
    int id;
    // Revisa si ya existe el producto
    while (fgets(linea, sizeof(linea), archivo) != NULL)
    {
        if (sscanf(linea, "%d", &id) == 1)
        {
            if (id == producto.getID())
            {
                printf("Erroreishon: producto con ID %d ya existe\n", id);
                fclose(archivo);
                return false;
            }
        }
    }

    //escribe al final del archivo
    fprintf(
        archivo, "%d,%d,%.2f\n",
        producto.getID(),
        producto.getNombre(),
        producto.getTipo(),
        producto.getStock(),
        producto.getPrecio(),
    );

    fclose(archivo);
    return true;
}
*/

bool GestorArchivos::escribirProductoBINARIO(const Producto& producto)
{
//con fopen lo abro, usando el modo read
    FILE* archivo = fopen(nombreArchivo, "r+b");

    if (!archivo) //si el archivo no existe, con write creo otro
    {
        archivo = fopen(nombreArchivo, "wb");
        if (!archivo) return false;
    }

    //declaro los datos del producto
    int id, stock;
    float precio;
    char nombre[50];
    char tipo[20];

    while (fread(&id, sizeof(int), 1, archivo) == 1) //mientras el archivo este abierto
    {
        //Este while lee todos los productos del archivo
        fread(&nombre, sizeof(char), 50, archivo);
        fread(&tipo, sizeof(char), 20, archivo);
        fread(&stock, sizeof(int), 1, archivo); //el "1" indica que leo un elemento de este dato
        fread(&precio, sizeof(float), 1, archivo);

        if (id == producto.getID())
        {
            printf("Error: producto con ID %d ya existe\n", id);
            fclose(archivo);
            return false;
        }
    }

    //me hace escribir en el final del archivo
    fseek(archivo, 0, SEEK_END);

    //recibimos los atributos nuevos que definimos en el objeto con sus metodos get
    int newId = producto.getID();
    const char *newNombre = producto.getNombre();
    const char *newTipo = producto.getTipo();
    int newStock = producto.getStock();
    float newPrecio = producto.getPrecio();


    //y esos atributos nuevos los escribimos con fwrite en el archivo
    fwrite(&newId, sizeof(int), 1, archivo);
    fwrite(&newNombre, sizeof(char), 50, archivo);
    fwrite(&newTipo, sizeof(char), 20, archivo);
    fwrite(&newStock, sizeof(int), 1, archivo);
    fwrite(&newPrecio, sizeof(float), 1, archivo);


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

    printf("contenido de %s\n", nombreArchivo);

    int numeroProducto = 1;
    int id, stock;
    float precio;
    char nombre[50];
    char tipo[20];

    // Lee los 3 campos por producto. fread devuelve 1 si leyo 1 elemento.
    while (
        //ahora si leem el stock y precio (si falla tira archivo corrupto/parcial)
        fread(&id, sizeof(int), 1, archivo) == 1 &&
        fread(&stock, sizeof(int), 1, archivo) == 1 &&
        fread(&precio, sizeof(float), 1, archivo) == 1 &&
        fread(&nombre, sizeof(char), 50, archivo) == 50 &&
        fread(&tipo, sizeof(char), 20, archivo) == 20
    )
    {
        printf("Error: archivo corrupto o fallido\n");
        break;
    }

    printf("Producto %d:  Nombre=%s, Tipo=%s, ID=%d, Stock=%d, Precio=%.2f\n",
           numeroProducto, nombre, tipo, id, stock, precio);
    numeroProducto++;

    fclose(archivo);
    return true;
}
