#include<iostream>
using namespace std;
#include "clsVendedor.h"
#include "archivoManager.h"
#include "artworks.h"
#define byte windows_byte
#include "rlutil.h"
#undef byte

void menuVendedor(Vendedor vendedor, ArchivoManager<Vendedor> gestor){
    string opciones[5] = {"AGREGAR VENDEDOR", "ELIMINAR VENDEDOR", "MODIFICAR VENDEDOR", "LISTAR VENDEDORES", "SALIR"};
    string opcioness[6] = {"LEGAJO", "NOMBRE", "DNI", "TELEFONO", "FECHA", "ESTADO"};
    int datos[6] = {10, 32, 11, 17, 12, 12};

    while(true) {
        int opcion = 0;
        bool curs = true;
        system("cls");

        menu("M E N U   V E N D E D O R", opciones, 7, 5);

        while(curs == true){
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
                                vendedor.cargar();
                                gestor.escribir(&vendedor);
                                cout << "Vendedor agregado exitosamente!" << endl;
                            }
                            break;
                        case 2: {
                                cout << "La cantidad de vendedores es: " << gestor.cantidadRegistros() << endl;
                                gestor.leer(opcioness, 3, 3, 6, datos);
                                int idEliminar;
                                cout << "Ingrese el ID del vendedor a eliminar: ";
                                cin >> idEliminar;
                                if (gestor.eliminarPorID(idEliminar)) {
                                    cout << "Vendedor con ID " << idEliminar << " eliminado exitosamente." << endl;
                                }
                                else {
                                    cout << "No se pudo eliminar el vendedor con ID " << idEliminar << "." << endl;
                                }
                            }
                            break;
                        case 4: break;
                        case 6:
                            cout << "La cantidad de vendedores es: " << gestor.cantidadRegistrosActivos() << endl;
                            gestor.leer(opcioness, 3, 3, 6, datos);
                            break;
                        case 8: return;
                    }
                    system("pause");
            }
        }
    }
}
