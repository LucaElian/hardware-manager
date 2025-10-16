#include<iostream>
using namespace std;
#include "clsVenta.h"
#include "gestorVenta.h"
#include "artworks.h"
#define byte windows_byte
#include "rlutil.h"
#undef byte

void menuVenta(Venta enta, GestorVenta gestor){
    string opciones[3] = {"GESTIONAR VENTA", "LISTAR VENTA", "SALIR"};

    while(true) {
        int opcion = 0;
        bool curs = true;
        system("cls");

        menu("M E N U   V E N D E D O R", opciones, 7, 3);

        while(curs == true){
            rlutil::locate(49, 13 + opcion);
            cout << (char)175;

            int pos = rlutil::getkey(); // Captura de teclas

            switch(pos) {
                case 14:
                    rlutil::locate(49, 13 + opcion);
                    cout << " ";
                    opcion -= 2;
                    if(opcion < 0) opcion = 4;
                    break;

                case 15:
                    rlutil::locate(49, 13 + opcion);
                    cout << " ";
                    opcion += 2;
                    if(opcion > 4) opcion = 0;
                    break;

                case 1:
                    system("cls");
                    curs = false;
                    switch(opcion) {
                        case 0: {
                            int legajoCreado, identificadorCliente;

                            cout << "Ingrese el id del cliente: "<<endl;
                            cin >> identificadorCliente;

                            cout << "Ingrese el legajo del vendedor: " << endl;
                            cin >> legajoCreado;

                            if (gestor.iniciarNuevaVenta(identificadorCliente, 
                                legajoCreado))cout << "SE INICIO VENTA" << endl;
                        }break;
                        case 2:
                        case 4: return;
                    }
                    system("pause");
            }
        }
    }
}
