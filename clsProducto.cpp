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

void Producto::Cargar(){
    cout << "Ingrese el nombre del producto " << endl;
    cin >> nombre[20];


}

void Producto::Mostrar() {
    cout << "----------------PRODUCTO " << id << "----------------------"<<endl;
    cout << "Nombre:lmñmñlmñlmñlm " << nombre << endl;
    cout << "Tipo: " << tipo << endl;
    cout << "ID: " << id << endl;
    cout << "Stock: " << stock << endl;
    cout << "Precio: $" << precio << endl;
    cout << "Fecha de ingreso: ";
    ingreso.Mostrar(); // Suponiendo que Fecha tiene un método mostrar()
    cout << endl;
}

