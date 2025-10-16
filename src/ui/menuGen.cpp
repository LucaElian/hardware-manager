#include <iostream>

using namespace std;

#include "menuGen.h"
#include "menuProducto.h"
#include "menuCliente.h"
#include "menuVendedor.h"
#include "menuVenta.h"
#include "Contexto.h"
#include "utilidades.h"
#include "artworks.h"

#define byte windows_byte
#include "rlutil.h"
#undef byte

///ESTA FUNCION MUESTRA EL MENU Y CONTROLA CON RLUTIL EL MOVIMIENTO DE LAS FLECHAS ---------------------------
//recibe el archivo del gestor para pasarselo a todos los menues, y el struct contexto con todos los objetos, tambien para pasarle a los menues
void MenuGen::mostrarMenuPrincipal(ContextoGestores gestores, Contexto objetos) {
    string opciones[5] = {"GESTIONAR PRODUCTOS", "GESTIONAR CLIENTES", "GESTIONAR VENDEDORES", "VENTA","SALIR"};

    while(true) {
        rlutil::hidecursor();
        int opcion = 0;
        bool curs = true;
        system("cls");

        titulo();
        menu("M E N U   G E S T O R", opciones, 10, 5);

        while(curs == true) {
            rlutil::locate(45, 16 + opcion);
            cout << (char)175;

            int pos = rlutil::getkey(); // Captura de teclas

            switch(pos) {
                case 14:
                    rlutil::locate(45, 16 + opcion);
                    cout << " ";
                    opcion -= 2;
                    if(opcion < 0) opcion = 8;
                    break;

                case 15:
                    rlutil::locate(45, 16 + opcion);
                    cout << " ";
                    opcion += 2;
                    if(opcion > 8) opcion = 0;
                    break;

                case 1:
                    system("cls");
                    curs = false;
                    switch(opcion) {
                        case 0: menuProducto(objetos.producto, gestores.gestorP); break;
                        case 2: menuCliente(objetos.cliente, gestores.gestorC); break;
                        case 4: menuVendedor(objetos.vendedor, gestores.gestorV); break;
                        case 6: menuVenta(objetos.venta, gestores.gestorVenta);
                        case 8: return;
                    }
            }
        }
    }
}




