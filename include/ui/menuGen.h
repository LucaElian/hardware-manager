#ifndef MENUGEN_H_INCLUDED
#define MENUGEN_H_INCLUDED
#include "Contexto.h"
#include "ContextoGestores.h"

class MenuGen{
public:
    static void mostrarMenuPrincipal(ContextoGestores gestores, Contexto objetos);
    static void seleccionarOpcion(int opcion, ContextoGestores gestores, Contexto objetos);

};

#endif // MENUGEN_H_INCLUDED
