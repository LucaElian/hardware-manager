#include <iostream>
using namespace std;

#include "clsProducto.h"
#include "clsFecha.h"
#include "archivoManager.h"
#include "artworks.h"
#include "utilidades.h"

#define byte windows_byte
#include "rlutil.h"
#undef byte

void menuProducto(Producto producto, ArchivoManager<Producto> gestor) {
    string opciones[5] = {"AGREGAR PRODUCTO", "ELIMINAR PRODUCTO", "MODIFICAR PRODUCTO", "MOSTRAR PRODUCTOS", "SALIR"};
    string opcioness[7] = {
                            "    ID    ",
                            "          N O M B R E           ",
                            "    TIPO    ",
                            "   STOCK   ",
                            "       PRECIO       ",
                            "   FECHA    ",
                            "  ESTADO  "
                            };

    int datos[7] = {10, 32, 12, 11, 20, 12, 10};


    while(true) {
        int opcion = 0;
        bool curs = true;
        system("cls");

        menu("M E N U   P R O D U C T O", opciones, 7, 5);

        while(curs == true) {
            rlutil::locate(49, 13 + opcion);
            cout << (char)175;

            int pos = rlutil::getkey(); // Captura de teclas

            switch(pos) {
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
                    switch(opcion) {
                        case 0: {
                                producto.cargar();
                                gestor.escribir(&producto);
                            }
                            break;
                        case 2: {
                                cout << "La cantidad de productos es: " << gestor.cantidadRegistros() << endl;
                                gestor.leer(opciones, 3, 7, datos, gestor.cantidadRegistrosActivos());
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
                        case 6: {
                            rlutil::locate(50, 1);
                            rlutil::setColor(rlutil::RED);
                            cout << "CANTIDAD DE PRODUCTOS: " << gestor.cantidadRegistrosActivos();

                            mostrar_encabezado(opcioness, 3, 7, datos);

                            gestor.leer(opcioness, 3, 7, datos, gestor.cantidadRegistrosActivos());
                            break;
                        }
                        case 8: return;
                    }
                    system("pause");
            }
        }
    }
}
