#include <iostream>
using namespace std;

#include "clsProducto.h"
#include "clsFecha.h"
#include "archivoManager.h"
#include "artworks.h"

#define byte windows_byte
#include "rlutil.h"
#undef byte

#include "uiManager.h"
#include "menuProducto.h"

const int OPCIONES = 5;
const int CURSOR_START_X = 49;
const int CURSOR_START_Y = 13;
const int INICIO_OPCIONES = 7;
const int CURSOR_MENU = 175;
const int OPCION_ESPACIO = 2;
const int ULTIMA_OPCION = 8;

void menuProducto(Producto producto, ArchivoManager<Producto> gestor) {
    string opciones[OPCIONES] = {"AGREGAR PRODUCTO", "ELIMINAR PRODUCTO", "MODIFICAR PRODUCTO", "MOSTRAR PRODUCTOS", "SALIR"};

    while(true) {
        int opcion = 0;
        bool curs = true;
        system("cls");

        menu("M E N U   P R O D U C T O", opciones, INICIO_OPCIONES, OPCIONES);

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
                        case 0: agregarProducto(producto, gestor); break;
                        case 2: eliminarProducto(producto, gestor); break;
                        case 4: modificarRegistro(gestor); break;
                        case 6: producto.mostrar(); break;
                        case 8: return;
                    }
                rlutil::setColor(rlutil::BLACK);
                system("pause");
            }
        }
    }
}

void agregarProducto(Producto producto, ArchivoManager<Producto> &gestor) {
    producto.cargar();
    gestor.escribir(&producto);
}

void eliminarProducto(Producto producto, ArchivoManager<Producto>& gestor) {
    producto.mostrar_activos();

    if(gestor.cantidadRegistrosActivos() > 0) {
        int idEliminar;
        caja_eliminar(&idEliminar, 52, 24);

        if(gestor.eliminarPorID(idEliminar)) {
            rlutil::setColor(rlutil::WHITE);
            rlutil::locate(41, 24+3);
            cout << "PRODUCTO CON ID " << idEliminar << " ELIMINADO EXITOSAMENTE";
        }

        else {
            rlutil::setColor(rlutil::RED);
            rlutil::locate(39, 24+3);
            cout << "NO SE ENCONTRARON REGISTROS ACTIVOS CON ID " << idEliminar;
        }
    }

    else {
        rlutil::locate(40, 15);
        rlutil::setColor(rlutil::RED);
        cerr << "NO SE ENCONTRARON REGISTROS ACTIVOS";
    }
}