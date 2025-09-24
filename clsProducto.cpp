#include <iostream>
#include "cargarCadena.h"
#include "clsProducto.h"
#include <cstring>
#include "utilidades.h"

using namespace std;
/* CLASE PRODUCTO: La clase producto sirve para agregar stock a la tienda, tiene 6 atributos:
- Id: De tipo autoincrement
- nombre y tipo: Dos valores de tipo char ingresador por usuario
- stock y precio: Valores entero y float.
- fecha: fecha es un objeto de tipo "Fecha", se llama al metodo para cargar la fecha dentro de cargarProducto.

Los objetos producto estan marcados con un id unico, ademas deberian estar asignados al usuario administrador que los añadió a stock,
y asignados al usuario cliente que lo agrego a su carrito.
*/

///CONSTRUCTOR
Producto::Producto(int _id,
                    const char *_nombre,
                    const char *_tipo,
                     int _stock,
                     float _precio,
                     Fecha _fecha) {
    id = _id;
    strcpy(nombre, _nombre);
    strcpy(tipo, _tipo);
    stock = _stock;
    precio = _precio;
    ingresoProducto = _fecha;
}
//usar fseek, usar la funcion contarRegistro y a partir de ese valor le sumo 1 al id
///SETTERS
void Producto::setID(int _id){
    id = _id;
}

void Producto::setNombre(char *_nombre){
    strcpy(nombre, _nombre);
    toUpperCase(nombre);
}

void Producto::setTipo(char *_tipo){
    strcpy(tipo, _tipo);
    toUpperCase(tipo);
}

void Producto::setStock(int _stock){
    stock = _stock;
}

void Producto::setPrecio(float _precio){
    precio = _precio;
}

///GETTERS
int Producto::getID() const {
    return id;
}

const char *Producto::getNombre() const {
    return nombre;
}

const char *Producto::getTipo() const {
    return tipo;
}

int Producto::getStock() const {
    return stock;
}

float Producto::getPrecio() const {
    return precio;
}

Fecha Producto::getFecha() const {
    return ingresoProducto;
}


///SETEAR IDENTIFICADOR, me quede aca creando esto
void Producto::setearIdentificador(int _id){ // es un void porque no devuelve nada, solo setea el id, sino da error/warning
    cout << "setear identificador" << endl;
    _id += 1;
    id = _id;
}


