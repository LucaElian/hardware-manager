#ifndef USUARIO_H_INCLUDED
#define USUARIO_H_INCLUDED
#include <cstring>

#include "clsFecha.h"

class Cliente
{
private:
    int idCliente;
    char nombre[50];
    char email[50];
    Fecha ingresoC;
public:
    //Creacion del constructor principal (en el .h), parsea todos los valores para sus nuevos "_"
    Cliente( int _idCliente = 0,
            const char *_nombre = "vacio",
             const char *_email = "vacio",
            Fecha _fecha = Fecha(1,1,1));

    ~Cliente() {}

    /// SETTERS, Como uso cargar cadena, no hace falta usar strcpy ni nada de eso, queda re lindo
    void setID(int);
    void setNombre(char *);
    void setEmail(char *);
    void setFecha(int, int, int);

    /// GETTERS
    int getID() const;
    const char *getNombre() const;
    const char *getEmail() const;
    Fecha getFecha() const;

    ///Otros metodos
    void CargarC();
    void MostrarC();
    void setearIdentificador(int);
};

#endif // USUARIO_H_INCLUDED
