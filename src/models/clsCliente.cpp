#include <iostream>
#include "clsCliente.h"
#include "utilidades.h"
#include "ContextoGestores.h"

void Cliente::cargar() {
    cout << "Ingrese el nombre del cliente: ";
    cargarCadena(nombre, 49);
    toUpperCase(nombre);

    cout << "Ingrese el telefono del cliente: ";
    cargarCadena(telefono, 14);

    ContextoGestores contexto;
    int cantidad = contexto.gestorC.cantidadRegistros();
    setID(cantidad + 1);
}

void Cliente::mostrar() const {
    cout << "-------------------- CLIENTE " << id << " ----------------------" << endl;
    cout << "Nombre: " << nombre << endl;
    cout << "Telefono: " << telefono << endl;
    cout << endl;
}
