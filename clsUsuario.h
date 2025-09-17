#ifndef USUARIO_H_INCLUDED
#define USUARIO_H_INCLUDED
#include <cstring>

#include "clsFecha.h"

class Usuario {
    private:
        char user[20];
        char pass[20];
        char rol[20];
        Fecha ingresa;
    public:
        Usuario(char _user[20], char _pass[20], char _rol[20], Fecha _fecha);
        ~Usuario(){}

        /// GETTERS
        char const *getUser() const {return user;}
        char const *getPass() const {return pass;}
        char const *getRol() const {return rol;}
        Fecha getFecha() const {return ingresa;}

        /// SETTERS
        void setUser(char u[20]) {strcpy(user, u);}
        void setPass(char p[20]) {strcpy(pass, p);}
        void setRol(char r[20]) {strcpy(rol, r);}
        void setFecha(int d, int m, int a) {ingresa.setFecha(d, m, a);}
};

#endif // USUARIO_H_INCLUDED
