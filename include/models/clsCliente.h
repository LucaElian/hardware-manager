#ifndef CLIENTE_H_INCLUDED
#define CLIENTE_H_INCLUDED
#include <cstring>
#include "clsFecha.h"
#include "clsEntidad.h"
#include "constantes.h"

class Cliente : public Entidad {
private:
    char nombre[MAX_NOMBRE];
    char telefono[MAX_TELEFONO];

    //UI
    const size_t OPCIONES = 3;
    const int INICIO_TITULO = 3;
    const int INICIO_TABLA = INICIO_TITULO + 5;
    const int CURSOR_START_X = 30;
    const int CURSOR_START_Y = 4;
    const int PAGINADO = 15;

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
    void modificar() override;
    void mostrar() const override;
    void mostrarFila(int posX, int posY) const override;
};

#endif // CLIENTE_H_INCLUDED
