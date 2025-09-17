#include <iostream>

#include "clsProducto.h"

using namespace std;

Producto::Producto(const char *_nombre, const char *_tipo, int _id, int _stock, float _precio, Fecha _fecha){
    strcpy(nombre, _nombre);
    strcpy(tipo, _tipo);
    id = _id;
    stock = _stock;
    precio = _precio;
    ingreso = _fecha;
}
