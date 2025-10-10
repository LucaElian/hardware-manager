#include <iostream>
#include "clsCliente.h"
#include "utilidades.h"

void Cliente::cargar() {
    cout << "Ingrese el nombre del cliente: ";
    cargarCadena(nombre, 49);
    toUpperCase(nombre);
    
    cout << "Ingrese el apellido del cliente: ";
    cargarCadena(apellido, 29);
    toUpperCase(apellido);
    
    cout << "Ingrese el email del cliente: ";
    cargarCadena(email, 49);
    
    fechaIngreso.CargarF();
}

void Cliente::mostrar() {
    cout << "-------------------- CLIENTE " << id << " ----------------------" << endl;
    cout << "Nombre: " << nombre << endl;
    cout << "Apellido: " << apellido << endl;
    cout << "Correo electronico: " << email << endl;
    cout << "Fecha de ingreso: ";
    fechaIngreso.MostrarF();
    cout << endl;
}