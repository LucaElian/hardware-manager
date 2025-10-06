#include<iostream>
using namespace std;
#include "clsProducto.h"
#include "clsFecha.h"
#include "gestorArchivo.h"
#include "artworks.h"
#define byte windows_byte
#include "rlutil.h"
#undef byte

void menuProducto(Producto producto, GestorArchivos gestor){
<<<<<<< HEAD
    string opciones[5] = {"AGREGAR PRODUCTO", "ELIMINAR PRODUCTO", "MODIFICAR PRODUCTO", "MOSTRAR PRODUCTOS", "SALIR"};
=======
    string opciones[5] = {"AGREGAR PRODUCTO", "ELIMINAR PRODUCTO", "MODIFICAR PRODUCTO", "MOSTRAR PRODUCTO", "SALIR"};
>>>>>>> f33bb5de07063265a7f9d952ac53fcc7951314da

    while(true) {
        int opcion = 0;
        bool curs = true;
        system("cls");

        menu("M E N U   P R O D U C T O", opciones, 7, 5);

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
                        case 0: {  // abre un bloque para declarar variables locales
                                //thiago aca habias creado un objeto producto, pero la funcion ya lo recibe asi q es lo mismo
                                producto.CargarP();
                                gestor.escribirProducto(producto);
                                cout << "Producto agregado exitosamente!" << endl;
                            }
                            break;
<<<<<<< HEAD
                        case 2: {
=======
                        case 2:
                            {
>>>>>>> f33bb5de07063265a7f9d952ac53fcc7951314da
                                cout << "La cantidad de productos es: " << gestor.cantidadRegistrosP() << endl;
                                gestor.leerProductos();
                                int idEliminar;
                                cout << "Ingrese el ID del producto a eliminar: ";
                                cin >> idEliminar;
                                if (gestor.eliminarProductoPorID(idEliminar)) {
                                    cout << "Producto con ID " << idEliminar << " eliminado exitosamente." << endl;
                                } 
                                else {
                                    cout << "No se pudo eliminar el producto con ID " << idEliminar << "." << endl;
                                }
                            }
                            break;
                        case 4: break;
                        case 6:
                            cout << "La cantidad de productos es: " << gestor.cantidadRegistrosP() << endl;
                            gestor.leerProductos();
                            //producto.MostrarP();
                            break;
                        case 8: return;
                    }
                    system("pause");
            }
        }
    }
}
