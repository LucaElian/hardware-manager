#include <iostream>
using namespace std;

#include "clsProducto.h"
#include <cstring>
#include "utilidades.h"

/* CLASE PRODUCTO: La clase producto sirve para agregar stock a la tienda, tiene 6 atributos:
- Id: De tipo autoincrement
- nombre y tipo: Dos valores de tipo char ingresador por usuario
- stock y precio: Valores entero y float.
- fecha: fecha es un objeto de tipo "Fecha", se llama al metodo para cargar la fecha dentro de cargarProducto.

Los objetos producto estan marcados con un id unico, ademas deberian estar asignados al usuario administrador que los a�adi� a stock,
y asignados al usuario cliente que lo agrego a su carrito.
*/

///CONSTRUCTOR
Producto::Producto(unsigned int _idProducto,
                    const char *_nombre,
                    const char *_tipo,
                    int _stock,
                    float _precio,
                    bool _estado,
                    Fecha _fecha) {
    idProducto = _idProducto;
    strcpy(nombre, _nombre);
    strcpy(tipo, _tipo);
    stock = _stock;
    precio = _precio;
    estado = _estado;
    ingresoProducto = _fecha;
}
//usar fseek, usar la funcion contarRegistro y a partir de ese valor le sumo 1 al id
///SETTERS
void Producto::setID(unsigned int _idProducto){
    idProducto = _idProducto;
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

void Producto::setEstado(bool _estado){
    estado = _estado;
}

///GETTERS
unsigned int Producto::getID() const {
    return idProducto;
}

const char *Producto::getNombre() const
{
    return nombre;
}

const char *Producto::getTipo() const
{
    return tipo;
}

int Producto::getStock() const
{
    return stock;
}

float Producto::getPrecio() const {
    return precio;
}

bool Producto::getEstado() const {
    return estado;
}

Fecha Producto::getFecha() const {
    return ingresoProducto;
}

///METODO CARGAR
void Producto::CargarP(){
    cout << "Ingrese el nombre del producto: ";
    cargarCadena(nombre,29);
    cout << "Ingrese el tipo del producto: ";
    cargarCadena(tipo,29);
    cout << "Ingrese el stock disponible: ";
    cin >> stock;
    cout << "Ingrese el precio: ";
    cin >> precio;
    estado = true;
    ingresoProducto.CargarF();
}

///METODO MOSTRAR
void Producto::MostrarP() {
    cout << "----------------PRODUCTO " << idProducto << "----------------------"<<endl;
    cout << "Nombre: " << nombre << endl;
    cout << "Tipo: " << tipo << endl;
    //cout << "ID: " << id << endl;
    cout << "Stock: " << stock << endl;
    cout << "Precio: $" << precio << endl;
    cout << "Estado: " << (estado ? "Activo" : "Inactivo") << endl;
    cout << "Fecha de ingreso: ";
    //Recibo el objeto de tipo fecha de la clase producto "ingresoProducto" y llamo al metodo mostrar de Fecha
    ingresoProducto.MostrarF();
    cout << endl;
}




