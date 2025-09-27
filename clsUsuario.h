#ifndef USUARIO_H_INCLUDED
#define USUARIO_H_INCLUDED
#include <cstring>

#include "clsFecha.h"

class Usuario {
    //Declaro en privado los atributos
    private:
        int id;
        char user[30];
        char pass[30];
        char rol[20];
        //recibe desde fecha el valor de "ingresa"
        Fecha ingresoUsuario;
    //declaro en publico mis metodos
    public:
        //Creacion del constructor principal (en el .h), parsea todos los valores para sus nuevos "_"
        Usuario(int _id = 0,
                const char *_user = "vacio",
                const char *_pass = "vacio",
                const char *_rol = "vacio",
                Fecha _fecha = Fecha(0,0,0)); // inicializo ac;
        ~Usuario(){}

        /// GETTERS
        char const *getUser();
        char const *getPass();
        char const *getRol();
        Fecha getFecha();

        /// SETTERS, Como uso cargar cadena, no hace falta usar strcpy ni nada de eso, queda re lindo
        void setUser(char);
        void setPass(char);
        void setRol(char);
        void setFecha(int, int, int);

        ///Otros metodos
        void CargarU();
        void MostrarU();
};

#endif // USUARIO_H_INCLUDED
