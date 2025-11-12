#include<iostream>
using namespace std;

#include "clsVenta.h"
#include "gestorVenta.h"
#include "ContextoGestores.h"
#include "menuVenta.h"
#include "uiManager.h"
#include "artworks.h"

#define byte windows_byte
#include "rlutil.h"
#undef byte

const int OPCIONES = 4;
const int CURSOR_START_X = 48;
const int CURSOR_START_Y = 13;
const int INICIO_OPCIONES = 7;
const int CURSOR_MENU = 175;
const int OPCION_ESPACIO = 2;
const int ULTIMA_OPCION = 6;

void menuVenta(GestorVenta& gestor, ContextoGestores& contexto) {
    Venta venta;
    string opciones[OPCIONES] = {"AGREGAR VENTA", "MOSTRAR VENTA", "MOSTRAR INFO DE VENTA", "SALIR"};

    while(true) {
        int opcion = 0;
        bool curs = true;
        system("cls");

        menu("M E N U   V E N T A", opciones, INICIO_OPCIONES, OPCIONES);

        while(curs == true){
            rlutil::locate(CURSOR_START_X, CURSOR_START_Y + opcion);
            cout << (char)CURSOR_MENU;

            int pos = rlutil::getkey();

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
                        case 0: venta.cargar(); break;
                        case 2: venta.mostrar(); break;
                        case 4: gestor.listarDetallesVentas(); break;
                        case 6: return;
                    }
                rlutil::setColor(rlutil::BLACK);
                system("pause");
            }
        }
    }
}

