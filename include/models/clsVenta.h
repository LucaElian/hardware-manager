#ifndef CLSVENTA_H
#define CLSVENTA_H

#include "clsEntidad.h"
#include <ctime>

class Venta : public Entidad{
private:
    int idVenta;
    int idCliente;
    int legajoVendedor;
    double total;
    Fecha fechaVenta;

    //UI
    static constexpr size_t OPCIONES = 6;
    static constexpr int INICIO_TITULO = 3;
    static constexpr int INICIO_TABLA = INICIO_TITULO + 5;
    static constexpr int CURSOR_START_X = 9;
    static constexpr int CURSOR_START_Y = 4;
    static constexpr int PAGINADO = 15;

public:
    // Constructor (solo declaración, valores por defecto van aquí)
    Venta(int _id = 0,
        int _idVenta = 0,
        int _idCliente = 0,
        int _legajoVendedor = 0,
        double _total = 0.0,
        bool _estado = true,
        Fecha _fechaVenta = Fecha());

    // Destructor
    ~Venta();

    // Metodos virtuales heredados
    void cargar() override;
    void mostrar() const override;
    void mostrarFila(int posX, int posY) const override;

    // Setters
    void setIdVenta(int _idVenta);
    void setIdCliente(int _idCliente);
    void setLegajoVendedor(int _legajoVendedor);
    void setTotal(double _total);
    void setFechaVenta(Fecha _fechaVenta);

    // Getters
    int getIdVenta() const;
    int getIdCliente() const;
    int getLegajoVendedor() const;
    double getTotal() const;
};

#endif // CLSVENTA_H