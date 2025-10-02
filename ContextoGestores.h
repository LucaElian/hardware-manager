#ifndef CONTEXTOGESTORES_H_INCLUDED
#define CONTEXTOGESTORES_H_INCLUDED

#include "gestorArchivo.h"

struct ContextoGestores {
    GestorArchivos gestorP;
    GestorArchivos gestorC;

    ContextoGestores() : gestorP("productos.dat"), gestorC("clientes.dat"){}
};

#endif // CONTEXTOGESTORES_H_INCLUDED
