#ifndef PRODUCTOS_H_INCLUDED
#define PRODUCTOS_H_INCLUDED

class Producto{
    private:
        int id; /// ID UNICO
        std::string nombre;
        std::string tipo; /// MOUSE, TECLADO, PROCESADOR, ETC
        int precio;
        int stock;
        Fecha ingreso;
    public:
        Producto(std::string nombre, std::string tipos, int id, int stock, int precio, Fecha fecha);
        virtual ~Producto(){}

        std::string getNombre() const {return nombre;}
        std::string getTipo() const {return tipo;}
        int getId() const {return id;}
        int getPrecio() const {return precio;}
        int getStock() const {return stock;}
};

class Componente : public Producto {
public:
    Componente(std::string nombre, std::string tipo, int id, int stock, int precio, Fecha fecha)
    : Producto(nombre, tipo, id, stock, precio, fecha) {}
};

class Periferico : public Producto {
public:
    Periferico(std::string nombre, std::string tipo, int id, int stock, int precio, Fecha fecha)
    : Producto(nombre, tipo, id, stock, precio, fecha) {}
};

/// COMPONENTES
class Procesador : public Componente{}; /// VELOCIDAD, NUCLEOS, HILOS, SOCKET
class Mother : public Componente{}; /// SOCKET, SLOTS RAM, PUERTOS
class RAM : public Componente{}; /// CAPACIDAD, FRECUENCIA, TIPO
class Cooler : public Componente{}; /// TIPO, TAMAÑO, COMPATIBILIDAD
class Gabinete : public Componente{}; /// VENTILADORES, ESPACIO, TAMAÑO
class Disco : public Componente{}; /// CAPACIDAD, TIPO, INTERFAZ
class Fuente : public Componente{}; /// POTENCIA, CERTIFICACION, TIPO
class PlacaDeVideo : public Componente{}; /// MEMORIA VRAM, CHIPSET, CONSUMO

/// PERIFERICOS
class Mouse : public Periferico{}; /// DPI, ALAMBRICO/INALAMBRICO
class Monitor : public Periferico{}; /// PULGADAS, RESOLUCION, HZ
class Teclado : public Periferico{}; /// TIPO, IDIOMA, RGB
class Webcam : public Periferico{}; /// RESOLUCION, FPS, MICROFONO?
class Microfono : public Periferico{}; /// TIPO, CONEXION, SENSIBILIDAD
class Auricular : public Periferico{}; /// TIPO, ALAMBRICO/INALAMBRICO, MICROFONO?


#endif // PRODUCTOS_H_INCLUDED
