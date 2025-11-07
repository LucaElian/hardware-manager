#include "clsVenta.h"
#include <iostream>   // Para std::cout, std::endl
#include <iomanip>    // Para std::fixed, std::setprecision

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
    : Entidad(_id, _estado, _fechaVenta)  // 1. Inicializa la base con la fecha (puede ser 1/1/1)
{
    // 2. Setea los miembros normales
    idVenta = _idVenta;
    idCliente = _idCliente;
    legajoVendedor = _legajoVendedor;
    total = _total;

    // 3. ¡AQUÍ ESTÁ EL ARREGLO!
    // Revisa si la fecha que llegó es la default (1/1/1)
    if (_fechaVenta.getDia() == 1 && _fechaVenta.getMes() == 1 && _fechaVenta.getAnio() == 1) {

        // 4. Si era default, la pisa con la fecha actual del sistema
        time_t now = time(0);
        tm* ltm = localtime(&now);
        Fecha fechaActual(ltm->tm_mday, ltm->tm_mon + 1, 1900 + ltm->tm_year);

        this->fechaVenta = fechaActual; // Actualiza el miembro local
        setFecha(fechaActual.getDia(), fechaActual.getMes(), fechaActual.getAnio()); // Actualiza el miembro de la clase base (Entidad)

    } else {
        // 5. Si no era default, solo setea el miembro local
        this->fechaVenta = _fechaVenta;
    }
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

void Venta::mostrarFila(int posX, int posY) const {

    int currentX = posX;

    // Col 1: ID VENTA (Ancho 10)
    rlutil::locate(currentX, posY);
    rlutil::setColor(rlutil::MAGENTA); // Barrita VIOLETA
    std::cout << (char)186; // ║
    rlutil::setColor(rlutil::WHITE); // Data BLANCA
    rlutil::locate(currentX + 1, posY);
    std::cout << getIdVenta();
    currentX += 10 + 1; // Avanza 10 (ancho) + 1 (borde)

    // Col 2: ID CLIENTE (Ancho 12)
    rlutil::locate(currentX, posY);
    rlutil::setColor(rlutil::MAGENTA); // Barrita VIOLETA
    std::cout << (char)186; // ║
    rlutil::setColor(rlutil::WHITE); // Data BLANCA
    rlutil::locate(currentX + 1, posY);
    std::cout << getIdCliente();
    currentX += 12 + 1;

    // Col 3: L.VENDEDOR (Ancho 10)
    rlutil::locate(currentX, posY);
    rlutil::setColor(rlutil::MAGENTA); // Barrita VIOLETA
    std::cout << (char)186; // ║
    rlutil::setColor(rlutil::WHITE); // Data BLANCA
    rlutil::locate(currentX + 1, posY);
    std::cout << getLegajoVendedor();
    currentX += 10 + 1;

    // Col 4: TOTAL (Ancho 15)
    rlutil::locate(currentX, posY);
    rlutil::setColor(rlutil::MAGENTA); // Barrita VIOLETA
    std::cout << (char)186; // ║
    rlutil::setColor(rlutil::WHITE); // Data BLANCA
    rlutil::locate(currentX + 1, posY);
    std::cout << std::fixed << std::setprecision(2) << getTotal();
    currentX += 15 + 1;

    // Col 5: FECHA (Ancho 12)
    rlutil::locate(currentX, posY);
    rlutil::setColor(rlutil::MAGENTA); // Barrita VIOLETA
    std::cout << (char)186; // ║
    rlutil::setColor(rlutil::WHITE); // Data BLANCA
    rlutil::locate(currentX + 1, posY);
    getFecha().MostrarF();
    currentX += 12 + 1;

    // Col 6: ESTADO (Ancho 10)
    rlutil::locate(currentX, posY);
    rlutil::setColor(rlutil::MAGENTA); // Barrita VIOLETA
    std::cout << (char)186; // ║
    rlutil::setColor(rlutil::WHITE); // Data BLANCA
    rlutil::locate(currentX + 1, posY);
    std::cout << (getEstado() ? "ACTIVO" : "INACTIVO");
    currentX += 10; // Avanza el último ancho (sin borde)

    // Barra final
    rlutil::locate(currentX + 1, posY);
    rlutil::setColor(rlutil::MAGENTA); // Barrita VIOLETA
    std::cout << (char)186; // ║

    rlutil::setColor(rlutil::MAGENTA); // Resetea el color
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