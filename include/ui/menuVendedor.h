#ifndef MENUVENDEDOR_H_INCLUDED
#define MENUVENDEDOR_H_INCLUDED

#include "clsVendedor.h"
#include "archivoManager.h"

void menuVendedor(Vendedor, ArchivoManager<Vendedor>);
void agregarVendedor(Vendedor vendedor, ArchivoManager<Vendedor> &gestor);
void eliminarVendedor(Vendedor vendedor, ArchivoManager<Vendedor> &gestor);

#endif // MENUVENDEDOR_H_INCLUDED
