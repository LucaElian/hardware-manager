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

void menuProducto(Producto producto, ArchivoManager<Producto> gestor) {
    const int OPCIONES = 5;
    const int CURSOR_START_X = 49;
    const int CURSOR_START_Y = 13;
    const int INICIO_OPCIONES = 7;
    const int CURSOR_MENU = 175;
    const int OPCION_ESPACIO = 2;
    const int ULTIMA_OPCION = 8;

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
                        case 2: {
                                mostrarRegistros(gestor);
                                int idEliminar;
                                cout << "Ingrese el ID del producto a eliminar: ";
                                cin >> idEliminar;
                                if (gestor.eliminarPorID(idEliminar)) {
                                    cout << "Producto con ID " << idEliminar << " eliminado exitosamente." << endl;
                                }
                                else {
                                    cout << "No se pudo eliminar el producto con ID " << idEliminar << "." << endl;
                                }
                            }
                            break;
                        case 4: break;
                        case 6: mostrarProducto(producto); break;
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

void mostrarProducto(Producto producto) {
    producto.mostrar();
}