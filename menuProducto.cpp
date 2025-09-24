#include<iostream>
using namespace std;

#include "clsProducto.h"
#include "clsFecha.h"

void menuProducto(Producto producto){
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

                producto.CargarP();
                break;
            break;
            case 2:
                //producto.MostrarP();
                break;
            break;
        }
        system("pause");
    }


}
