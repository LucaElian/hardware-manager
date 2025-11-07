#ifndef CONTEXTOGESTORES_H_INCLUDED
#define CONTEXTOGESTORES_H_INCLUDED

#include "archivoManager.h"
#include "clsProducto.h"
#include "clsCliente.h"
#include "clsVendedor.h"
#include "gestorVenta.h"
#include "constantes.h"

class ContextoGestores {
public:
    ArchivoManager<Producto> gestorP;
    ArchivoManager<Cliente> gestorC;
    ArchivoManager<Vendedor> gestorV;
    GestorVenta gestorVenta;

    ContextoGestores() : gestorP(ARCHIVO_PRODUCTOS),
                        gestorC(ARCHIVO_CLIENTES),
                        gestorV(ARCHIVO_VENDEDORES) {}
};

#endif // CONTEXTOGESTORES_H_INCLUDED