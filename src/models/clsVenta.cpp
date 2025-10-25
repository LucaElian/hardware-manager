#include "clsVenta.h"
#include <iostream>   // Para std::cout, std::endl
#include <iomanip>    // Para std::fixed, std::setprecision
#include "rlutil.h"   // Para rlutil::

// Hack de rlutil
#define byte windows_byte
#include "rlutil.h"
#undef byte

// Constructor
Venta::Venta(int _id,
             int _idVenta,
             int _idCliente,
             int _legajoVendedor,
             double _total,
             bool _estado,
             Fecha _fechaVenta)
    : Entidad(_id, _estado, _fechaVenta) // Pasa la fecha a la Entidad base
{
    // El cuerpo que tenías en el .h
    idVenta = _idVenta;
    idCliente = _idCliente;
    legajoVendedor = _legajoVendedor;
    total = _total;
    // Asignamos también a la variable local (aunque es redundante)
    this->fechaVenta = _fechaVenta;
}

// Destructor
Venta::~Venta() {}

// --- Implementing pure virtual functions ---

void Venta::cargar() {
    // Implementación vacía, como la tenías
}

void Venta::mostrar() const {
    std::cout << "Venta #" << idVenta << std::endl;
    std::cout << "Cliente: " << idCliente << std::endl;
    std::cout << "Vendedor: " << legajoVendedor << std::endl;
    std::cout << "Total: $" << total << std::endl;
    std::cout << "Fecha: ";
    getFecha().MostrarF(); // Usamos el getter de Entidad
    std::cout << std::endl;
}

// Esta es la versión corregida de mostrarFila que arreglamos
void Venta::mostrarFila(int posX, int posY) const {

    rlutil::setColor(rlutil::MAGENTA); // Color violeta
    int currentX = posX;

    // Col 1: ID VENTA (Ancho 10)
    rlutil::locate(currentX, posY);
    std::cout << (char)186; // ║
    rlutil::locate(currentX + 1, posY);
    std::cout << getIdVenta();
    currentX += 10 + 1; // Avanza 10 (ancho) + 1 (borde)

    // Col 2: ID CLIENTE (Ancho 12)
    rlutil::locate(currentX, posY);
    std::cout << (char)186; // ║
    rlutil::locate(currentX + 1, posY);
    std::cout << getIdCliente();
    currentX += 12 + 1;

    // Col 3: L.VENDEDOR (Ancho 10)
    rlutil::locate(currentX, posY);
    std::cout << (char)186; // ║
    rlutil::locate(currentX + 1, posY);
    std::cout << getLegajoVendedor();
    currentX += 10 + 1;

    // Col 4: TOTAL (Ancho 15)
    rlutil::locate(currentX, posY);
    std::cout << (char)186; // ║
    rlutil::locate(currentX + 1, posY);
    std::cout << std::fixed << std::setprecision(2) << getTotal();
    currentX += 15 + 1;

    // Col 5: FECHA (Ancho 12)
    rlutil::locate(currentX, posY);
    std::cout << (char)186; // ║
    rlutil::locate(currentX + 1, posY);
    getFecha().MostrarF(); // Usamos el getter de Entidad
    currentX += 12 + 1;

    // Col 6: ESTADO (Ancho 10)
    rlutil::locate(currentX, posY);
    std::cout << (char)186; // ║
    rlutil::locate(currentX + 1, posY);
    std::cout << (getEstado() ? "ACTIVO" : "INACTIVO");
    currentX += 10; // Avanza el último ancho (sin borde)

    // Barra final
    rlutil::locate(currentX + 1, posY);
    std::cout << (char)186; // ║

    rlutil::setColor(rlutil::MAGENTA);
}


// --- Setters ---

void Venta::setIdVenta(int _idVenta) {
    idVenta = _idVenta;
}
void Venta::setIdCliente(int _idCliente) {
    idCliente = _idCliente;
}
void Venta::setLegajoVendedor(int _legajoVendedor) {
    legajoVendedor = _legajoVendedor;
}
void Venta::setTotal(double _total) {
    total = _total;
}
void Venta::setFechaVenta(Fecha _fechaVenta) {
    fechaVenta = _fechaVenta;
    // Sincroniza también la fecha de la Entidad base
    setFecha(_fechaVenta.getDia(), _fechaVenta.getMes(), _fechaVenta.getAnio());
}

// --- Getters ---

int Venta::getIdVenta() const {
    return idVenta;
}
int Venta::getIdCliente() const {
    return idCliente;
}
int Venta::getLegajoVendedor() const {
    return legajoVendedor;
}
double Venta::getTotal() const {
    return total;
}
