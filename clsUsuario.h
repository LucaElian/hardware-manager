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
                Fecha _fecha = Fecha(1,1,1)); // inicializo ac;
        ~Usuario(){}

        /// SETTERS, Como uso cargar cadena, no hace falta usar strcpy ni nada de eso, queda re lindo
        void setID(int);
        void setUser(char *);
        void setPass(char *);
        void setRol(char *);
        void setFecha(int, int, int);

        /// GETTERS
        int getID() const;
        const char *getUser() const;
        const char *getPass() const;
        const char *getRol() const;
        Fecha getFecha() const;

        ///Otros metodos
        void CargarU();
        void MostrarU();
        void setearIdentificador(int);
};

#endif // USUARIO_H_INCLUDED
