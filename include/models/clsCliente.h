#ifndef CLIENTE_H_INCLUDED
#define CLIENTE_H_INCLUDED
#include <cstring>
#include "clsFecha.h"
#include "clsEntidad.h"

class Cliente : public Entidad {
private:
    char nombre[31];
    char telefono[16];

public:
    // Constructor
    Cliente(int _id = 0,
           const char *_nombre = "vacio",
           const char *_telefono = "vacio")
        : Entidad(_id, true, true) {
        strcpy(nombre, _nombre);
        strcpy(telefono, _telefono);
    }

    ~Cliente() {}

    // Setters especificos
    void setNombre(const char *_nombre) {
        strcpy(nombre, _nombre);
    }
    void setTelefono(const char *_telefono) {
        strcpy(telefono, _telefono);
    }

    // Getters especificos
    const char *getNombre() const { return nombre; }
    const char *getTelefono() const { return telefono; }

    // Implementacion de metodos virtuales
    void cargar() override;
    void mostrar(int x, int y) override;
};
#endif // CLIENTE_H_INCLUDED
//si, copypasteo una banda el mismo codigo que existe
