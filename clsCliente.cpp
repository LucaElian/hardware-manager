#include <iostream>
using namespace std;

#include "clsCliente.h"

///CPP == Implementacion del constructor
Cliente::Cliente(int _idCliente,
                 const char *_nombre,
                 const char *_apellido,
                 int _dni,
                 const char *_email,
                Fecha _fecha){ //recibe los atributos
    idCliente = _idCliente;
    strcpy(nombre, _nombre);
    strcpy(apellido, _apellido);
    dni = _dni;
    strcpy(email, _email);
    ingresoC = _fecha;
}

void Cliente::CargarC(){
    cout << "soy cargar cliente" << endl;
}

void Cliente::MostrarC(){
    cout << "-------------------- CLIENTE " << idCliente << " ----------------------"<< endl;
    cout << "Nombre: " << nombre << endl;
    cout << "Apellido: " << apellido << endl;
    cout << "dni: " << dni << endl;
    cout << "Correo electronico: " << email << endl;
    cout << "Fecha de ingreso: ";
    //ingresoCliente.Mostrar(); // Suponiendo que Fecha tiene un m�todo mostrar()
    cout << endl;
}






