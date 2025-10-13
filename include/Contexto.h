#ifndef CONTEXTO_H_INCLUDED
#define CONTEXTO_H_INCLUDED

#include "clsCliente.h"
#include "clsProducto.h"
#include "clsVendedor.h"


struct Contexto {
    Producto producto;
    Cliente cliente;
    Vendedor vendedor;
};



#endif // CONTEXTO_H_INCLUDED
