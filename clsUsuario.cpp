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
    ingresaFecha = _fecha;
}

void Usuario::cargarId(){
    cout << "INGRESE EL ID: "; cin >> id;
}

void Usuario::cargarNombre(){
    cout << "INGRESE EL NOMBRE DEL USUARIO: "; cin >> nombre;
    toUpperCase(nombre);
}

void Usuario::cargarApellido(){
    cout << "INGRESE EL APELLIDO DEL USUARIO: "; cin >> apellido;
    toUpperCase(apellido);
}

void Usuario::cargarPass(){
    cout << "INGRESE LA CONTRASENIA DEL USUARIO: "; cin >> pass;
}

void Usuario::cargarRol(){
    cout << "INGRESE ROL DEL USUARIO [ADMIN - USER]: "; cin >> rol;
    toUpperCase(rol);
    while (strcmp(rol, "ADMIN") != 0 && strcmp(rol, "USER") != 0) {
        cout << "ROL INVALIDO. INGRESE ROL DEL USUARIO VALIDO [ADMIN - USER]:\n"; cin >> rol;
        toUpperCase(rol);
    }   
    
}

void Usuario::cargarDatos(){
    //mas ordenado
    Usuario::cargarId();
    Usuario::cargarNombre();
    Usuario::cargarApellido();
    Usuario::cargarPass();
    Usuario::cargarRol();
    ingresaFecha.cargarFechaProducto();
}


void Usuario::mostrar(){
    cout << "--------------------USUARIO----------------------\n" <<
            "ID: " << id <<
            "\nNOMBRE: " << nombre <<
            "\nAPELLIDO: " << apellido <<
            "\nCONTRASENIA: " << pass <<
            "\nROL: " << rol <<
            "\nFECHA DE INGRESO: "; ingresaFecha.mostrarFechaProducto();
    cout << "\n-------------------------------------------------\n";
}
