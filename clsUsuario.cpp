#include <iostream>
#include "clsUsuario.h"
using namespace std;

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
    ingresa = _fecha;
}


void Usuario::Mostrar(){
    cout << "-------------------- USUARIO " << id << " ----------------------"<< endl;
    cout << "User: " << user << endl;
    cout << "Pass: " << pass << endl;
    cout << "Rol: " << rol << endl;
    cout << "Fecha de ingreso: ";
    ingresa.Mostrar(); // Suponiendo que Fecha tiene un método mostrar()
    cout << endl;
}
