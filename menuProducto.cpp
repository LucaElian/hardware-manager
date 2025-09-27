#include<iostream>
using namespace std;

#include "clsProducto.h"
#include "clsFecha.h"
#include "gestorArchivo.h"

void menuProducto(Producto producto, GestorArchivos gestorProductos){
    int opcion;
    while(true){
        system("cls");
        cout << "------------------Menu producto---------------" << endl;
        cout << "1. Agregar producto" << endl;
        cout << "2. Mostrar producto" << endl;
        cout << "Opcion: ";
        cin >> opcion;
        switch(opcion){
            case 1:
                producto.CargarP(); // Da error
                gestorProductos.escribirProductoBINARIO(producto);
                break;
            break;
            case 2:
                gestorProductos.leerProductos();
                //producto.MostrarP(); // Da error
                break;
            break;
        }
        system("pause");
    }


}
