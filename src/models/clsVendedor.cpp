#include <iostream>
#include "clsVendedor.h"
#include "utilidades.h"
#include "ContextoGestores.h"
void Vendedor::cargar() {
    cout << "Ingrese el nombre del vendedor: ";
    cargarCadena(nombre, 29);
    toUpperCase(nombre);

    cout << "Ingrese el telefono del vendedor: ";
    cargarCadena(telefonoVendedor, 14);

    cout << "Ingrese el dni del vendedor: ";
    cargarCadena(dni, 9);

    //fechaIngreso.CargarF();

    ContextoGestores contexto;
    int cantidad = contexto.gestorV.cantidadRegistros();
    setLegajo(cantidad +1);
    setID(cantidad +1); // Asignar ID igual al legajo pq trabajamos con id a nivel codigo, no legajos
}

void Vendedor::mostrar() const{
    cout << "----------------VENDEDOR NUMERO " << legajo << "----------------------" << endl;
    cout << "Nombre: " << nombre << endl;
    cout << "Numero telefonico: " << telefonoVendedor << endl;
    cout << "DNI: " << dni << endl;
    cout << "Estado: " << (estado ? "Activo" : "Inactivo") << endl;
    cout << "ID: " << id << endl;
    cout << endl;
}
