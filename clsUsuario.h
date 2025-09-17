#ifndef USUARIO_H_INCLUDED
#define USUARIO_H_INCLUDED
#include <cstring>

#include "clsFecha.h"

class Usuario {
    //Declaro en privado los atributos
    private:
        int id;
        char user[50];
        char pass[50];
        char rol[20];
        //recibe desde fecha el valor de "ingresa"
        Fecha ingresa;
    //declaro en publico mis metodos
    public:
        //Creacion del constructor principal (en el .h), parsea todos los valores para sus nuevos "_"
        Usuario(int _id = 0,
                const char *_user = "vacio",
                const char *_pass = "vacio",
                const char *_rol = "vacio",
                Fecha _fecha);

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
