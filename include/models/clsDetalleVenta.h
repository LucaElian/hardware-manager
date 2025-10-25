#ifndef CLSDETALLEVENTA_H
#define CLSDETALLEVENTA_H

#include "clsEntidad.h"
#include <iostream>   // Para std::cout
#include <iomanip>    // Para std::fixed y std::setprecision
#include "rlutil.h"   // Para rlutil::
#define byte windows_byte
#include "rlutil.h"
#undef byte


class DetalleVenta : public Entidad
{
private:
    int idVenta;
    int idProducto;
    int cantidad;
    double precioVenta;
    double subtotal;
public:
    // Constructor (solo declaración)
    DetalleVenta(int _id = 0,
                 int _idVenta = 0,
                 int _idProducto = 0,
                 int _cantidad = 0,
                 double _precioVenta = 0.0,
                 double _subtotal = 0.0,
                 bool _estado = true,
                 Fecha _fecha = Fecha(1,1,1));

    // Destructor (solo declaración)
    ~DetalleVenta();

    // Implementacion con los metodos virtuales
    void cargar() override;
    void mostrar() const override;
    void mostrarFila(int posX, int posY) const override;

    // Setters
    void setIdVenta(int _idVenta);
    void setIdProducto(int _idProducto);
    void setCantidad(int _cantidad);
    void setPrecioVenta(double _precioVenta);
    void setSubtotal(double _subtotal);

    // Getters
    int getIdVenta() const;
    int getIdProducto() const;
    int getCantidad() const;
    double getPrecioVenta() const;
    double getSubtotal() const;
};

#endif
