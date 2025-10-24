#include <iostream>

#include "clsVendedor.h"
#include "archivoManager.h"
#include "utilidades.h"
#include "ContextoGestores.h"
#include "uiManager.h"
#include "artworks.h"

#define byte windows_byte
#include "rlutil.h"
#undef byte

const int OPCIONES = 6;
const int INICIO_TITULO = 3;
const int INICIO_TABLA = INICIO_TITULO + 5;
const int CURSOR_START_X = 12; // 3
const int CURSOR_START_Y = 4;
const int PAGINADO = 15;
static ArchivoManager<Vendedor> archivo("vendedores.dat");

void Vendedor::cargar() {
    string datos[OPCIONES-1] = {
        "NOMBRE: [                                ]", 
        "TELEFONO: [                 ]"             , /// ERROR SIMBO/LET | 10 MIN | TEL REPETIDO | 
        "DNI: [          ]"                         , /// ERROR SIMBO/LET | NO COMPLETO | DNI REPETIDO |
        "FECHA: [ __/__/____ ]"                     , /// ERROR DIA 0 32 | MES 0 13 | ANIO 0  
        "ID: [          ]"                          };

    agregar("A G R E G A R  V E N D E D O R", INICIO_TITULO, OPCIONES-2);
    agregar_opciones(datos, INICIO_TABLA, OPCIONES-1, datos[OPCIONES-2]);

    rlutil::setColor(rlutil::RED);
    rlutil::locate(68, 10);
    cout << "MINIMO 10 NUMEROS";

    rlutil::locate(50, 12);
    cout << "AGREGAR CEROS ADELANTE SI FALTAN DIGITOS";

    rlutil::locate(54, 14);
    cout << "FECHA ACEPTADA: dd/mm/aaaa o d/m/aaaa";

    rlutil::setColor(rlutil::MAGENTA);
    rlutil::showcursor();



    ContextoGestores contexto;
    int cantidad = contexto.gestorV.cantidadRegistros();
    setLegajo(cantidad + 1); /// ID
    setID(cantidad + 1); // Asignar ID igual al legajo pq trabajamos con id a nivel codigo, no legajos
    rlutil::locate(81, 8);
    cout << legajo;



    bool valido = false;

    while(!valido) {
        rlutil::locate(42, 8); /// NOMBRE
        cargarCadena(nombre, 31);
        toUpperCase(nombre);

        int can = strlen(nombre);

        valido = true;

        for(int x = 0; x < can; x++) {
            int letra = static_cast<int>(nombre[x]);
            if(!((letra >= 'A' && letra <= 'Z') || letra == ' ')) {
                valido = false;
                break;
            }
        }

        if (!valido) {
            rlutil::setColor(rlutil::RED);
            rlutil::locate(52, 20);
            cout << "ERROR: SOLO LETRAS";

            rlutil::setColor(rlutil::MAGENTA);
            rlutil::locate(42, 8);
            cout << "                              ";
        }
    }
    limpiar_linea(47, 20);


    vector<Vendedor> vendedor;
    archivo.leer(vendedor);
    valido = false;

    while(!valido) {
        rlutil::locate(44, 10); /// TELEFONO
        cargarCadena(telefonoVendedor, 16);
        
        int registros = vendedor.size();

        int can = strlen(telefonoVendedor);
        valido = true;

        if(can < 10) {
            rlutil::setColor(rlutil::RED);
            limpiar_linea(47, 20);
            rlutil::locate(49, 20);
            cout << "ERROR: MINIMO 10 NUMEROS";
            valido = false;
        }

        else {
            for(int x = 0; x < can; x++) {
                if(!(telefonoVendedor[x] >= '0' && telefonoVendedor[x] <= '9')) {
                    rlutil::setColor(rlutil::RED);
                    limpiar_linea(47, 20);
                    rlutil::locate(52, 20);
                    cout << "ERROR: SOLO NUMEROS";
                    valido = false;
                    break;
                }
            }
        }

        for(int x = 0; x < registros; x++) {
            if(strcmp(vendedor[x].getTelefonoVendedor(), telefonoVendedor) == 0) {
                rlutil::setColor(rlutil::RED);
                limpiar_linea(47, 20);
                rlutil::locate(47, 20);
                cout << "ERROR: TELEFONO YA EXISTENTE";
                valido = false;
                break;
            }
        }

        if(!valido) {
            rlutil::setColor(rlutil::MAGENTA);
            rlutil::locate(44, 10);
            cout << "               ";
        }
    }
    limpiar_linea(47, 20);

    valido = false;

    while(!valido) {
        rlutil::locate(39, 12); /// DNI
        cargarCadena(dni, 9);
        
        int registros = vendedor.size();

        int can = strlen(dni);
        valido = true;

        if(can != 8) {
            rlutil::setColor(rlutil::RED);
            limpiar_linea(47, 20);
            rlutil::locate(49, 20);
            cout << "ERROR: INGRESAR 8 DIGITOS";
            valido = false;
        }

        else {
            for(int x = 0; x < can; x++) {
                if(!(dni[x] >= '0' && dni[x] <= '9')) {
                    rlutil::setColor(rlutil::RED);
                    limpiar_linea(47, 20);
                    rlutil::locate(52, 20);
                    cout << "ERROR: SOLO NUMEROS";
                    valido = false;
                    break;
                }
            }
        }

        for(int x = 0; x < registros; x++) {
            if(strcmp(vendedor[x].getDni(), dni) == 0) {
                rlutil::setColor(rlutil::RED);
                limpiar_linea(47, 20);
                rlutil::locate(50, 20);
                cout << "ERROR: DNI YA EXISTENTE";
                valido = false;
                break;
            }
        }

        if(!valido) {
            rlutil::setColor(rlutil::MAGENTA);
            rlutil::locate(39, 12);
            cout << "        ";
        }
    }
    limpiar_linea(47, 20);



    rlutil::locate(41, 14); /// DIA
    fechaIngreso.setDia();

    while (fechaIngreso.getDia() < 1 || fechaIngreso.getDia() > 31) {
        rlutil::setColor(rlutil::RED);
        rlutil::locate(45, 20);
        cout << "ERROR: ESCRIBA DIA ENTRE 01 A 31";

        rlutil::locate(41, 14);
        rlutil::setColor(rlutil::GREY);
        cout << "__";
        rlutil::locate(41, 14);
        rlutil::setColor(rlutil::MAGENTA);
        fechaIngreso.setDia();
    }
    limpiar_linea(45, 20);



    rlutil::locate(44, 14); /// MES
    fechaIngreso.setMes();
    while (fechaIngreso.getMes() < 1 || fechaIngreso.getMes() > 12) {
        rlutil::setColor(rlutil::RED);
        rlutil::locate(45, 20);
        cout << "ERROR: ESCRIBA MES ENTRE 01 A 12";

        rlutil::locate(44, 14);
        rlutil::setColor(rlutil::GREY);
        cout << "__";
        rlutil::locate(44, 14);
        rlutil::setColor(rlutil::MAGENTA);
        fechaIngreso.setMes();
    }
    limpiar_linea(45, 20);



    rlutil::locate(47, 14); /// ANIO
    fechaIngreso.setAnio();
    while (fechaIngreso.getAnio() < 1) {
        rlutil::setColor(rlutil::RED);
        rlutil::locate(45, 20);
        cout << "ERROR: ESCRIBA UN ANIO MAYOR A 0";

        rlutil::locate(47, 14);
        rlutil::setColor(rlutil::GREY);
        cout << "____";
        rlutil::locate(47, 14);
        rlutil::setColor(rlutil::MAGENTA);
        fechaIngreso.setAnio();
    }
    limpiar_linea(45, 20);



    rlutil::setColor(rlutil::WHITE);
    rlutil::locate(46, 20);
    cout << "VENDEDOR AGREGADO EXITOSAMENTE";

    rlutil::hidecursor();
}


void Vendedor::mostrar() const {
    string datos_titulo[OPCIONES] = {
                            "    ID    ",
                            "          N O M B R E           ",
                            "    TELEFONO     ",
                            "   DNI    ",
                            "   FECHA    ",
                            "  ESTADO  "
                            };

    int datos_espacios[OPCIONES] = {10, 32, 17, 10, 12, 10};

    rlutil::locate(50, 1);
    rlutil::setColor(rlutil::MAGENTA);
    cout << "CANTIDAD DE VENDEDORES: " << archivo.cantidadRegistros();
    rlutil::locate(46, 2);
    cout << "CANTIDAD DE VENDEDORES ACTIVOS: " << archivo.cantidadRegistrosActivos();

    mostrarRegistros(archivo, datos_titulo, datos_espacios, CURSOR_START_X, CURSOR_START_Y, PAGINADO, OPCIONES, 1);
}

void Vendedor::mostrar_activos() const {
    string datos_titulo[OPCIONES] = {
                            "    ID    ",
                            "          N O M B R E           ",
                            "    TELEFONO     ",
                            "   DNI    ",
                            "   FECHA    ",
                            "  ESTADO  "
                            };

    int datos_espacios[OPCIONES] = {10, 32, 17, 10, 12, 10};

    rlutil::locate(50, 1);
    rlutil::setColor(rlutil::MAGENTA);
    cout << "CANTIDAD DE PRODUCTOS: " << archivo.cantidadRegistros();
    rlutil::locate(46, 2);
    cout << "CANTIDAD DE PRODUCTOS ACTIVOS: " << archivo.cantidadRegistrosActivos();

    mostrarRegistros(archivo, datos_titulo, datos_espacios, CURSOR_START_X, CURSOR_START_Y, PAGINADO, OPCIONES, 0);
}



void Vendedor::mostrarFila(int posX, int posY) const {
    rlutil::locate(posX, posY);
    cout << char(186) << "          " /// ID / LEGAJO
                    << char(186) << "                                " /// NOMBRE
                    << char(186) << "                 " /// TELEFONO
                    << char(186) << "          " /// DNI
                    << char(186) << "   /  /     " /// FECHA
                    << char(186) << "          " /// ESTADO
                    << char(186);

    rlutil::locate(posX, posY);
    cout << char(186);
    rlutil::setColor(rlutil::WHITE);
    rlutil::locate(14, posY); cout << legajo;
    rlutil::locate(25, posY); cout << getNombre();
    rlutil::locate(58, posY); cout << getTelefonoVendedor();
    rlutil::locate(76, posY); cout << getDni();
    rlutil::locate(87, posY); getFecha().MostrarF();
    rlutil::locate(100, posY); cout << (getEstado() ? "ACTIVO" : "INACTIVO");

    rlutil::setColor(rlutil::MAGENTA);
}

