#ifndef CONTEXTOGESTORES_H_INCLUDED
#define CONTEXTOGESTORES_H_INCLUDED

#include "archivoManager.h"
#include "clsProducto.h"
#include "clsCliente.h"

struct ContextoGestores {
    ArchivoManager<Producto> gestorP;
    ArchivoManager<Cliente> gestorC;

    ContextoGestores() : gestorP("productos.dat"), 
    gestorC("clientes.dat"){}
};

#endif // CONTEXTOGESTORES_H_INCLUDED
