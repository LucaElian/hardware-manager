#ifndef PRODUCTOS_H_INCLUDED
#define PRODUCTOS_H_INCLUDED

#include <cstring>
#include "clsFecha.h"
#include "clsEntidad.h"
#include "constantes.h"

class Producto : public Entidad {
private:
    char nombre[MAX_NOMBRE];
    char tipo;
    double precio;
    int stock;

public:
    // Constructor (solo declaración)
    Producto(int _id = 0,
             const char *_nombre = "vacio",
             const char _tipo = 'V',
             int _stock = 0,
             double _precio = 0,
             bool _estado = true,
             Fecha _fecha = Fecha(1,1,1)); // <-- Implementación movida

    // Destructor (solo declaración)
    ~Producto(); // <-- Implementación movida

    // Setters especificos (solo declaración)
    void setNombre(const char *_nombre);
    void setTipo(const char _tipo);
    void setStock(int _stock);
    void setPrecio(double _precio);

    // Getters especificos (solo declaración)
    const char *getNombre() const;
    char getTipo() const;
    double getPrecio() const;
    int getStock() const;

    // Métodos virtuales (ya estaban como declaración)
    void cargar() override;
    void modificar() override;
    void mostrar() const override;
    void mostrarFila(int posX, int posY) const override;

    void mostrar_activos() const;
};

#endif // PRODUCTOS_H_INCLUDED
