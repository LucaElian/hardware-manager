#ifndef CONTEXTOGESTORES_H_INCLUDED
#define CONTEXTOGESTORES_H_INCLUDED

#include "archivoManager.h"
#include "clsProducto.h"
#include "clsCliente.h"

struct ContextoGestores {
    ArchivoManager gestorP;
    ArchivoManager gestorC;

    ContextoGestores() : gestorP("productos.dat", 'p', sizeof(Producto)), 
    gestorC("clientes.dat", 'c', sizeof(Cliente)){}
};

#endif // CONTEXTOGESTORES_H_INCLUDED
