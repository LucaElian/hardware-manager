#ifndef CONTEXTOGESTORES_H_INCLUDED
#define CONTEXTOGESTORES_H_INCLUDED

#include "gestorArchivo.h"

struct ContextoGestores {
    GestorArchivos gestorP;
    GestorArchivos gestorU;

    ContextoGestores() : gestorP("productos.dat"), gestorU("usuarios.dat"){}
};

#endif // CONTEXTOGESTORES_H_INCLUDED
