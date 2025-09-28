#include <iostream>
using namespace std;

#include "clsUsuario.h"

///CPP == Implementacion del constructor
Usuario::Usuario(int _id,
                 const char *_user,
                 const char *_pass,
                 const char *_rol,
                 Fecha _fecha){ //recibe los atributos
    id = _id;
    strcpy(user, _user);
    strcpy(pass, _pass);
    strcpy(rol, _rol);
    ingresoUsuario = _fecha;
}

void Usuario::CargarU(){
    cout << "soy cargar User" << endl;
}

void Usuario::MostrarU(){
    cout << "-------------------- USUARIO " << id << " ----------------------"<< endl;
    cout << "User: " << user << endl;
    cout << "Pass: " << pass << endl;
    cout << "Rol: " << rol << endl;
    cout << "Fecha de ingreso: ";
    //ingresoUsuario.Mostrar(); // Suponiendo que Fecha tiene un m�todo mostrar()
    cout << endl;
}






