#ifndef CLSVENTA_H
#define CLSVENTA_H

#include <iostream>
#include <iomanip>
#define byte windows_byte
#include "rlutil.h"
#undef byte

#include "clsEntidad.h"
#include "clsFecha.h"

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
    void mostrar() const override {
        std::cout << "Venta #" << idVenta << std::endl;
        std::cout << "Cliente: " << idCliente << std::endl;
        std::cout << "Vendedor: " << legajoVendedor << std::endl;
        std::cout << "Total: $" << total << std::endl;
        std::cout << "Fecha: ";
        fechaVenta.MostrarF();
        std::cout << std::endl;
    }

    // GEMINI ME DIJO DE REEMPLAZAR ASI:
void mostrarFila(int posX, int posY) const override {
    rlutil::locate(posX, posY);
    // Estructura de la fila (7 campos)
    std::cout << char(186) << "          " // ID VENTA
              << char(186) << "            " // ID CLIENTE
              << char(186) << "            " // LEGAJO VEND
              << char(186) << "               " // TOTAL
              << char(186) << "            " // FECHA
              << char(186) << "          " // ESTADO
              << char(186);

    // Rellenar con datos
    rlutil::setColor(rlutil::WHITE);
    // Ajusta estos 'posX + X' si las columnas no coinciden
    rlutil::locate(posX + 2, posY); std::cout << getID();
    rlutil::locate(posX + 12, posY); std::cout << getIdVenta();
    rlutil::locate(posX + 24, posY); std::cout << getIdCliente();
    rlutil::locate(posX + 38, posY); std::cout << getLegajoVendedor();
    rlutil::locate(posX + 52, posY); std::cout << std::fixed << std::setprecision(2) << getTotal();
    rlutil::locate(posX + 68, posY); getFecha().MostrarF(); // Usa getFecha() de Entidad
    rlutil::locate(posX + 81, posY); std::cout << (getEstado() ? "ACTIVO" : "INACTIVO");

    rlutil::setColor(rlutil::MAGENTA);
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
