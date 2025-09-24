#include <iostream>
#include "rlutil.h"
#include "menuGen.h"
#include "menuProducto.h"
using namespace std;

/*Porque static?
Porque no necesitamos instanciar un objeto de la clase menuGen para usar sus metodos.
*/
void MenuGen::mostrarMenuPrincipal()
{
    int opcion;
    Producto producto;

    while(true){
    rlutil::cls();
    rlutil::setColor(rlutil::YELLOW);
    //rlutil::locate(35,1);
    cout << "===================" << std::endl;
    //rlutil::locate(35,2);
    cout << "GESTION DE HARDWARE" << std::endl;
    //rlutil::locate(35,3);
    cout << "===================" << std::endl;
    rlutil::setColor(rlutil::WHITE);
    cout << "1. Gestionar Productos" << std::endl;
    cout << "2. Gestionar Usuarios" << std::endl;
    cout << "3. Salir" << std::endl;
    cout << "Seleccione una opcion: ";
    cin >> opcion;
    MenuGen::seleccionarOpcion(opcion);
    }
}

void MenuGen::seleccionarOpcion(int opcion)
{
    switch(opcion)
    {
    case 1:
        // Llamar a la funcion para gestionar productos
        cout << "gestionar productos" << endl;
        menuProducto(producto);
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

