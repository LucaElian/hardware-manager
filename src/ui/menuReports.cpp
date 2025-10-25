#include "menuReports.h"
#include "artworks.h"
#include <iostream>
#include "archivoManager.h"
#include "rlutil.h"
#include "uiManager.h"
#include <string>
#include "ContextoGestores.h"

#define byte windows_byte
#include "rlutil.h"
#undef byte

void menuReports([[maybe_unused]] ContextoGestores& contextoGestores) {
    const int TAMANIO_MENU = 6;
    std::string opciones[TAMANIO_MENU] = {
        "VENTAS DEL ULTIMO CUATRIMESTRE", 
        "CLIENTE CON MAS PRODUCTOS", 
        "TOP 3 VENDEDORES", 
        "PRODUCTO MAS VENDIDO",
        "VENTA CON MAYOR MONTO",
        "SALIR"
    };

    const int INICIO_MENU_Y = 7;
    const int POSICION_CURSOR_X = 44;
    const int ESPACIO_MENU = 13;
    const int OPCION_MAXIMA = 10;

    while(true) {
        int opcionSeleccionada = 0;
        bool cursorActivo = true;
        system("cls");

        menu("R E P O R T E S", opciones, INICIO_MENU_Y, TAMANIO_MENU);

        while(cursorActivo == true) {
            rlutil::locate(POSICION_CURSOR_X, ESPACIO_MENU + opcionSeleccionada);
            std::cout << (char)175;

            int teclaPresionada = rlutil::getkey();
            const int PASO_OPCION = 2;
            const int PASO_ABAJO = 2;

            switch(teclaPresionada) {
                case 14: // Flecha arriba
                    rlutil::locate(POSICION_CURSOR_X, ESPACIO_MENU + opcionSeleccionada);
                    std::cout << " ";
                    opcionSeleccionada -= PASO_OPCION;
                    if(opcionSeleccionada < 0) opcionSeleccionada = OPCION_MAXIMA;
                    break;

                case 15: // Flecha abajo
                    rlutil::locate(POSICION_CURSOR_X, ESPACIO_MENU + opcionSeleccionada);
                    std::cout << " ";
                    opcionSeleccionada += PASO_ABAJO;
                    if(opcionSeleccionada > OPCION_MAXIMA) opcionSeleccionada = 0;
                    break;

                case 1: // Enter
                    system("cls");
                    cursorActivo = false;
                    switch(opcionSeleccionada) {
                        case 0: 
                            std::cout << "Mostrando ventas del ultimo cuatrimestre..." << std::endl;
                            break;
                        case 2:
                            std::cout << "Mostrando cliente con mas productos..." << std::endl;
                            break;
                        case 4:
                            std::cout << "Mostrando top 3 vendedores..." << std::endl;
                            break;
                        case 6:
                            std::cout << "Mostrando producto más vendido..." << std::endl;
                            break;
                        case 8:
                            std::cout << "Mostrando venta con mayor monto..." << std::endl;
                            break;
                        case 10: 
                            return;
                    }
                    system("pause");
            }
        }
    }
}

/*
Opción 1: Ventas del último cuatrimestre
*/
// void opcion1(ContextoGestores& contextoGestores) {
// }

/*
Opción 2: Cliente con más productos
*/
// void opcion2(ContextoGestores& contextoGestores) {
//     // Obtener el cliente con más productos comprados
//     id
// }