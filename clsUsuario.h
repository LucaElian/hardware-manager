#ifndef USUARIO_H_INCLUDED
#define USUARIO_H_INCLUDED
#include <cstring>

#include "clsFecha.h"

class Usuario {
    private:
        int id;
        char nombre[20];
        char apellido[20];
        char pass[50];
        char rol[20];
        Fecha ingresaFecha;

        void cargarId();
        void cargarNombre();
        void cargarApellido();
        void cargarPass();
        void cargarRol();

    public:
        /// CONSTRUCTOR Y DESTRUCTOR
        Usuario(int _id = 0,
                const char *_nombre = "",
                const char *_apellido = "",
                const char *_pass = "",
                const char *_rol = "",
                Fecha _fecha = Fecha(1,1,1));
        ~Usuario(){}

        /// GETTERS
        int getID() const {return id;};
        char const *getNombre() const {return nombre;}
        char const *getApellido() const {return apellido;}
        char const *getPass() const {return pass;}
        char const *getRol() const {return rol;}
        std::string getFecha() const {return ingresaFecha.formatToDate();}

        /// SETTERS
        void setNombre(char n[20]) {strcpy(nombre, n);}
        void setApellido(char a[20]) {strcpy(apellido, a);}
        void setPass(char p[50]) {strcpy(pass, p);}
        void setRol(char r[20]) {strcpy(rol, r);}
        void setFecha(int d, int m, int a) {ingresaFecha.setFecha(d, m, a);}

        /// METODOS
        void cargarDatos();
        void mostrar();
};

#endif // USUARIO_H_INCLUDED
