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

    // M�todos de gestorArchivos
    bool escribirProductoTEXTO(const Producto& producto);
    bool escribirProductoBINARIO(const Producto& producto);
    bool leerProductos();
    bool actualizarStock(int idProducto, int nuevoStock);
    int obtenerStock(int idProducto);
};

#endif // GESTORARCHIVOS_H
