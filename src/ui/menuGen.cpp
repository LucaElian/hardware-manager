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
#include "menuReports.h"

#define byte windows_byte
#include "rlutil.h"
#undef byte

#include "genDb.h"

const int OPCIONES = 6;
const int CURSOR_START_X = 45;
const int CURSOR_START_Y = 16;
const int INICIO_OPCIONES = 10;
const int CURSOR_MENU = 175;
const int OPCION_ESPACIO = 2;
const int ULTIMA_OPCION = 10;

///ESTA FUNCION MUESTRA EL MENU Y CONTROLA CON RLUTIL EL MOVIMIENTO DE LAS FLECHAS ---------------------------
//recibe el archivo del gestor para pasarselo a todos los menues, y el class contexto con todos los objetos, tambien para pasarle a los menues
void MenuGen::mostrarMenuPrincipal(ContextoGestores gestores, Contexto objetos) {
    string opciones[6] = {"PRODUCTOS", "CLIENTES", "VENDEDORES", "VENTAS", "REPORTES", "SALIR"};

    while(true) {
        rlutil::hidecursor();
        int opcion = 0;
        bool curs = true;
        system("cls");

        titulo();
        menu("M E N U   G E S T O R", opciones, INICIO_OPCIONES, OPCIONES);

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
                case 20: // F3
                    rlutil::locate(1,1);
                    rlutil::setColor(rlutil::GREEN);
                    system("python test/borrar_archivo.py");
                    generarProductos();
                    generarClientes();
                    generarVendedores();
                    generarVentas();
                    rlutil::setColor(rlutil::MAGENTA);
                    break;
                case 1:
                    system("cls");
                    curs = false;
                    switch(opcion) {
                        case 0: menuProducto(objetos.producto, gestores.gestorP); break;
                        case 2: menuCliente(objetos.cliente, gestores.gestorC); break;
                        case 4: menuVendedor(objetos.vendedor, gestores.gestorV); break;
                        case 6: menuVenta(gestores.gestorVenta, gestores); break;
                        case 8: menuReports(gestores);
                        case 10: return;
                    }
            }
        }
    }
}




