#include<iostream>
using namespace std;

#include "clsProducto.h"
#include "clsFecha.h"
#include "gestorArchivo.h"
#include "artworks.h"

#define byte windows_byte
#include "rlutil.h"
#undef byte

void menuProducto(Producto producto, GestorArchivos gestorProductos){
    string opciones[5] = {"AGREGAR PRODUCTO", "ELIMINAR PRODUCTO", "MODIFICAR PRODUCTO", "MOSTRAR PRODUCTO", "SALIR"};

    while(true){
        int opcion = 0;
        bool curs = true;
        system("cls");

        menu("M E N U   P R O D U C T O", opciones, 7, 5);

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
                            {  // abre un bloque para declarar variables locales
                                Producto nuevoProducto;  //cread un producto NUEVO aca
                                nuevoProducto.CargarP();
                                gestorProductos.escribirProductoBINARIO(nuevoProducto);
                                cout << "Producto agregado exitosamente!" << endl;
                            }
                        case 2: 
                            {//cod aux
                                gestorProductos.leerProductos();
                                int idEliminar;
                                cout << "Ingrese el ID del producto a eliminar: ";
                                cin >> idEliminar;
                                if (gestorProductos.eliminarProductoPorID(idEliminar)) {
                                    cout << "Producto con ID " << idEliminar << " eliminado exitosamente." << endl;
                                } else {
                                    cout << "No se pudo eliminar el producto con ID " << idEliminar << "." << endl;
                                }
                            }
                            break;
                        case 4: break;
                        case 6:
                            cout << "La cantidad de productos es: " << gestorProductos.cantidadRegistros() << endl;
                            gestorProductos.leerProductos();
                            //producto.MostrarP();
                            break;
                        case 8: return;
                    }
                    system("pause");
            }
        }
    }
}
