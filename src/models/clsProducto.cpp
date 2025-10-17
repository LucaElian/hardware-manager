#include <iostream>
#include <conio.h>
#include <iomanip>

using namespace std;

#include "clsProducto.h"
#include "utilidades.h"
#include "ContextoGestores.h"
#include "artworks.h"

#define byte windows_byte
#include "rlutil.h"
#undef byte

void Producto::cargar() {
    string datos[6] = {
                "NOMBRE: [                                ]",
                "TIPO: [   ]"                               ,
                "STOCK: [           ]"                      ,
                "PRECIO: [                 ]"               ,
                "FECHA: [ __/__/____ ]"                     ,
                "ID: [          ]"                          };

    agregar("A G R E G A R  P R O D U C T O", 3, 5);
    agregar_opciones(datos, 8, 6, datos[5]);

    rlutil::setColor(rlutil::RED);
    rlutil::locate(47, 10);
    cout << "'A' PARA PERIFERICO. 'B' PARA COMPONENTE.";

    rlutil::locate(54, 16);
    cout << "FECHA ACEPTADA: dd/mm/aaaa o d/m/aaaa";

    rlutil::setColor(rlutil::GREEN);
    rlutil::showcursor();

    ContextoGestores contexto;
    int cantidad = contexto.gestorP.cantidadRegistros();
    setID(cantidad + 1);
    rlutil::locate(81, 8); /// ID
    cout << id;

    rlutil::locate(42, 8); /// NOMBRE
    cargarCadena(nombre, 31);
    toUpperCase(nombre);

    rlutil::locate(40, 10); /// TIPO
    cargarCadena(&tipo, 2);
    toUpperCase(&tipo);
    while(tipo != 'A' && tipo != 'B'){
        rlutil::setColor(rlutil::RED);
        rlutil::locate(49, 22);
        cout << "ERROR: ESCRIBA 'A' O 'B'";

        rlutil::setColor(rlutil::GREEN);
        rlutil::locate(40, 10);
        cout << " ";
        rlutil::locate(40, 10);

        cargarCadena(&tipo, 2);
        toUpperCase(&tipo);
    }
    rlutil::locate(49, 22);
    cout << "                        ";

    rlutil::locate(41, 12); /// STOCK
    stock = cargarInt(9);

    rlutil::locate(42, 14); /// PRECIO
    precio = cargarDouble(15, 2);

    rlutil::locate(41, 16); /// DIA
    fechaIngreso.setDia();
    while (fechaIngreso.getDia() < 1 || fechaIngreso.getDia() > 31) {
        rlutil::setColor(rlutil::RED);
        rlutil::locate(49, 22);
        cout << "ERROR: ESCRIBA DIA ENTRE 01 A 31";

        rlutil::locate(41, 16);
        rlutil::setColor(rlutil::GREY);
        cout << "__";
        rlutil::locate(41, 16);
        rlutil::setColor(rlutil::GREEN);
        fechaIngreso.setDia();
    }
    rlutil::locate(49, 22);
    cout << "                                ";

    rlutil::locate(44, 16); /// MES
    fechaIngreso.setMes();
    while (fechaIngreso.getMes() < 1 || fechaIngreso.getMes() > 12) {
        rlutil::setColor(rlutil::RED);
        rlutil::locate(49, 22);
        cout << "ERROR: ESCRIBA MES ENTRE 01 A 12";

        rlutil::locate(44, 16);
        rlutil::setColor(rlutil::GREY);
        cout << "__";
        rlutil::locate(44, 16);
        rlutil::setColor(rlutil::GREEN);
        fechaIngreso.setMes();
    }
    rlutil::locate(49, 22);
    cout << "                                ";

    rlutil::locate(47, 16); /// ANIO
    fechaIngreso.setAnio();
    while (fechaIngreso.getAnio() < 1) {
        rlutil::setColor(rlutil::RED);
        rlutil::locate(49, 22);
        cout << "ERROR: ESCRIBA UN ANIO MAYOR A 0";

        rlutil::locate(47, 16);
        rlutil::setColor(rlutil::GREY);
        cout << "____";
        rlutil::locate(47, 16);
        rlutil::setColor(rlutil::GREEN);
        fechaIngreso.setAnio();
    }
    rlutil::locate(49, 22);
    cout << "                                ";

    rlutil::setColor(rlutil::WHITE);
    rlutil::locate(47,22);
    cout << "PRODUCTO AGREGADO EXITOSAMENTE";

    rlutil::hidecursor();
    rlutil::setColor(rlutil::BLACK);
}

void Producto::mostrar(int fila) {
    rlutil::setColor(rlutil::RED);

    rlutil::locate(3, 6+fila);
    cout << char(186) << "          " << /// ID
    char(186) << "                                " << /// NOMBRE
    char(186) << "            " << /// TIPO
    char(186) << "           " << /// STOCK
    char(186) << "                    " << /// PRECIO
    char(186) << "   /  /     " << /// FECHA
    char(186) << "          " << /// ESTADO
    char(186);

    rlutil::setColor(rlutil::WHITE);
    rlutil::locate(5, 6+fila);
    cout << id;

    rlutil::locate(16, 6+fila);
    cout << nombre;

    rlutil::locate(49, 6+fila);
    if(tipo == 'A') cout << "PERIFERICO";
    else if (tipo == 'B') cout << "COMPONENTE";

    rlutil::locate(62, 6+fila);
    cout << stock;

    rlutil::locate(74, 6+fila);
    cout << fixed << setprecision(2) << precio;

    rlutil::locate(95, 6+fila);
    fechaIngreso.MostrarF();

    rlutil::locate(108, 6+fila);
    cout << (estado ? "ACTIVO" : "INACTIVO");
}
