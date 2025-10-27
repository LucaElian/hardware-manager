#ifndef CLSVENTA_H
#define CLSVENTA_H

// Solo se necesitan los includes para las declaraciones
#include "clsEntidad.h"
#include "clsFecha.h"

#include <ctime> // Para la fecha actual

class Venta : public Entidad {
private:
    int idVenta;
    int idCliente;
    int legajoVendedor;
    double total;
    Fecha fechaVenta; // Este miembro es redundante si ya lo tiene Entidad
public:
    // Constructor (solo declaración, valores por defecto van aquí)
    Venta(int _id = 0,
          int _idVenta = 0,
          int _idCliente = 0,
          int _legajoVendedor = 0,
          double _total = 0.0,
          bool _estado = true,
          Fecha _fechaVenta = Fecha(1,1,1));

    // Destructor (solo declaración)
    ~Venta();

    // Implementing pure virtual functions (solo declaración)
    void cargar() override;
    void mostrar() const override;
    void mostrarFila(int posX, int posY) const override;

    // Setters (solo declaración)
    void setIdVenta(int _idVenta);
    void setIdCliente(int _idCliente);
    void setLegajoVendedor(int _legajoVendedor);
    void setTotal(double _total);
    void setFechaVenta(Fecha _fechaVenta);

    // Getters (solo declaración)
    int getIdVenta() const;
    int getIdCliente() const;
    int getLegajoVendedor() const;
    double getTotal() const;
};

#endif
