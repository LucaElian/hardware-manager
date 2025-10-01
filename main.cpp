#include <iostream>

using namespace std;

#include "clsFecha.h"
#include "clsProducto.h"
#include "clsCliente.h"
#include "menuProducto.h"
#include "menuGen.h"
#include "gestorArchivo.h"
#include "Contexto.h"
#include "ContextoGestores.h"

int main(){
    //creo el objeto del gestor para el archivo de productos
    ContextoGestores gestores;
    Contexto objetos;
    MenuGen::mostrarMenuPrincipal(gestores, objetos);

    /*fe.mostrarFechaProducto();
    cout << "\n\n";

    p1.mostrar();
    cout << "\n\n";

    u1.mostrar();
    cout << "\n\n";*/

    /// Producto p2;
    /// p2.cargar();
    /// cout << "\n\n";
    /// p2.mostrar();

    /*Usuario u2;
    u2.cargarDatos();
    cout << "\n\n";
    u2.mostrar();*/

    return 0;
}
