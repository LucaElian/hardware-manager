#ifndef MENUPRODUCTO_H_INCLUDED
#define MENUPRODUCTO_H_INCLUDED
#include "clsProducto.h"
#include "archivoManager.h"

void menuProducto(Producto, ArchivoManager<Producto>);
void agregarProducto(Producto producto, ArchivoManager<Producto> &gestor);
void mostrarProducto(Producto producto);

#endif // MENUPRODUCTO_H_INCLUDED
