#include<iostream>
using namespace std;

#include "clsCliente.h"
#include "clsFecha.h"
#include "archivoManager.h"
#include "artworks.h"
#include "utilidades.h"

#define byte windows_byte
#include "rlutil.h"
#undef byte

void menuCliente(Cliente cliente, ArchivoManager<Cliente> gestor) {
    string opciones[4] = {"AGREGAR CLIENTE", "MODIFICAR CLIENTE", "MOSTRAR CLIENTES", "SALIR"};
    string opcioness[3] = {
                        "    ID    ",
                        "          N O M B R E           ",
                        "    TELEFONO     "
                        };

    int datos[3] = {10, 32, 17};

    while(true) {
        int opcion = 0;
        bool curs = true;
        system("cls");

        menu("M E N U   C L I E N T E S", opciones, 7, 4);


        while(curs == true) {
            rlutil::locate(49, 13 + opcion);
            cout << (char)175;

            int pos = rlutil::getkey(); // Captura de teclas

            switch(pos) {
                case 14:
                    rlutil::locate(49, 13 + opcion);
                    cout << " ";
                    opcion -= 2;
                    if(opcion < 0) opcion = 6;
                    break;

            case 15:
                rlutil::locate(49, 13 + opcion);
                cout << " ";
                opcion += 2;
                if(opcion > 6) opcion = 0;
                break;

                case 1:
                    system("cls");
                    curs = false;
                    switch(opcion) {
                        case 0: {
                            cliente.cargar();
                            gestor.escribir(&cliente);
                            }
                            break;
                        case 2: break;
                        case 4: {
                            if (gestor.cantidadRegistros() > 0) {
                                rlutil::locate(50, 1);
                                rlutil::setColor(rlutil::RED);
                                cout << "CANTIDAD DE CLIENTES: " << gestor.cantidadRegistros();

                                mostrar_encabezado(opcioness, 32, 3, 3, datos);
                                gestor.leer(opcioness, 32, 3, 3, datos);
                            }
                            else {
                                rlutil::locate(40, 15);
                                rlutil::setColor(rlutil::RED);
                                cerr << "NO SE ENCONTRARON REGISTROS";
                            }
                            }
                            break;
                        case 6: return;
                    }
                rlutil::setColor(rlutil::BLACK);
                system("pause");
            }
        }
    }
}



