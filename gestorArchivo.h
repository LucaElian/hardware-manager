#ifndef GESTORARCHIVOS_H
#define GESTORARCHIVOS_H

#include <cstdio>
#include <cstring>
#include "clsProducto.h"

class GestorArchivos {
private:
    char nombreArchivo[256];

public:
    // Constructor
    GestorArchivos(const char* archivo);

    setNombreArchivo(char);
    getNombreArchivo(){
    return nombreArchivo[256];
    }

    // Métodos de gestorArchivos
    bool escribirProducto(const Producto& producto);
    bool leerProductos();
    bool actualizarStock(int idProducto, int nuevoStock);
    int obtenerStock(int idProducto);
};

#endif // GESTORARCHIVOS_H
