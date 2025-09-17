#include <iostream>

#include "clsProducto.h"

using namespace std;

Producto::Producto(int _id = 0, const char *_nombre = "vacio", const char *_tipo = " vacio", int _stock = 0, float _precio = 0.0, Fecha _fecha = (00,00,0000)){
    id = _id;
    strcpy(nombre, _nombre);
    strcpy(tipo, _tipo);
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

