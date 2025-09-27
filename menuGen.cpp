#include <iostream>
#include "rlutil.h"
#include "menuGen.h"
#include "menuProducto.h"
#include "Contexto.h"

using namespace std;

///ESTA FUNCION MUESTRA EL MENU Y CONTROLA CON RLUTIL EL MOVIMIENTO DE LAS FLECHAS ---------------------------
//recibe el archivo del gestor para pasarselo a todos los menues, y el struct contexto con todos los objetos, tambien para pasarle a los menues
void MenuGen::mostrarMenuPrincipal(ContextoGestores gestores, Contexto objetos)
{
    const int OPCIONES = 3;
    int opcionSeleccionada = 1;
    bool salir = false;
    const string opciones[OPCIONES] =
    {
        "Gestionar Productos",
        "Gestionar Usuarios",
        "Salir"
    };

    while(!salir)
    {
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
        for(int i = 0; i < OPCIONES; i++)
        {
            rlutil::locate(35, 5+i);
            if(i + 1 == opcionSeleccionada)
            {
                rlutil::setColor(rlutil::GREEN);
                cout << "> " << opciones[i] << endl;
            }
            else
            {
                rlutil::setColor(rlutil::WHITE);
                cout << "  " << opciones[i] << endl;
            }
        }

        // Captura de teclas
        int key = rlutil::getkey();

        //le pedi a chat gpt que me lo haga en un idioma mas principante porq si no no tiene onda, todo copilot
        //Recibo la tecla W o la flecha del usuario
        if (key == rlutil::KEY_UP || key == 'w' || key == 'W')
        {
            if (opcionSeleccionada > 1)
            {
                opcionSeleccionada = opcionSeleccionada - 1; // sube una opción
            }
            else
            {
                opcionSeleccionada = OPCIONES; // si estaba en la primera, salta a la última
            }
        }
        else if (key == rlutil::KEY_DOWN || key == 's' || key == 'S')
        {
            if (opcionSeleccionada < OPCIONES)
            {
                opcionSeleccionada = opcionSeleccionada + 1; // baja una opción
            }
            else
            {
                opcionSeleccionada = 1; // si estaba en la última, vuelve a la primera
            }
        }
        else if (key == rlutil::KEY_ENTER || key == '\n')
        {
            seleccionarOpcion(opcionSeleccionada, gestores, objetos); // ejecuta la opción elegida

            if (opcionSeleccionada == OPCIONES)
            {
                salir = true; // si era la última opción (ej: "Salir"), termina el programa
            }
        }

        rlutil::showcursor();
        rlutil::setColor(rlutil::WHITE);
    }
}

///Ahora si, esta funcion tiene el switch de seleccionar opcion --------------------------------------------------------------------
    void MenuGen::seleccionarOpcion(int opcion, ContextoGestores gestores, Contexto objetos)
    {
        switch(opcion)
        {
        case 1:
            // Llamar a la funcion para gestionar productos
            cout << "gestionar productos" << endl;
            //le paso el respectivo objeto de productos y luego el gestor para poder cargar en los archivos de producto
            menuProducto(objetos.producto, gestores.gestorP);
            break;
        case 2:
            // Llamar a la funcion para gestionar usuarios
            cout << "gestionar usuarios" << endl;
            break;
        case 3:
            cout << "Saliendo del programa..." << std::endl;
            //falta desarrollar
            break;
        default:
            cout << "Opcion invalida. Intente de nuevo." << std::endl;
            break;
        }
            system("pause");
    }

