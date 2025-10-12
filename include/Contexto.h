#ifndef CONTEXTO_H_INCLUDED
#define CONTEXTO_H_INCLUDED

#include "clsCliente.h"
#include "clsProducto.h"


struct Contexto {
    Producto producto;
    Cliente cliente;
    //GestorArchivos gestor;
};



#endif // CONTEXTO_H_INCLUDED
