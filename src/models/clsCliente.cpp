#include <iostream>

using namespace std;

#include "clsCliente.h"
#include "archivoManager.h"
#include "utilidades.h"
#include "ContextoGestores.h"
#include "uiManager.h"
#include "artworks.h"
#include "constantes.h"

#define byte windows_byte
#include "rlutil.h"
#undef byte

static ArchivoManager<Cliente> archivo("clientes.dat");

void Cliente::cargar() {
    string datos[CLIENTE_OPCIONES_CARGA] = {
                "NOMBRE: [                                ]",
                "TELEFONO: [                 ]"             ,
                "ID: [          ]"                          };

    agregar("A G R E G A R  C L I E N T E", CLIENTE_INICIO_TITULO, CLIENTE_OPCIONES_CARGA-1);
    agregar_opciones(datos, CLIENTE_INICIO_TABLA, CLIENTE_OPCIONES_CARGA, datos[CLIENTE_OPCIONES_CARGA-1], 75);

    rlutil::setColor(rlutil::RED);
    rlutil::locate(68, 10);
    cout << "MINIMO 10 NUMEROS";

    rlutil::setColor(rlutil::MAGENTA);
    rlutil::showcursor();

    ContextoGestores contexto;
    int cantidad = contexto.gestorC.cantidadRegistros();
    setID(cantidad + 1);
    rlutil::locate(81, 8); /// ID
    cout << id;


    vector<Cliente> clientes;
    archivo.leer(clientes);
    bool valido = false;

    while(!valido) {
        rlutil::locate(42, 8);  /// NOMBRE
        cargarCadena(nombre, MAX_NOMBRE);
        toUpperCase(nombre);

        size_t can = strlen(nombre);
        valido = true;

        for(size_t x = 0; x < can; x++) {
            int letra = static_cast<int>(nombre[x]);
            if(!((letra >= 'A' && letra <= 'Z') || letra == ' ')) {
                valido = false;
                break;
            }
        }

        if (!valido) {
            rlutil::setColor(rlutil::RED);
            rlutil::locate(52, 16);
            cout << "ERROR: SOLO LETRAS";

            rlutil::setColor(rlutil::MAGENTA);
            rlutil::locate(42, 8);
            cout << "                              ";
        }
    }
    limpiar_linea(52, 16);

    valido = false;

    while(!valido) {
        rlutil::locate(44, 10); /// TELEFONO
        cargarCadena(telefono, MAX_TELEFONO);

        size_t registros = clientes.size();

        size_t can = strlen(telefono);
        valido = true;

        if(can < 10) {
            rlutil::setColor(rlutil::RED);
            limpiar_linea(47, 16);
            rlutil::locate(49, 16);
            cout << "ERROR: MINIMO 10 NUMEROS";
            valido = false;
        }

        else {
            for(size_t x = 0; x < can; x++) {
                if(!(telefono[x] >= '0' && telefono[x] <= '9')) {
                    rlutil::setColor(rlutil::RED);
                    limpiar_linea(47, 16);
                    rlutil::locate(52, 16);
                    cout << "ERROR: SOLO NUMEROS";
                    valido = false;
                    break;
                }
            }
        }

        for(size_t x = 0; x < registros; x++) {
            if(strcmp(clientes[x].getTelefono(), telefono) == 0) {
                rlutil::setColor(rlutil::RED);
                limpiar_linea(47, 16);
                rlutil::locate(47, 16);
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
    limpiar_linea(47, 16);

    rlutil::setColor(rlutil::WHITE);
    rlutil::locate(47, 16);
    cout << "CLIENTE AGREGADO EXITOSAMENTE";

    rlutil::hidecursor();
}

void Cliente::mostrar() const {
    string datos_titulo[CLIENTE_OPCIONES_CARGA] = {
                            "    ID    ",
                            "          N O M B R E           ",
                            "    TELEFONO     "
                            };

    size_t datos_espacios[CLIENTE_OPCIONES_CARGA] = {10, 32, 17};

    rlutil::locate(50, 1);
    rlutil::setColor(rlutil::MAGENTA);
    cout << "CANTIDAD DE CLIENTES: " << archivo.cantidadRegistros();

    mostrarRegistros(archivo, datos_titulo, datos_espacios, CLIENTE_CURSOR_START_X, CLIENTE_CURSOR_START_Y, CLIENTE_PAGINADO, CLIENTE_OPCIONES_CARGA, 1);
}

void Cliente::mostrarFila(int posX, int posY) const {
    rlutil::locate(posX, posY);
    cout << char(186) << "          " /// ID
                    << char(186) << "                                " /// NOMBRE
                    << char(186) << "                 " /// TELEFONO
                    << char(186);

    rlutil::locate(posX, posY);
    cout << char(186);
    rlutil::setColor(rlutil::WHITE);
    rlutil::locate(32, posY); cout << id;
    rlutil::locate(43, posY); cout << getNombre();
    rlutil::locate(76, posY); cout << getTelefono();

    rlutil::setColor(rlutil::MAGENTA);
}

void Cliente::modificar() {
    string datos[CLIENTE_OPCIONES_CARGA] = {
            "NOMBRE: [                                ]",
            "TELEFONO: [                 ]"             ,
            "ID: [          ]"  };

    rlutil::setColor(rlutil::MAGENTA);

    agregar("M O D I F I C A R  C L I E N T E", CLIENTE_INICIO_TITULO, CLIENTE_OPCIONES_CARGA-1);
    agregar_opciones(datos, CLIENTE_INICIO_TABLA, CLIENTE_OPCIONES_CARGA, datos[CLIENTE_OPCIONES_CARGA-2], 75);

    rlutil::setColor(rlutil::RED);
    rlutil::locate(68, 10);
    cout << "MINIMO 10 NUMEROS";

    rlutil::setColor(rlutil::MAGENTA);
    rlutil::showcursor();

    string valoresActuales[2] = {nombre, telefono};
    mostrarPlaceholdersActuales(valoresActuales, 2, 32, CLIENTE_INICIO_TABLA, 2);

    rlutil::locate(81, 8); /// ID
    cout << id;


    vector<Cliente> clientes;
    archivo.leer(clientes);
    bool valido = false;

    while(!valido) {
        rlutil::locate(42, 8); /// NOMBRE
        cargarCadenaConValor(nombre, MAX_NOMBRE);
        toUpperCase(nombre);

        size_t can = strlen(nombre);
        valido = true;

        for(size_t x = 0; x < can; x++) {
            int letra = static_cast<int>(nombre[x]);
            if(!((letra >= 'A' && letra <= 'Z') || letra == ' ')) {
                valido = false;
                break;
            }
        }

        if (!valido) {
            rlutil::setColor(rlutil::RED);
            rlutil::locate(52, 16);
            cout << "ERROR: SOLO LETRAS";

            rlutil::setColor(rlutil::MAGENTA);
            rlutil::locate(42, 8);
            cout << "                              ";
        }
    }
    limpiar_linea(52, 16);

    valido = false;

    while(!valido) {
        rlutil::locate(44, 10); /// TELEFONO
        cargarCadenaConValor(telefono, MAX_TELEFONO);

        size_t registros = clientes.size();

        size_t can = strlen(telefono);
        valido = true;

        if(can < 10) {
            rlutil::setColor(rlutil::RED);
            limpiar_linea(47, 16);
            rlutil::locate(49, 16);
            cout << "ERROR: MINIMO 10 NUMEROS";
            valido = false;
        }

        else {
            for(size_t x = 0; x < can; x++) {
                if(!(telefono[x] >= '0' && telefono[x] <= '9')) {
                    rlutil::setColor(rlutil::RED);
                    limpiar_linea(47, 16);
                    rlutil::locate(52, 16);
                    cout << "ERROR: SOLO NUMEROS";
                    valido = false;
                    break;
                }
            }
        }

        for(size_t x = 0; x < registros; x++) {
            if(strcmp(clientes[x].getTelefono(), telefono) == 0 && clientes[x].getID() != id) {
                rlutil::setColor(rlutil::RED);
                limpiar_linea(47, 16);
                rlutil::locate(47, 16);
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
    limpiar_linea(47, 16);

    rlutil::setColor(rlutil::WHITE);
    rlutil::locate(46, 16);
    cout << "CLIENTE MODIFICADO EXITOSAMENTE";

    rlutil::hidecursor();
}
