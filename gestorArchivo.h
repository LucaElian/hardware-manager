#ifndef GESTORARCHIVOS_H
#define GESTORARCHIVOS_H

#include <cstdio>
#include <cstring>
#include "clsProducto.h"
#include "clsCliente.h"

class GestorArchivos {
private:
    char nombreArchivo[256];

public:
    // Constructor
    GestorArchivos(const char* archivo);

   bool escribirProducto(Producto& producto);
    bool leerProductos();
    bool eliminarProductoPorID(int idProducto);
    int cantidadRegistrosP();

    // Métodos para CLIENTES
    bool escribirCliente(Cliente& cliente);
    bool leerClientes();
    bool eliminarClientePorID(int idCliente);
    int cantidadRegistrosC();

};

#endif // GESTORARCHIVOS_H
