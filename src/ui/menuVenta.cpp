#include<iostream>
using namespace std;
#include "clsVenta.h"
#include "gestorVenta.h"
#include "artworks.h"
#define byte windows_byte
#include "rlutil.h"
#undef byte
#include "ContextoGestores.h"
#include "menuVenta.h"

void menuVenta(GestorVenta& gestor, ContextoGestores& contexto) {
    const int CURSOR_X_POS = 48;
    const int CURSOR_Y_POS = 13;
    const int SALTO_ENTRE_OPCIONES = 2;
    const int ULTIMA_OPCION = 6;
    const int OPCIONES = 4;
    const int INICIO_OPCIONES = 7;
    const int CURSOR_MENU = 175; // Código ASCII para el cursor
    string opciones[OPCIONES] = {"GESTIONAR VENTA", "LISTAR VENTA", "LISTAR DETALLES DE VENTAS", "SALIR"};

    while(true) {
        int opcion = 0;
        bool curs = true;

        system("cls");

        menu("M E N U   V E N D E D O R", opciones, INICIO_OPCIONES, OPCIONES);

        while(curs == true){
            rlutil::locate(CURSOR_X_POS, CURSOR_Y_POS + opcion);
            cout << (char)CURSOR_MENU;

            int pos_cursor = rlutil::getkey(); // Captura de teclas

            switch(pos_cursor) {
                case 14:
                    rlutil::locate(CURSOR_X_POS, CURSOR_Y_POS + opcion);
                    cout << " ";
                    opcion -= SALTO_ENTRE_OPCIONES;
                    if(opcion < 0) opcion = ULTIMA_OPCION;
                    break;

                case 15:
                    rlutil::locate(CURSOR_X_POS, CURSOR_Y_POS + opcion);
                    cout << " ";
                    opcion += SALTO_ENTRE_OPCIONES;
                    if(opcion > ULTIMA_OPCION) opcion = 0;
                    break;

                case 1:
                    system("cls");
                    curs = false;
                    switch(opcion) {
                        case 0: {
                            procesarVenta(contexto, gestor);
                        }break;
                        case 2:{
                            gestor.listarVentas();
                        }break;
                        case 4:{
                            gestor.listarDetallesVentas();
                        }break;
                        case 6: return;
                    }
                    system("pause");
            }
        }
    }
}

void procesarVenta(ContextoGestores& contexto, GestorVenta& gestor){
    int legajoCreado, identificadorCliente;

    cout << "Ingrese el id del cliente: "<<endl;
    cin >> identificadorCliente;

    cout << "Ingrese el legajo del vendedor: " << endl;
    cin >> legajoCreado;

    if (gestor.iniciarNuevaVenta(identificadorCliente, 
        legajoCreado))cout << "SE INICIO VENTA" << endl;

    vector<Producto> p;
    contexto.gestorP.leerTodos(p);
    
    cout << "=== LISTA DE PRODUCTOS DISPONIBLES ===" << endl;

    for (const auto& producto : p) {
        cout << "ID: " << producto.getID()
                << " - Nombre: " << producto.getNombre()
                << " - Precio: $" << producto.getPrecio() << endl;
    }

    int idProducto, cantidad;
    char continuar;

    do {
        cout << "Ingrese el ID del producto a agregar: ";
        cin >> idProducto;
        cout << "Ingrese la cantidad: ";
        cin >> cantidad;

        if (gestor.agregarProducto(idProducto, cantidad)) {
            cout << "Producto agregado al carrito." << endl;
        } else {
            cout << "Error: No hay stock suficiente o el producto no existe." << endl;
        }

        gestor.mostrarCarrito();

        cout << "¿Desea agregar otro producto? (s/n): ";
        cin >> continuar;
    } while (continuar == 's' || continuar == 'S');

    if (gestor.finalizarVenta()) {
        cout << "Venta finalizada exitosamente." << endl;
    } else {
        cout << "Error al finalizar la venta." << endl;
    }
}