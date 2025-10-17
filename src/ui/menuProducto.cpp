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
                            if (gestor.cantidadRegistrosActivos() > 0) {
                                rlutil::locate(54, 1);
                                rlutil::setColor(rlutil::RED);
                                cout << "CANTIDAD DE PRODUCTOS: " << gestor.cantidadRegistrosActivos();

                                mostrar_encabezado(opcioness, 3, 3, 7, datos);
                                gestor.leer(opcioness, 3, 3, 7, datos);
                                rlutil::locate(52, 24);
                                cout << (char)201; centrar_texto("", (char)205, 4); cout << (char)203;
                                centrar_texto("", (char)205, 10); cout << (char)187;

                                rlutil::locate(52, 25);
                                cout << (char)186; rlutil::setColor(rlutil::GREY); cout << " ID ";
                                rlutil::setColor(rlutil::RED); cout << (char)186;
                                cout << "          " << (char)186;

                                rlutil::locate(52, 26);
                                cout << (char)200; centrar_texto("", (char)205, 4); cout << (char)202;
                                centrar_texto("", (char)205, 10); cout << (char)188;

                                rlutil::locate(59, 25);
                                rlutil::showcursor();
                                rlutil::setColor(rlutil::WHITE);
                                int idEliminar = cargarInt(8);
                                rlutil::hidecursor();

                                rlutil::locate(41, 27);
                                if (gestor.eliminarPorID(idEliminar)) {
                                    rlutil::setColor(rlutil::WHITE);
                                    cout << "PRODUCTO CON ID " << idEliminar << " ELIMINADO EXITOSAMENTE";
                                }

                                else {
                                    rlutil::locate(41, 27);
                                    rlutil::setColor(rlutil::RED);
                                    cerr << "NO SE ENCONTRARON REGISTROS ACTIVOS CON ID " << idEliminar;
                                }
                            }
                            }
                            break;
                        case 4: break;
                        case 6: {
                            if (gestor.cantidadRegistrosActivos() > 0) {
                                rlutil::locate(50, 1);
                                rlutil::setColor(rlutil::RED);
                                cout << "CANTIDAD DE PRODUCTOS: " << gestor.cantidadRegistrosActivos();

                                mostrar_encabezado(opcioness, 3, 3, 7, datos);
                                gestor.leer(opcioness, 3, 3, 7, datos);
                            }
                            else {
                                rlutil::locate(40, 15);
                                rlutil::setColor(rlutil::RED);
                                cerr << "NO SE ENCONTRARON REGISTROS ACTIVOS";
                            }
                            }
                            break;
                        case 8: return;
                    }
                rlutil::setColor(rlutil::BLACK);
                system("pause");
            }
        }
    }
}
