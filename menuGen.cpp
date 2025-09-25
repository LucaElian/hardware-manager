#include <iostream>
#include "rlutil.h"
#include "menuGen.h"
#include "menuProducto.h"
using namespace std;

/*Porque static?
Porque no necesitamos instanciar un objeto de la clase menuGen para usar sus metodos.
*/
void MenuGen::mostrarMenuPrincipal() {
    const int OPCIONES = 3;
    int opcionSeleccionada = 1;
    bool salir = false;
    const string opciones[OPCIONES] = {
        "Gestionar Productos",
        "Gestionar Usuarios",
        "Salir"
    };

    while(!salir) {
        rlutil::cls();
        rlutil::hidecursor();
        
        // Tirulo
        rlutil::setColor(rlutil::YELLOW);
        rlutil::locate(35,1);
        cout << "===================" << endl;
        rlutil::locate(35,2);
        cout << "GESTION DE HARDWARE" << endl;
        rlutil::locate(35,3);
        cout << "===================" << endl;
        
        // Opciones del menu
        for(int i = 0; i < OPCIONES; i++) {
            rlutil::locate(35, 5+i);
            if(i + 1 == opcionSeleccionada) {
                rlutil::setColor(rlutil::GREEN);
                cout << "> " << opciones[i] << endl;
            } else {
                rlutil::setColor(rlutil::WHITE);
                cout << "  " << opciones[i] << endl;
            }
        }

        // Captura de teclas
        int key = rlutil::getkey();
        
        if(key == rlutil::KEY_UP || key == 'w' || key == 'W') {
            opcionSeleccionada = (opcionSeleccionada > 1) ? opcionSeleccionada - 1 : OPCIONES;
        }
        else if(key == rlutil::KEY_DOWN || key == 's' || key == 'S') {
            opcionSeleccionada = (opcionSeleccionada < OPCIONES) ? opcionSeleccionada + 1 : 1;
        }
        else if(key == rlutil::KEY_ENTER || key == '\n') {
            seleccionarOpcion(opcionSeleccionada);
            if(opcionSeleccionada == OPCIONES) salir = true;
        }
    }
    rlutil::showcursor();
    rlutil::setColor(rlutil::WHITE);
}

void MenuGen::seleccionarOpcion(int opcion)
{
    switch(opcion)
    {
    case 1:
        // Llamar a la funcion para gestionar productos
        cout << "gestionar productos" << endl;
        //menuProducto(producto);
        system("pause");
        break;
    case 2:
        // Llamar a la funcion para gestionar usuarios
        cout << "gestionar usuarios" << endl;
        system("pause");
        break;
    case 3:
        cout << "Saliendo del programa..." << std::endl;
        //falta desarrollar
        system("pause");
        break;
    default:
        std::cout << "Opcion invalida. Intente de nuevo." << std::endl;
        system("pause");
        break;
    }
}

