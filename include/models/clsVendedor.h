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
    // Constructor
    Vendedor(int _legajo = 0,
            const char *_nombre = "vacio",
            const char *_telefonoVendedor = "vacio",
            const char *_dni = "vacio",
            bool _estado = true,
            Fecha _fecha = Fecha(1, 1, 1))
        : Entidad(_legajo, _estado, _fecha) {
        legajo = _legajo;
        strcpy(nombre, _nombre);
        strcpy(telefonoVendedor, _telefonoVendedor);
        strcpy(dni, _dni);
    }

    ~Vendedor() {}

    // Setters especificos
    void setNombre(const char *_nombre) { strcpy(nombre, _nombre); }
    void setLegajo(int _legajo) { legajo = _legajo; }
    void setTelefonoVendedor(const char *_telefonoVendedor) { strcpy(telefonoVendedor, _telefonoVendedor); }
    void setDni(const char *_dni) { strcpy(dni, _dni); }

    // Getters especificos
    const char *getNombre() const { return nombre; }
    const char *getTelefonoVendedor() const { return telefonoVendedor; }
    const char *getDni() const { return dni; }

    // Implementacion con los metodos virtuales
    void cargar() override;
    void modificar() override;
    void mostrar() const override;
    void mostrarFila(int posX, int posY) const override;

    void mostrar_activos() const;
};

#endif // CLSVENDEDOR_H_INCLUDED
