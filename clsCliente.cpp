#include <iostream>
#include "clsCliente.h"
#include "utilidades.h"

///CPP == Implementacion del constructor
Cliente::Cliente(int _idCliente,
                 const char *_nombre,
                 const char *_apellido,
                 const char *_email,
                 Fecha _fecha)  //recibe los atributos
{
    idCliente = _idCliente;
    strcpy(nombre, _nombre);
    strcpy(apellido, _apellido);
    strcpy(email, _email);
    ingresoC = _fecha;
}

///SETTERS
void Cliente::setID(int _idCliente)
{
    idCliente = _idCliente;
}

void Cliente::setNombre(char *_nombre)
{
    strcpy(nombre, _nombre);
    toUpperCase(nombre);
}

void Cliente::setApellido(char *_apellido)
{
    strcpy(apellido, _apellido);
    toUpperCase(apellido);
}

void Cliente::setEmail(char *_email)
{
    strcpy(email, _email);
}

/// =========== GETTERS ============
int Cliente::getID() const
{
    return idCliente;
}

const char *Cliente::getNombre() const
{
    return nombre;
}

const char *Cliente::getApellido() const
{
    return apellido;
}

const char *Cliente::getEmail() const
{
    return email;
}

/// ================ METODO CARGAR =============
///METODO CARGAR
void Cliente::cargar(){
    cout << "Ingrese el nombre del cliente: ";
    cargarCadena(nombre,49);
    cout << "Ingrese el apellido del cliente: ";
    cargarCadena(apellido,29);
    cout << "Ingrese el email del cliente: ";
    cargarCadena(email,29);
    ingresoC.CargarF();
}

void Cliente::mostrar()
{
    cout << "-------------------- CLIENTE " << idCliente << " ----------------------"<< endl;
    cout << "Nombre: " << nombre << endl;
    cout << "Apellido: " << apellido << endl;
    cout << "Correo electronico: " << email << endl;
    cout << "Fecha de ingreso: ";
    //ingresoCliente.Mostrar(); // Suponiendo que Fecha tiene un m�todo mostrar()
    cout << endl;
}






