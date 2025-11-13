#ifndef CLSVENDEDOR_H_INCLUDED
#define CLSVENDEDOR_H_INCLUDED

#include <cstring>
#include "clsFecha.h"
#include "clsEntidad.h"
#include "constantes.h"

class Vendedor : public Entidad {
private:
    int legajo;
    char nombre[MAX_NOMBRE];
    char telefonoVendedor[MAX_TELEFONO];
    char dni[MAX_DNI];



public:
    // Constructor (solo declaración)
    Vendedor(int _legajo = 0,
             const char *_nombre = "vacio",
             const char *_telefonoVendedor = "vacio",
             const char *_dni = "vacio",
             bool _estado = true,
             Fecha _fecha = Fecha(1, 1, 1)); // <-- Implementación movida

    // Destructor (solo declaración)
    ~Vendedor(); // <-- Implementación movida

    // Setters especificos (solo declaración)
    void setNombre(const char *_nombre);
    void setLegajo(int _legajo);
    void setTelefonoVendedor(const char *_telefonoVendedor);
    void setDni(const char *_dni);

    // Getters especificos (solo declaración)
    const char *getNombre() const;
    const char *getTelefonoVendedor() const;
    const char *getDni() const;
    int getLegajo() const; // <-- Faltaba este en tu .h original, ¡pero lo tenías en el .cpp!

    // Implementacion con los metodos virtuales (ya estaban como declaración)
    void cargar() override;
    void modificar() override;
    void mostrar() const override;
    void mostrarFila(int posX, int posY) const override;

    void mostrar_activos() const;
};

#endif // CLSVENDEDOR_H_INCLUDED
