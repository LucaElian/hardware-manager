#include <iostream>
#include "clsProducto.h"
#include "utilidades.h"
#include "ContextoGestores.h"

void Producto::cargar() {
    cout << "Ingrese el nombre del producto: ";
    cargarCadena(nombre, 29);
    toUpperCase(nombre);

    cout << "Ingrese el tipo del producto: ";
    cargarCadena(tipo, 29);
    toUpperCase(tipo);

    cout << "Ingrese el stock disponible: ";
    cin >> stock;

    cout << "Ingrese el precio: ";
    cin >> precio;

    fechaIngreso.CargarF();
    //setEstado(true);

    ContextoGestores contexto;
    int cantidad = contexto.gestorP.cantidadRegistros();
    setID(cantidad + 1);
}

void Producto::mostrar() {
    cout << "----------------PRODUCTO " << id << "----------------------" << endl;
    cout << "Nombre: " << nombre << endl;
    cout << "Tipo: " << tipo << endl;
    cout << "Stock: " << stock << endl;
    cout << "Precio: $" << precio << endl;
    cout << "Estado: " << (estado ? "Activo" : "Inactivo") << endl;
    cout << "Fecha de ingreso: ";
    fechaIngreso.MostrarF();
    cout << endl;
}
