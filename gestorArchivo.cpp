// DEJEN DE COMENTARLO, SOLO COMENTEN LA LINEA 6 EN EL MAIN LA PUTA QUE LO PARIO
#include <iostream>
#include <cstdio>
#include <cstring>
#include "clsProducto.h"
#include "menuProducto.h"
#include "gestorArchivo.h"

///PRIMER METODO: guardo el nombre del archivo y lo paso a string
GestorArchivos::GestorArchivos(const char* archivo)
{
    strncpy(nombreArchivo, archivo, sizeof(nombreArchivo)-1);
    nombreArchivo[sizeof(nombreArchivo)-1] = '\0';
}

///Metodo para escribir un producto en el archivo
bool GestorArchivos::escribirProducto(const Producto& producto)
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

/*bool actualizarStock(int idProducto, int nuevoStock)
{
    FILE* archivo = fopen(nombreArchivo, "r+b");
    if (!archivo)
    {
        printf("Error: no se pudo abrir el archivo %s\n", nombreArchivo);
        return false;
    }

    int id, stock;
    float precio;
    bool encontrado = false;

    while (fread(&id, sizeof(int), 1, archivo) == 1)
    {
        long posicionStock = ftell(archivo); // apunta al inicio del campo stock

        // lee el stock y precio para avanzar el cursor
        if (fread(&stock, sizeof(int), 1, archivo) != 1 ||
                fread(&precio, sizeof(float), 1, archivo) != 1)
        {
            printf("Error: archivo corrupto o truncado\n");
            break;
        }

        if (id == idProducto)
        {
            // vuelce a la posición del stock y sobrescribe
            if (fseek(archivo, posicionStock, SEEK_SET) != 0)
            {
                printf("Error: fseek falló\n");
                break;
            }
            if (fwrite(&nuevoStock, sizeof(int), 1, archivo) != 1)
            {
                printf("Error: no se pudo escribir el nuevo stock\n");
                break;
            }
            encontrado = true;
            break;
        }
    }

    fclose(archivo);

    if (encontrado)
    {
        printf("Stock actualizado para ID %d: %d\n", idProducto, nuevoStock);
        return true;
    }
    else
    {
        printf("Producto con ID %d no encontrado\n", idProducto);
        return false;
    }
}

int obtenerStock(int idProducto)
{
    FILE* archivo = fopen(nombreArchivo, "rb");
    if (!archivo) return -1;

    int id, stock;
    float precio;

    while (fread(&id, sizeof(int), 1, archivo) == 1)
    {
        if (fread(&stock, sizeof(int), 1, archivo) != 1 ||
                fread(&precio, sizeof(float), 1, archivo) != 1)
        {
            break;
        }

        if (id == idProducto)
        {
            fclose(archivo);
            return stock;
        }
    }

    fclose(archivo);
    return -1;
}

*/


