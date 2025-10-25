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

    // Implementacion con los metodos virtuales
    void cargar() override {}
    void mostrar() const override {
        std::cout << "Detalle de Venta " << id << std::endl;
        std::cout << "ID Venta: " << idVenta << std::endl;
        std::cout << "ID Producto: " << idProducto << std::endl;
        std::cout << "Cantidad: " << cantidad << std::endl;
        std::cout << "Precio: $" << precioVenta << std::endl;
        std::cout << "Subtotal: $" << subtotal << std::endl;
    }

    // A�ADE ESTO EN SU LUGAR:
void mostrarFila(int posX, int posY) const override {
    rlutil::locate(posX, posY);
    // Estructura (7 campos)
    std::cout << char(186) << "          " // ID
              << char(186) << "          " // ID VENTA
              << char(186) << "          " // ID PROD
              << char(186) << "        "   // CANT
              << char(186) << "               " // PRECIO
              << char(186) << "               " // SUBTOTAL
              << char(186) << "          " // ESTADO
              << char(186);

    // Rellenar con datos
    rlutil::setColor(rlutil::WHITE);
    // Ajusta estos 'posX + X' si es necesario
    rlutil::locate(posX + 2, posY); std::cout << getID();
    rlutil::locate(posX + 12, posY); std::cout << getIdVenta();
    rlutil::locate(posX + 22, posY); std::cout << getIdProducto();
    rlutil::locate(posX + 33, posY); std::cout << getCantidad();
    rlutil::locate(posX + 41, posY); std::cout << std::fixed << std::setprecision(2) << getPrecioVenta();
    rlutil::locate(posX + 57, posY); std::cout << std::fixed << std::setprecision(2) << getSubtotal();
    rlutil::locate(posX + 73, posY); std::cout << (getEstado() ? "ACTIVO" : "INACTIVO");

    rlutil::setColor(rlutil::MAGENTA);
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
