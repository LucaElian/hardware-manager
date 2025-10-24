#ifndef PRODUCTOS_H_INCLUDED
#define PRODUCTOS_H_INCLUDED
#include <cstring>
#include "clsFecha.h"
#include "clsEntidad.h"

class Producto : public Entidad {
private:
    char nombre[31];
    char tipo;
    double precio;
    int stock;

public:
    // Constructor
    Producto(int _id = 0,
            const char *_nombre = "vacio",
            const char _tipo = 'V',
            int _stock = 0,
            double _precio = 0,
            bool _estado = true,
            Fecha _fecha = Fecha(1,1,1))
        : Entidad(_id, _estado, _fecha) {
        strcpy(nombre, _nombre);
        tipo = _tipo;
        stock = _stock;
        precio = _precio;
    }

    ~Producto() {}

    // Setters especificos
    void setNombre(const char *_nombre) { strcpy(nombre, _nombre); }
    void setTipo(const char _tipo) { tipo = _tipo; }
    void setStock(int _stock) { stock = _stock; }
    void setPrecio(double _precio) { precio = _precio; }

    // Getters especificos
    const char *getNombre() const { return nombre; }
    char getTipo() const { return tipo; }
    double getPrecio() const { return precio; }
    int getStock() const { return stock; }

    // Implementacion con los metodos virtuales
    void cargar() override;
    void mostrar() const override;
    void mostrarFila(int posX, int posY) const override;

    void mostrar_activos() const;
};

#endif // PRODUCTOS_H_INCLUDED
