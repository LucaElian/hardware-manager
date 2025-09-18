#include <iostream>

#include "clsFecha.h"
#include "clsProducto.h"
#include "clsUsuario.h"
#include "menuProducto.h"

using namespace std;

int main(){

    //Objetivo 1: Crear un producto con su fecha
    Producto prod;

    /*prod.CargarP();
    prod.MostrarP();*/

    //Objetivo 2: Crear un usuario con su fecha de login

    int opcion;
    while(true){
        system("cls");
        cout << "----------Bienvenido a compra gaymer-----------" << endl;
        cout << "Ingrese un numero para elegir su opcion:" << endl;
        cout << "0. Salir del programa"<<endl;
        cout << "1. Registrarse" << endl;
        cout << "2. Iniciar sesion " << endl;
        cout << "3. Administrar productos" << endl;
        cout << "Opcion: ";
        cin >> opcion;
        switch(opcion){
            case 0:
                cout << "Hasta la vista baby"<< endl;
                system("pause");
                return 0;
            break;
            case 1:
                cout << "soy la opcion 1"<< endl;
            break;
            case 2:
                cout << "soy la opcion 2"<< endl;
            break;
            case 3:
                cout << "soy la opcion 3"<< endl;
                menuProducto(prod);
            break;
        }
        system("pause");
    }



    return 0;
}
