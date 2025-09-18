#include <iostream>
#include <cstring>

#include "clsProducto.h"
#include "utilidades.h"

using namespace std;

Producto::Producto(int _id, const char _nombre[20], const char _tipo[20], int _stock, float _precio, Fecha _fecha){
    id = _id;
    strcpy(nombre, _nombre);
    toUpperCase(nombre);
    strcpy(tipo, _tipo);
    toUpperCase(tipo);
    stock = _stock;
    precio = _precio;
    ingreso = _fecha;
}


void Producto::cargar(){
    cout << "INGRESE EL ID: "; cin >> id;
    cout << "INGRESE EL NOMBRE DEL PRODUCTO: "; cin >> nombre;
    toUpperCase(nombre);
    cout << "INGRESE EL TIPO DE PRODUCTO [COMPONENTE - PERIFERICO]: "; cin >> tipo;
    toUpperCase(tipo);
    cout << "INGRESE STOCK: "; cin >> stock;
    cout << "INGRESE PRECIO: "; cin >> precio;
    ingreso.cargarFechaProducto();
}

void Producto::mostrar() {
    cout << "----------------PRODUCTO----------------------\n" <<
            "ID: " << id <<
            "\nNOMBRE: " << nombre <<
            "\nTIPO: " << tipo <<
            "\nSTOCK: " << stock <<
            "\nPRECIO: $" << precio <<
            "\nFECHA DE INGRESO: "; ingreso.mostrarFechaProducto();
    cout << "\n----------------------------------------------\n";
}

