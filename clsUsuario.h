#ifndef USUARIO_H_INCLUDED
#define USUARIO_H_INCLUDED
#include <cstring>

#include "clsFecha.h"

class Usuario {
    //Declaro en privado los atributos
    private:
        char user[20];
        char pass[20];
        char rol[20];
        //recibe desde fecha el valor de "ingresa"
        Fecha ingresa;
    //declaro en publico mis metodos
    public:
        //Constructor principal, parsea todos los valores para sus nuevos "_"
        Usuario(const char *_user, const char *_pass, const char *_rol, Fecha _fecha);
        //Constructor vacio
        Usuario();
        ~Usuario(){}

        /// GETTERS
        char const *getUser();
        char const *getPass();
        char const *getRol();
        Fecha getFecha();

        /// SETTERS
        void setUser(char u[20]) {strcpy(user, u);}
        void setPass(char p[20]) {strcpy(pass, p);}
        void setRol(char r[20]) {strcpy(rol, r);}
        void setFecha(int d, int m, int a) {ingresa.setFecha(d, m, a);}

        ///Otros metodos
        void Mostrar();
};

#endif // USUARIO_H_INCLUDED
