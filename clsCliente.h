#ifndef CLIENTE_H_INCLUDED
#define CLIENTE_H_INCLUDED
#include <cstring>
#include "clsEntidad.h"

class Cliente : public Entidad {
private:
    char nombre[50];
    char apellido[30];
    char email[50];

public:
    // Constructor
    Cliente(int _id = 0,
           const char *_nombre = "vacio",
           const char *_apellido = "vacio",
           const char *_email = "vacio",
           Fecha _fecha = Fecha(1,1,1))
        : Entidad(_id, true, _fecha) {
        strcpy(nombre, _nombre);
        strcpy(apellido, _apellido);
        strcpy(email, _email);
    }

    ~Cliente() {}

    // Setters especificos
    void setNombre(const char *_nombre) { 
        strcpy(nombre, _nombre); 
    }
    void setApellido(const char *_apellido) { 
        strcpy(apellido, _apellido); 
    }
    void setEmail(const char *_email) { 
        strcpy(email, _email); 
    }

    // Getters especificos
    const char *getNombre() const { return nombre; }
    const char *getApellido() const { return apellido; }
    const char *getEmail() const { return email; }

    // Implementacion de metodos virtuales
    void cargar() override;
    void mostrar() override;
};
#endif // CLIENTE_H_INCLUDED
//si, copypasteo una banda el mismo codigo que existe