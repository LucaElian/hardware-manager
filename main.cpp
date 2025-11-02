#include <iostream>

using namespace std;

#include "clsFecha.h"
#include "clsProducto.h"
#include "clsCliente.h"
#include "menuProducto.h"
#include "menuGen.h"
#include "Contexto.h"
#include "ContextoGestores.h"

//#include "genDb.h"

int main() {
    /*bool debug = 0;
    if (debug==true) {
        generarProductos();
        generarClientes();
        generarVendedores();
        generarVentas();
    }*/
    //creo el objeto del gestor para el archivo de productos
    ContextoGestores gestores;
    Contexto objetos;
    MenuGen::mostrarMenuPrincipal(gestores, objetos);

    return 0;
}
