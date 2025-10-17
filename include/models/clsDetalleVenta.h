#ifndef CLSDETALLEVENTA_H
#define CLSDETALLEVENTA_H

#include "clsEntidad.h"

class DetalleVenta : public Entidad {
private:
    int idVenta;
    int idProducto;
    int cantidad;
    double precioVenta;
    double subtotal;
public:
    // Constructor
    DetalleVenta(int _id = 0,
                 int _idVenta = 0,
                 int _idProducto = 0,
                 int _cantidad = 0,
                 double _precioVenta = 0.0,
                 double _subtotal = 0.0,
                 bool _estado = true,
                 Fecha _fecha = Fecha(1,1,1))
        : Entidad(_id, _estado, _fecha) {
        idVenta = _idVenta;
        idProducto = _idProducto;
        cantidad = _cantidad;
        precioVenta = _precioVenta;
        subtotal = _subtotal;
    }

    ~DetalleVenta() {}

    // Implementing pure virtual functions
    void cargar() override {}
    void mostrar(int fila) override {
        std::cout << "Detalle de Venta " << id << std::endl;
        std::cout << "ID Venta: " << idVenta << std::endl;
        std::cout << "ID Producto: " << idProducto << std::endl;
        std::cout << "Cantidad: " << cantidad << std::endl;
        std::cout << "Precio: $" << precioVenta << std::endl;
        std::cout << "Subtotal: $" << subtotal << std::endl;
    }

    // Setters
    void setIdVenta(int _idVenta) { idVenta = _idVenta; }
    void setIdProducto(int _idProducto) { idProducto = _idProducto; }
    void setCantidad(int _cantidad) { cantidad = _cantidad; }
    void setPrecioVenta(double _precioVenta) { precioVenta = _precioVenta; }
    void setSubtotal(double _subtotal) { subtotal = _subtotal; }

    // Getters
    int getIdVenta() const { return idVenta; }
    int getIdProducto() const { return idProducto; }
    int getCantidad() const { return cantidad; }
    double getPrecioVenta() const { return precioVenta; }
    double getSubtotal() const { return subtotal; }
};

#endif
