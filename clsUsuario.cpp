#include <iostream>

#include "clsUsuario.h"
#include "utilidades.h"

using namespace std;

Usuario::Usuario(int _id, const char *_nombre, const char *_apellido, const char *_pass, const char *_rol, Fecha _fecha){
    id = _id;
    strcpy(nombre, _nombre);
    toUpperCase(nombre);
    strcpy(apellido, _apellido);
    toUpperCase(apellido);
    strcpy(pass, _pass);
    strcpy(rol, _rol);
    toUpperCase(rol);
    ingresa = _fecha;
}

void Usuario::cargar(){
    cout << "INGRESE EL ID: "; cin >> id;
    cout << "INGRESE EL NOMBRE DEL USUARIO: "; cin >> nombre;
    toUpperCase(nombre);
    cout << "INGRESE EL APELLIDO DEL USUARIO: "; cin >> apellido;
    toUpperCase(apellido);
    cout << "INGRESE LA CONTRASENIA DEL USUARIO: "; cin >> pass;
    cout << "INGRESE ROL DEL USUARIO [ADMIN - USER]: "; cin >> rol;
    toUpperCase(rol) ;
    ingresa.cargarFechaProducto();
}


void Usuario::mostrar(){
    cout << "--------------------USUARIO----------------------\n" <<
            "ID: " << id <<
            "\nNOMBRE: " << nombre <<
            "\nAPELLIDO: " << apellido <<
            "\nCONTRASENIA: " << pass <<
            "\nROL: " << rol <<
            "\nFECHA DE INGRESO: "; ingresa.mostrarFechaProducto();
    cout << "\n-------------------------------------------------\n";
}
