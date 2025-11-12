#ifndef MENUPRODUCTO_H_INCLUDED
#define MENUPRODUCTO_H_INCLUDED
#include "clsProducto.h"
#include "archivoManager.h"

void menuProducto(Producto, ArchivoManager<Producto>);
void agregarProducto(Producto producto, ArchivoManager<Producto> &gestor);
void eliminarProducto(Producto producto, ArchivoManager<Producto>& gestor);
void modificarProducto(Producto producto, ArchivoManager<Producto>& gestor);

#endif // MENUPRODUCTO_H_INCLUDED
