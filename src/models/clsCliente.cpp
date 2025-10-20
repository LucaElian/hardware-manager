#include <iostream>
#include "clsCliente.h"
#include "utilidades.h"
#include "ContextoGestores.h"

void Cliente::cargar() {
    string datos[3] = {
                    "NOMBRE: [                                ]",
                    "TELEFONO: [                 ]",
                    "ID: [          ]"
                    };

    agregar("A G R E G A R  C L I E N T E", 3, 2);
    agregar_opciones(datos, 8, 3, datos[2]);

    rlutil::setColor(rlutil::GREEN);
    rlutil::showcursor();

    ContextoGestores contexto;
    int cantidad = contexto.gestorC.cantidadRegistros();
    setID(cantidad + 1);
    rlutil::locate(81, 8);
    cout << id;

    rlutil::locate(42, 8);
    cargarCadena(nombre, 31);

    while (true){
        bool cor = true;
        for (int x = 0; nombre[x] != '\0'; x++){
            if (!isalpha(nombre[x]) && nombre[x] != ' ') cor = false;
        }
        if (!cor) {
            rlutil::setColor(rlutil::RED);
            rlutil::locate(49, 16);
            cout << "ERROR: ESCRIBA SOLO LETRAS";

            rlutil::setColor(rlutil::GREEN);
            rlutil::locate(42, 8);
            cout << "                              ";
            rlutil::locate(42, 8);

            cargarCadena(nombre, 31);
        }
        else break;
    }
    rlutil::locate(49, 16);
    cout << "                          ";
    toUpperCase(nombre);

    rlutil::locate(44, 10);
    cargarCadena(telefono, 16);

    /// ERROR DE INGRESAR LETRAS
    while (true){
        bool cor = true;
        for (int x = 0; telefono[x] != '\0'; x++){
            if (!isdigit(telefono[x]) && telefono[x] != ' ') cor = false;
        }
        if (!cor) {
            rlutil::setColor(rlutil::RED);
            rlutil::locate(49, 16);
            cout << "ERROR: ESCRIBA SOLO NUMEROS";

            rlutil::setColor(rlutil::GREEN);
            rlutil::locate(44, 10);
            cout << "               ";
            rlutil::locate(44, 10);

            cargarCadena(telefono, 31);
        }
        else break;
    }


    rlutil::locate(49, 16);
    cout << "                        ";

    rlutil::setColor(rlutil::WHITE);
    rlutil::locate(47,16);
    cout << "CLIENTE AGREGADO EXITOSAMENTE";

    rlutil::hidecursor();
}

void Cliente::mostrar() const {
    cout << "-------------------- CLIENTE " << id << " ----------------------" << endl;
    cout << "Nombre: " << nombre << endl;
    cout << "Telefono: " << telefono << endl;
    cout << endl;
}
