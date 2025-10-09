#include <cstdio>
#include <cstring>
#include <iostream>
#include "archivoManager.h"
#include "clsProducto.h"
#include "clsCliente.h"

#include "utilidades.h"

using namespace std;

ArchivoManager::ArchivoManager(const char* archivo, char tipoObj, size_t size)
{
    strncpy(nombreArchivo, archivo, sizeof(nombreArchivo)-1);
    nombreArchivo[sizeof(nombreArchivo)-1] = '\0';

    if (toupper(tipoObj) != 'P' && toupper(tipoObj) != 'C') {
        cerr << "ERROR: TIPO DE OBJETO DESCONOCIDO." << endl;
        nombreArchivo[0] = '\0'; // Marca el nombre del archivo como inválido
    }
    this->tipoObj = toupper(tipoObj);
    this->size = size;
}

bool ArchivoManager::escribir(void* objeto)
{
    FILE* archivo = fopen(nombreArchivo, "ab");
    if (!archivo)
    {
        cerr << "Error: fallo al escribir el objeto" << endl;
        return false;
    }

    size_t element = fwrite(objeto, size, 1, archivo);
    fclose(archivo);

    if (element != 1)
    {
        cerr << "Error: fallo al escribir el objeto" << endl;
        return false;
    }
    return true;
}

bool ArchivoManager::leer() {
    FILE* archivo = fopen(nombreArchivo, "rb");

    if (!archivo)
    {
        cerr << "ERROR: NO SE PUDO LEER EL ARCHIVO OSTIAS%s\n" << nombreArchivo << endl;
        return false;
    }

    cout << "CONTENIDO DE %s\n" << nombreArchivo << endl;

    if (tipoObj == 'P') {
        Producto producto;
        bool activos = false;
        while (fread(&producto, size, 1, archivo) == 1)   //me falta ver que hace exactamente esta linea y pongo un mejor comentario
        {
            if (producto.getEstado() == true) // saltea productos eliminados
            {
                producto.MostrarP();
                cout << "---------------------\n";
                activos = true;
            }
        }
        if(!activos) cout << "NO SE ENCONTRARON PRODUCTOS ACTIVOS." << endl;
    }
    else if (tipoObj == 'C') {
        Cliente cliente;
        bool activos = false;
        while (fread(&cliente, size, 1, archivo) == 1)   //me falta ver que hace exactamente esta linea y pongo un mejor comentario
        {
            // if (cliente.getEstado() == true) // saltea clientes eliminados
            // {
            //     cliente.mostrar();
            //     cout << "---------------------\n";
            //     activos = true;
            // }
            continue;
        }
        if(!activos) cout << "NO SE ENCONTRARON CLIENTES ACTIVOS." << endl;
    }
    else {
        cerr << "ERROR: TIPO DE OBJETO DESCONOCIDO." << endl;
        fclose(archivo);
        return false;
    }
    fclose(archivo);
    return true;
}

bool ArchivoManager::eliminarPorID(int id) {
    // Abre el archivo en modo lectura/escritura binario
    FILE* archivo = fopen(nombreArchivo, "r+b");
    if (!archivo)
    {
        cerr << "Error: no se pudo abrir el archivo " << nombreArchivo << endl;
        return false;
    }

    // Buscar producto por su ID
    if (tipoObj != 'P') {
        Producto producto;  

        while (fread(&producto, sizeof(Producto), 1, archivo) == 1)
        {
            if (producto.getID() == id)
            {
                // Mover puntero al inicio del registro leído
                long posActual = ftell(archivo);        // posicion actual en el archivo
                long posRegistro = posActual - sizeof(Producto);
                fseek(archivo, posRegistro, SEEK_SET);  // mover puntero al inicio del registro

                // Marcar como eliminado
                producto.setID(-1);
                fwrite(&producto, sizeof(Producto), 1, archivo);

                fclose(archivo);
                return true; // Producto eliminado con éxito
            }
        }
    }
    else if (tipoObj != 'C') {
        Cliente cliente;  

        while (fread(&cliente, sizeof(Cliente), 1, archivo) == 1)
        {
            if (cliente.getID() == id)
            {
                // Mover puntero al inicio del registro leído
                long posActual = ftell(archivo);        // posicion actual en el archivo
                long posRegistro = posActual - sizeof(Cliente);
                fseek(archivo, posRegistro, SEEK_SET);  // mover puntero al inicio del registro

                // Marcar como eliminado
                cliente.setID(-1);
                fwrite(&cliente, sizeof(Cliente), 1, archivo);

                fclose(archivo);
                return true; // Cliente eliminado con éxito
            }
        }
    }
    else {
        cerr << "ERROR: TIPO DE OBJETO DESCONOCIDO." << endl;
        fclose(archivo);
        return false;
    }

    // si no se encontró
    cerr << "Error: producto con ID " << id << " no encontrado." << endl;
    fclose(archivo);
    return false;
}

int ArchivoManager::cantidadRegistros() {
    FILE* archivo = fopen(nombreArchivo, "rb");

    if (!archivo) return 0;

    if (tipoObj == 'P'){
        Producto producto;

        fseek(archivo, 0, SEEK_END);
        long can = ftell(archivo);
        fclose(archivo);

        if (sizeof(Producto) == 0) return 0;
        return can / sizeof(Producto);    // Cantidad de registros
    }
    else if (tipoObj == 'C'){
        Cliente cliente;

        fseek(archivo, 0, SEEK_END);
        long can = ftell(archivo);
        fclose(archivo);

        if (sizeof(Cliente) == 0) return 0;
        return can / sizeof(Cliente);    // Cantidad de registros
    }
    else {
        cerr << "ERROR: TIPO DE OBJETO DESCONOCIDO." << endl;
        fclose(archivo);
        return 0;
    }    
}