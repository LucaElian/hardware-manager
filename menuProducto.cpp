#include<iostream>
using namespace std;

#include "gestorArchivo.h"
#include "clsProducto.h"
#include "clsFecha.h"

void menuProducto(Producto producto, GestorArchivos gestorProductos){ //ahora tambien recibe el objeto del gestor
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
                gestorProductos.escribirProducto(producto);
            break;
            case 2:
                //producto.MostrarP();
                //llamo al metodo para leer el archivo atraves del objeto
                gestorProductos.leerProductos();
            break;
        }
        system("pause");
    }


}
