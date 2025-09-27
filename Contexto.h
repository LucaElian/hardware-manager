#ifndef CONTEXTO_H_INCLUDED
#define CONTEXTO_H_INCLUDED

#include "clsUsuario.h"
#include "clsProducto.h"
#include "gestorArchivo.h"


struct Contexto {
    Producto producto;
    Usuario usuario;
    //GestorArchivos gestor;
};



#endif // CONTEXTO_H_INCLUDED
