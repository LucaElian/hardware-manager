#include<iostream>
using namespace std;

#include "clsCliente.h"
#include "clsFecha.h"
#include "archivoManager.h"
#include "artworks.h"

#define byte windows_byte
#include "rlutil.h"
#undef byte

#include "uiManager.h"
#include "menuCliente.h"

void menuCliente(Cliente cliente, ArchivoManager<Cliente> gestor) {
    const int OPCIONES = 5;
    const int CURSOR_START_X = 49;
    const int CURSOR_START_Y = 13;
    const int INICIO_OPCIONES = 7;
    const int CURSOR_MENU = 175;
    const int OPCION_ESPACIO = 2;
    const int ULTIMA_OPCION = 8;

    string opciones[OPCIONES] = {"AGREGAR CLIENTE", "ELIMINAR CLIENTE", "MODIFICAR CLIENTE", "LISTAR CLIENTES", "SALIR"};

    while(true) {
        int opcion = 0;
        bool curs = true;
        system("cls");

        menu("M E N U   C L I E N T E S", opciones, INICIO_OPCIONES, OPCIONES);

        while(curs == true) {
            rlutil::locate(CURSOR_START_X, CURSOR_START_Y + opcion);
            cout << (char)CURSOR_MENU;

            int pos = rlutil::getkey(); // Captura de teclas

            switch(pos) {
                case 14:
                    rlutil::locate(CURSOR_START_X, CURSOR_START_Y + opcion);
                    cout << " ";
                    opcion -= OPCION_ESPACIO;
                    if(opcion < 0) opcion = ULTIMA_OPCION;
                    break;

            case 15:
                rlutil::locate(CURSOR_START_X, CURSOR_START_Y + opcion);
                cout << " ";
                opcion += OPCION_ESPACIO;
                if(opcion > ULTIMA_OPCION) opcion = 0;
                break;

                case 1:
                    system("cls");
                    curs = false;
                    switch(opcion) {
                        case 0:
                            agregarCliente(cliente, gestor);
                            break;
                        case 2: {
                            cout << "La cantidad de clientes es: " << gestor.cantidadRegistros() << endl;
                            mostrarRegistros(gestor);
                            int idEliminar;
                            cout << "Ingrese el ID del cliente a eliminar: ";
                            cin >> idEliminar;
                            if (gestor.eliminarPorID(idEliminar)) {
                                cout << "Cliente con ID " << idEliminar << " eliminado exitosamente." << endl;
                            }
                            else {
                                cout << "No se pudo eliminar el cliente con ID " << idEliminar << "." << endl;
                            }
                        }
                        break;
                        case 4:
                            cout << "soy el metodo modificar" << endl;
                            break;
                        case 6:
                            cout << "La cantidad de clientes es: " << gestor.cantidadRegistros() << endl;
                            mostrarRegistros(gestor);
                            break;

                        case 8: return;
                    }
                system("pause");
            }
        }
    }
}

void agregarCliente(Cliente cliente, ArchivoManager<Cliente> &gestor) {
    cliente.cargar();
    gestor.escribir(&cliente);
}

