#include<iostream>
using namespace std;

#include "clsCliente.h"
#include "clsFecha.h"
#include "gestorArchivo.h"
#include "artworks.h"

#define byte windows_byte
#include "rlutil.h"
#undef byte

void menuCliente(Cliente cliente, GestorArchivos gestor){
    string opciones[5] = {"AGREGAR CLIENTE", "ELIMINAR CLIENTE", "MODIFICAR CLIENTE", "LISTAR CLIENTES", "SALIR"};

    while(true){
        int opcion = 0;
        bool curs = true;
        system("cls");

        menu("M E N U   C L I E N T E S", opciones, 7, 5);

        while(curs == true){
            rlutil::locate(49, 13 + opcion);
            cout << (char)175;

            int pos = rlutil::getkey(); // Captura de teclas

            switch(pos){
                case 14:
                    rlutil::locate(49, 13 + opcion);
                    cout << " ";
                    opcion -= 2;
                    if(opcion < 0) opcion = 8;
                    break;

                case 15:
                    rlutil::locate(49, 13 + opcion);
                    cout << " ";
                    opcion += 2;
                    if(opcion > 8) opcion = 0;
                    break;

                case 1:
                    system("cls");
                    curs = false;
                    switch(opcion){
                        case 0:
                            // usuario.CargarP(); // Da error
                            // gestorUsuario.escribirProductoBINARIO(producto);
                            break;
                        case 2: break;
                        case 4: break;
                        case 6:
                            // gestorUsuario.leerProductos();
                            // usuario.MostrarP(); // Da error;
                            break;
                        case 8: return;
                    }
            }
        }
    }
}



