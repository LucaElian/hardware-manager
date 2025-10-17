#ifndef CLSVENTA_H
#define CLSVENTA_H

#include "clsEntidad.h"

class Venta : public Entidad {
private:
    int idVenta;
    int idCliente;
    int legajoVendedor;
    double total;
    Fecha fechaVenta;
public:
    // Constructor
    Venta(int _id = 0,
          int _idVenta = 0,
          int _idCliente = 0,
          int _legajoVendedor = 0,
          double _total = 0.0,
          bool _estado = true,
          Fecha _fechaVenta = Fecha(1,1,1))
        : Entidad(_id, _estado, _fechaVenta) {
        idVenta = _idVenta;
        idCliente = _idCliente;
        legajoVendedor = _legajoVendedor;
        total = _total;
    }

    // Destructor
    ~Venta() {}

    // Implementing pure virtual functions
    void cargar() override {}
    void mostrar(int x, int y) override {
        std::cout << "Venta #" << idVenta << std::endl;
        std::cout << "Cliente: " << idCliente << std::endl;
        std::cout << "Vendedor: " << legajoVendedor << std::endl;
        std::cout << "Total: $" << total << std::endl;
        std::cout << "Fecha: ";
        fechaVenta.MostrarF();
        std::cout << std::endl;
    }

    // Setters
    void setIdVenta(int _idVenta) { idVenta = _idVenta; }
    void setIdCliente(int _idCliente) { idCliente = _idCliente; }
    void setLegajoVendedor(int _legajoVendedor) { legajoVendedor = _legajoVendedor; }
    void setTotal(double _total) { total = _total; }
    void setFechaVenta(Fecha _fechaVenta) { fechaVenta = _fechaVenta; }

    // Getters
    int getIdVenta() const { return idVenta; }
    int getIdCliente() const { return idCliente; }
    int getLegajoVendedor() const { return legajoVendedor; }
    double getTotal() const { return total; }
};

#endif
