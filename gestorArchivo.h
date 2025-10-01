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

    // Metodos de gestorArchivos
    bool escribirProductoTEXTO(const Producto& producto);
    bool escribirProductoBINARIO( Producto& producto);
    bool leerProductos();
    bool eliminarUltimoP();
    bool eliminarProductoID();
    int cantidadRegistros();
};

#endif // GESTORARCHIVOS_H
