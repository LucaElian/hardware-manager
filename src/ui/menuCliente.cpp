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

const int OPCIONES = 4;
const int CURSOR_START_X = 49;
const int CURSOR_START_Y = 13;
const int INICIO_OPCIONES = 7;
const int CURSOR_MENU = 175;
const int OPCION_ESPACIO = 2;
const int ULTIMA_OPCION = 6;

void menuCliente(Cliente cliente, ArchivoManager<Cliente> gestor) {
    string opciones[OPCIONES] = {"AGREGAR CLIENTE", "MODIFICAR CLIENTE", "MOSTRAR CLIENTES", "SALIR"};

    while(true) {
        int opcion = 0;
        bool curs = true;
        system("cls");

        menu("M E N U   C L I E N T E", opciones, INICIO_OPCIONES, OPCIONES);

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
                        case 0: agregarCliente(cliente, gestor); break;
                        case 2: modificarCliente(cliente, gestor); break;
                        case 4: cliente.mostrar(); break;
                        case 6: return;
                    }
                rlutil::setColor(rlutil::BLACK);
                system("pause");
            }
        }
    }
}

void agregarCliente(Cliente cliente, ArchivoManager<Cliente> &gestor) {
    cliente.cargar();
    gestor.escribir(&cliente);
}

void modificarCliente(Cliente cliente, ArchivoManager<Cliente> &gestor) {
    cliente.mostrar();

    if(gestor.cantidadRegistros() > 0) {
        modificarRegistro(gestor);
    }

    else {
        rlutil::locate(40, 15);
        rlutil::setColor(rlutil::RED);
        cerr << "NO SE ENCONTRARON REGISTROS ACTIVOS";
    }
}

