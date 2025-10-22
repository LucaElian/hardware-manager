#ifndef CONTEXTO_H_INCLUDED
#define CONTEXTO_H_INCLUDED

#include "clsCliente.h"
#include "clsProducto.h"
#include "clsVendedor.h"
#include "clsVenta.h"

class Contexto {
public:
    Producto producto;
    Cliente cliente;
    Vendedor vendedor;
    Venta venta;
};

#endif // CONTEXTO_H_INCLUDED