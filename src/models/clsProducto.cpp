#include <iostream>
#include <iomanip>

using namespace std;

#include "clsProducto.h"
#include "archivoManager.h"
#include "utilidades.h"
#include "ContextoGestores.h"
#include "uiManager.h"
#include "artworks.h"

#define byte windows_byte
#include "rlutil.h"
#undef byte

const size_t OPCIONES = 7;
const int INICIO_TITULO = 3;
const int INICIO_TABLA = INICIO_TITULO + 5;
const int CURSOR_START_X = 3;
const int CURSOR_START_Y = 4;
const int PAGINADO = 15;
static ArchivoManager<Producto> archivo("productos.dat");

void Producto::cargar() {
    string datos[OPCIONES-1] = {
                "NOMBRE: [                                ]",
                "TIPO: [   ]"                               ,
                "STOCK: [           ]"                      ,
                "PRECIO: [                 ]"               ,
                "FECHA: [ __/__/____ ]"                     ,
                "ID: [          ]"                          };

    agregar("A G R E G A R  P R O D U C T O", INICIO_TITULO, OPCIONES-2);
    agregar_opciones(datos, INICIO_TABLA, OPCIONES-1, datos[OPCIONES-2]);

    rlutil::setColor(rlutil::RED);
    rlutil::locate(47, 10);
    cout << "'A' PARA PERIFERICO - 'B' PARA COMPONENTE";

    rlutil::locate(54, 16);
    cout << "FECHA ACEPTADA: dd/mm/aaaa o d/m/aaaa";

    rlutil::setColor(rlutil::MAGENTA);
    rlutil::showcursor();



    ContextoGestores contexto;
    int cantidad = contexto.gestorP.cantidadRegistros();
    setID(cantidad + 1);
    rlutil::locate(81, 8); /// ID
    cout << id;



    bool repetido = true;

    while(repetido) {
        rlutil::locate(42, 8); /// NOMBRE
        cargarCadena(nombre, 31);
        toUpperCase(nombre);

        vector<Producto> productos;
        archivo.leer(productos);
        size_t can = productos.size();

        repetido = false;
        
        for(size_t x = 0; x < can; x++) {
            if(strcmp(productos[x].getNombre(), nombre) == 0) {
                repetido = true;
                break;
            }
        }

        if(repetido) {
            rlutil::setColor(rlutil::RED);
            rlutil::locate(48, 22);
            cout << "ERROR: NOMBRE YA EXISTENTE";

            rlutil::setColor(rlutil::MAGENTA);
            rlutil::locate(42, 8);
            cout << "                              ";
        }
    }
    limpiar_linea(43, 22);



    rlutil::locate(40, 10); /// TIPO
    cargarCadena(&tipo, 2);
    toUpperCase(&tipo);

    while(tipo != 'A' && tipo != 'B'){
        rlutil::setColor(rlutil::RED);
        rlutil::locate(49, 22);
        cout << "ERROR: ESCRIBA 'A' O 'B'";

        rlutil::setColor(rlutil::MAGENTA);
        rlutil::locate(40, 10);
        cout << " ";
        rlutil::locate(40, 10);

        cargarCadena(&tipo, 2);
        toUpperCase(&tipo);
    }
    limpiar_linea(43, 22);



    rlutil::locate(41, 12); /// STOCK
    stock = cargarInt(9);

    while(stock <= 0) {
        rlutil::setColor(rlutil::RED);
        rlutil::locate(43, 22);
        cout << "ERROR: ESCRIBA UNA CANTIDAD MAYOR A 0";

        rlutil::setColor(rlutil::MAGENTA);
        rlutil::locate(41, 12);
        cout << "         ";
        rlutil::locate(41, 12);

        stock = cargarInt(9);
    }
    limpiar_linea(43, 22);



    rlutil::locate(42, 14); /// PRECIO
    precio = cargarDouble(15, 2);

    while(precio <= 0) {
        rlutil::setColor(rlutil::RED);
        rlutil::locate(44, 22);
        cout << "ERROR: ESCRIBA UN PRECIO MAYOR A 0";

        rlutil::setColor(rlutil::MAGENTA);
        rlutil::locate(42, 14);
        cout << "               ";
        rlutil::locate(42, 14);

        precio = cargarDouble(15, 2);
    }
    limpiar_linea(43, 22);



    rlutil::locate(41, 16); /// DIA
    fechaIngreso.setDia();

    while (fechaIngreso.getDia() < 1 || fechaIngreso.getDia() > 31) {
        rlutil::setColor(rlutil::RED);
        rlutil::locate(45, 22);
        cout << "ERROR: ESCRIBA DIA ENTRE 01 A 31";

        rlutil::locate(41, 16);
        rlutil::setColor(rlutil::GREY);
        cout << "__";
        rlutil::locate(41, 16);
        rlutil::setColor(rlutil::MAGENTA);
        fechaIngreso.setDia();
    }
    limpiar_linea(43, 22);



    rlutil::locate(44, 16); /// MES
    fechaIngreso.setMes();
    while (fechaIngreso.getMes() < 1 || fechaIngreso.getMes() > 12) {
        rlutil::setColor(rlutil::RED);
        rlutil::locate(45, 22);
        cout << "ERROR: ESCRIBA MES ENTRE 01 A 12";

        rlutil::locate(44, 16);
        rlutil::setColor(rlutil::GREY);
        cout << "__";
        rlutil::locate(44, 16);
        rlutil::setColor(rlutil::MAGENTA);
        fechaIngreso.setMes();
    }
    limpiar_linea(43, 22);



    rlutil::locate(47, 16); /// ANIO
    fechaIngreso.setAnio();
    while (fechaIngreso.getAnio() < 1) {
        rlutil::setColor(rlutil::RED);
        rlutil::locate(45, 22);
        cout << "ERROR: ESCRIBA UN ANIO MAYOR A 0";

        rlutil::locate(47, 16);
        rlutil::setColor(rlutil::GREY);
        cout << "____";
        rlutil::locate(47, 16);
        rlutil::setColor(rlutil::MAGENTA);
        fechaIngreso.setAnio();
    }
    limpiar_linea(43, 22);



    rlutil::setColor(rlutil::WHITE);
    rlutil::locate(46, 22);
    cout << "PRODUCTO AGREGADO EXITOSAMENTE";

    rlutil::hidecursor();
}


void Producto::mostrar() const {
    string datos_titulo[OPCIONES] = {
                            "    ID    ",
                            "          N O M B R E           ",
                            "    TIPO    ",
                            "   STOCK   ",
                            "       PRECIO       ",
                            "   FECHA    ",
                            "  ESTADO  "
                            };

    size_t datos_espacios[OPCIONES] = {10, 32, 12, 11, 20, 12, 10};

    rlutil::locate(50, 1);
    rlutil::setColor(rlutil::MAGENTA);
    cout << "CANTIDAD DE PRODUCTOS: " << archivo.cantidadRegistros();
    rlutil::locate(46, 2);
    cout << "CANTIDAD DE PRODUCTOS ACTIVOS: " << archivo.cantidadRegistrosActivos();

    mostrarRegistros(archivo, datos_titulo, datos_espacios, CURSOR_START_X, CURSOR_START_Y, PAGINADO, OPCIONES, 1); /// AGREGAR
}

void Producto::mostrar_activos() const {
    string datos_titulo[OPCIONES] = {
                            "    ID    ",
                            "          N O M B R E           ",
                            "    TIPO    ",
                            "   STOCK   ",
                            "       PRECIO       ",
                            "   FECHA    ",
                            "  ESTADO  "
                            };

    size_t datos_espacios[OPCIONES] = {10, 32, 12, 11, 20, 12, 10};

    rlutil::locate(50, 1);
    rlutil::setColor(rlutil::MAGENTA);
    cout << "CANTIDAD DE PRODUCTOS: " << archivo.cantidadRegistros();
    rlutil::locate(46, 2);
    cout << "CANTIDAD DE PRODUCTOS ACTIVOS: " << archivo.cantidadRegistrosActivos();

    mostrarRegistros(archivo, datos_titulo, datos_espacios, CURSOR_START_X, CURSOR_START_Y, PAGINADO, OPCIONES, 0); /// ELIMINAR
}



void Producto::mostrarFila(int posX, int posY) const {
    rlutil::locate(posX, posY);
    cout << char(186) << "          " /// ID
                    << char(186) << "                                " /// NOMBRE
                    << char(186) << "            " /// TIPO
                    << char(186) << "           " /// STOCK
                    << char(186) << "                    " /// PRECIO
                    << char(186) << "   /  /     " /// FECHA
                    << char(186) << "          " /// ESTADO
                    << char(186);

    rlutil::locate(posX, posY);
    cout << char(186);
    rlutil::setColor(rlutil::WHITE);
    rlutil::locate(5, posY); cout << id;
    rlutil::locate(16, posY); cout << getNombre();
    rlutil::locate(49, posY); cout << (getTipo() == 'A' ? "PERIFERICO" : "COMPONENTE");
    rlutil::locate(62, posY); cout << getStock();
    rlutil::locate(74, posY); cout << fixed << setprecision(2) << getPrecio();
    rlutil::locate(95, posY); getFecha().MostrarF();
    rlutil::locate(108, posY); cout << (getEstado() ? "ACTIVO" : "INACTIVO");

    rlutil::setColor(rlutil::MAGENTA);
}

void Producto::modificar() {
    string datos[OPCIONES-1] = {
                "NOMBRE: [                                ]",
                "TIPO: [   ]"                               ,
                "STOCK: [           ]"                      ,
                "PRECIO: [                 ]"               ,
                "FECHA: [ __/__/____ ]"                     ,
                "ID: [          ]"                          };

    agregar("M O D I F I C A R  P R O D U C T O", INICIO_TITULO, OPCIONES-2);
    agregar_opciones(datos, INICIO_TABLA, OPCIONES-1, datos[OPCIONES-2]);

    rlutil::setColor(rlutil::RED);
    rlutil::locate(47, 10);
    cout << "'A' PARA PERIFERICO - 'B' PARA COMPONENTE";

    rlutil::locate(54, 16);
    cout << "FECHA ACEPTADA: dd/mm/aaaa o d/m/aaaa";

    rlutil::setColor(rlutil::MAGENTA);
    rlutil::showcursor();

    // Mostrar datos ACTUALES como placeholders
    rlutil::locate(42, 8); /// NOMBRE
    cout << nombre;
    
    rlutil::locate(40, 10); /// TIPO
    cout << tipo;
    
    rlutil::locate(41, 12); /// STOCK
    cout << stock;
    
    rlutil::locate(42, 14); /// PRECIO
    cout << fixed << setprecision(2) << precio;
    
    rlutil::locate(81, 8); /// ID
    cout << id;



    bool repetido = true;

    while(repetido) {
        rlutil::locate(42, 8); /// NOMBRE
        cargarCadena(nombre, 31);
        toUpperCase(nombre);

        vector<Producto> productos;
        archivo.leer(productos);
        size_t can = productos.size();

        repetido = false;
        
        for(size_t x = 0; x < can; x++) {
            // NO REPETIR CON EL MISMO ID (es el que estamos modificando)
            if(strcmp(productos[x].getNombre(), nombre) == 0 && productos[x].getID() != id) {
                repetido = true;
                break;
            }
        }

        if(repetido) {
            rlutil::setColor(rlutil::RED);
            rlutil::locate(48, 22);
            cout << "ERROR: NOMBRE YA EXISTENTE";

            rlutil::setColor(rlutil::MAGENTA);
            rlutil::locate(42, 8);
            cout << "                                  ";
        }
    }
    limpiar_linea(43, 22);



    rlutil::locate(40, 10); /// TIPO
    cargarCadena(&tipo, 2);
    toUpperCase(&tipo);

    while(tipo != 'A' && tipo != 'B'){
        rlutil::setColor(rlutil::RED);
        rlutil::locate(49, 22);
        cout << "ERROR: ESCRIBA 'A' O 'B'";

        rlutil::setColor(rlutil::MAGENTA);
        rlutil::locate(40, 10);
        cout << " ";
        rlutil::locate(40, 10);

        cargarCadena(&tipo, 2);
        toUpperCase(&tipo);
    }
    limpiar_linea(43, 22);



    rlutil::locate(41, 12); /// STOCK
    stock = cargarInt(9);

    while(stock <= 0) {
        rlutil::setColor(rlutil::RED);
        rlutil::locate(43, 22);
        cout << "ERROR: ESCRIBA UNA CANTIDAD MAYOR A 0";

        rlutil::setColor(rlutil::MAGENTA);
        rlutil::locate(41, 12);
        cout << "         ";
        rlutil::locate(41, 12);

        stock = cargarInt(9);
    }
    limpiar_linea(43, 22);



    rlutil::locate(42, 14); /// PRECIO
    precio = cargarDouble(15, 2);

    while(precio <= 0) {
        rlutil::setColor(rlutil::RED);
        rlutil::locate(44, 22);
        cout << "ERROR: ESCRIBA UN PRECIO MAYOR A 0";

        rlutil::setColor(rlutil::MAGENTA);
        rlutil::locate(42, 14);
        cout << "               ";
        rlutil::locate(42, 14);

        precio = cargarDouble(15, 2);
    }
    limpiar_linea(43, 22);



    rlutil::locate(41, 16); /// DIA
    fechaIngreso.setDia();

    while (fechaIngreso.getDia() < 1 || fechaIngreso.getDia() > 31) {
        rlutil::setColor(rlutil::RED);
        rlutil::locate(45, 22);
        cout << "ERROR: ESCRIBA DIA ENTRE 01 A 31";

        rlutil::locate(41, 16);
        rlutil::setColor(rlutil::GREY);
        cout << "__";
        rlutil::locate(41, 16);
        rlutil::setColor(rlutil::MAGENTA);
        fechaIngreso.setDia();
    }
    limpiar_linea(43, 22);



    rlutil::locate(44, 16); /// MES
    fechaIngreso.setMes();
    while (fechaIngreso.getMes() < 1 || fechaIngreso.getMes() > 12) {
        rlutil::setColor(rlutil::RED);
        rlutil::locate(45, 22);
        cout << "ERROR: ESCRIBA MES ENTRE 01 A 12";

        rlutil::locate(44, 16);
        rlutil::setColor(rlutil::GREY);
        cout << "__";
        rlutil::locate(44, 16);
        rlutil::setColor(rlutil::MAGENTA);
        fechaIngreso.setMes();
    }
    limpiar_linea(43, 22);



    rlutil::locate(47, 16); /// ANIO
    fechaIngreso.setAnio();
    while (fechaIngreso.getAnio() < 1) {
        rlutil::setColor(rlutil::RED);
        rlutil::locate(45, 22);
        cout << "ERROR: ESCRIBA UN ANIO MAYOR A 0";

        rlutil::locate(47, 16);
        rlutil::setColor(rlutil::GREY);
        cout << "____";
        rlutil::locate(47, 16);
        rlutil::setColor(rlutil::MAGENTA);
        fechaIngreso.setAnio();
    }
    limpiar_linea(43, 22);



    rlutil::setColor(rlutil::WHITE);
    rlutil::locate(46, 22);
    cout << "PRODUCTO MODIFICADO EXITOSAMENTE";

    rlutil::hidecursor();
    estado = true;
}