#include <iostream>

using namespace std;

#include "clsFecha.h"
#include "clsProducto.h"
#include "clsCliente.h"
#include "menuProducto.h"
#include "menuGen.h"
#include "Contexto.h"
#include "ContextoGestores.h"

int main() {
    //creo el objeto del gestor para el archivo de productos
    ContextoGestores gestores;
    Contexto objetos;
    MenuGen::mostrarMenuPrincipal(gestores, objetos);

    return 0;
}
