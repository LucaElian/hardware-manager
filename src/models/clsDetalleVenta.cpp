#include "clsDetalleVenta.h"
#include <iostream>     // Para std::cout, std::endl
#include <iomanip>      // Para std::fixed, std::setprecision

#include "constantes.h"

// Hack para rlutil en Windows
#define byte windows_byte
#include "rlutil.h"
#undef byte

// Constructor
DetalleVenta::DetalleVenta(int _id,
                         int _idVenta,
                         int _idProducto,
                         int _cantidad,
                         double _precioVenta,
                         double _subtotal,
                         bool _estado,
                         Fecha _fecha)
    : Entidad(_id, _estado, _fecha) // Lista de inicialización
{
    // Cuerpo del constructor
    idVenta = _idVenta;
    idProducto = _idProducto;
    cantidad = _cantidad;
    precioVenta = _precioVenta;
    subtotal = _subtotal;
}

// Destructor
DetalleVenta::~DetalleVenta() {}

// --- Implementacion con los metodos virtuales ---

void DetalleVenta::cargar() {
    // Implementación vacía
}

void DetalleVenta::mostrar() const {
    std::cout << "Detalle de Venta " << id << std::endl;
    std::cout << "ID Venta: " << idVenta << std::endl;
    std::cout << "ID Producto: " << idProducto << std::endl;
    std::cout << "Cantidad: " << cantidad << std::endl;
    std::cout << "Precio: $" << precioVenta << std::endl;
    std::cout << "Subtotal: $" << subtotal << std::endl;
}

void DetalleVenta::mostrarFila(int posX, int posY) const {
    rlutil::locate(posX, posY);
    // Estructura (7 campos) - Tipeado a mano para evitar "Encoding Changed"
    std::cout << char(ASCII_BARRA_VERTICAL) << "          " // ID (10)
              << char(ASCII_BARRA_VERTICAL) << "          " // ID VENTA (10)
              << char(ASCII_BARRA_VERTICAL) << "          " // ID PROD (10)
              << char(ASCII_BARRA_VERTICAL) << "        "   // CANT (8)
              << char(ASCII_BARRA_VERTICAL) << "               " // PRECIO (15)
              << char(ASCII_BARRA_VERTICAL) << "               " // SUBTOTAL (15)
              << char(ASCII_BARRA_VERTICAL) << "          " // ESTADO (10)
              << char(ASCII_BARRA_VERTICAL);

    // Rellenar con datos
    // (Cambiado a MAGENTA para que coincida con tus otras tablas)
    rlutil::setColor(rlutil::WHITE);

    // (Alineado a la izquierda, como tus otras tablas)
    int currentX = posX;

    // Col 1: ID
    rlutil::locate(currentX + 1, posY); std::cout << getID();
    currentX += 10 + 1;

    // Col 2: ID VENTA
    rlutil::locate(currentX + 1, posY); std::cout << getIdVenta();
    currentX += 10 + 1;

    // Col 3: ID PROD
    rlutil::locate(currentX + 1, posY); std::cout << getIdProducto();
    currentX += 10 + 1;

    // Col 4: CANT
    rlutil::locate(currentX + 1, posY); std::cout << getCantidad();
    currentX += 8 + 1;

    // Col 5: PRECIO
    rlutil::locate(currentX + 1, posY); std::cout << std::fixed << std::setprecision(2) << getPrecioVenta();
    currentX += 15 + 1;

    // Col 6: SUBTOTAL
    rlutil::locate(currentX + 1, posY); std::cout << std::fixed << std::setprecision(2) << getSubtotal();
    currentX += 15 + 1;

    // Col 7: ESTADO
    rlutil::locate(currentX + 1, posY); std::cout << (getEstado() ? "ACTIVO" : "INACTIVO");
    currentX += 10;

   // Barra final
    rlutil::locate(currentX + 1, posY);
    rlutil::setColor(rlutil::MAGENTA); // Barrita VIOLETA
    std::cout << (char)ASCII_BARRA_VERTICAL; // ║

    rlutil::setColor(rlutil::MAGENTA); // Resetea el color
}

// --- Setters ---

void DetalleVenta::setIdVenta(int _idVenta) {
    idVenta = _idVenta;
}
void DetalleVenta::setIdProducto(int _idProducto) {
    idProducto = _idProducto;
}
void DetalleVenta::setCantidad(int _cantidad) {
    cantidad = _cantidad;
}
void DetalleVenta::setPrecioVenta(double _precioVenta) {
    precioVenta = _precioVenta;
}
void DetalleVenta::setSubtotal(double _subtotal) {
    subtotal = _subtotal;
}

// --- Getters ---

int DetalleVenta::getIdVenta() const {
    return idVenta;
}
int DetalleVenta::getIdProducto() const {
    return idProducto;
}
int DetalleVenta::getCantidad() const {
    return cantidad;
}
double DetalleVenta::getPrecioVenta() const {
    return precioVenta;
}
double DetalleVenta::getSubtotal() const {
    return subtotal;
}
