#ifndef CONTEXTOGESTORES_H_INCLUDED
#define CONTEXTOGESTORES_H_INCLUDED

#include "archivoManager.h"
#include "clsProducto.h"
#include "clsCliente.h"
#include "clsVendedor.h"
#include "gestorVenta.h"

struct ContextoGestores {
    ArchivoManager<Producto> gestorP;
    ArchivoManager<Cliente> gestorC;
    ArchivoManager<Vendedor> gestorV;

    ContextoGestores() : gestorP("productos.dat"),
    gestorC("clientes.dat"), gestorV("vendedores.dat"){}

    GestorVenta gestorVenta;
};

#endif // CONTEXTOGESTORES_H_INCLUDED
