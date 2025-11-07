#include <iostream>
using namespace std;

#include "artworks.h"
#include "utilidades.h"
#include "constantes.h"

#define byte windows_byte
#include "rlutil.h"
#undef byte

void titulo() {
    const string title[5] =
    {
        ",--.   ,--. ,------. ,--.   ,--. ,--.   ,--.  ",
        "|   `.'   | |  .---'  \\  `.'  /   \\  `.'  / ",
        "|  |'.'|  | |  `--,    .'    \\     .'    \\  ",
        "|  |   |  | |  `---.  /  .'.  \\   /  .'.  \\ ",
        "`--'   `--' `------' '--'   '--' '--'   '--'  "
    };

    rlutil::setColor(rlutil::MAGENTA);

    for(int x = 0; x < 5; x++) {
        rlutil::locate(40, 3+x);
        cout << title[x] << "\n";
    }
}

void menu(string title, string opciones[], int inicio, int can) {
    rlutil::setColor(rlutil::MAGENTA);
    rlutil::locate(40, inicio);
    cout << (char)ASCII_ESQUINA_IZQUIERDA;
    centrar_texto("", (char)ASCII_BARRA_HORIZONTAL, 41);
    cout << (char)ASCII_ESQUINA_DERECHA;

    rlutil::locate(40, inicio+1);
    cout << (char)ASCII_BARRA_VERTICAL;
    centrar_texto("", ' ', 41);
    cout << (char)ASCII_BARRA_VERTICAL;

    rlutil::locate(40, inicio+2);
    cout << (char)ASCII_BARRA_VERTICAL;
    rlutil::setColor(rlutil::WHITE);
    centrar_texto(title, ' ', 41);
    rlutil::setColor(rlutil::MAGENTA);
    cout << (char)ASCII_BARRA_VERTICAL;

    rlutil::locate(40, inicio+3);
    cout << (char)ASCII_BARRA_VERTICAL;
    centrar_texto("", ' ', 41);
    cout << (char)ASCII_BARRA_VERTICAL;

    rlutil::locate(40, inicio+4);
    cout << (char)ASCII_BARRA_EMPALME_DERECHA;
    centrar_texto("", (char)ASCII_BARRA_HORIZONTAL, 41);
    cout << (char)ASCII_BARRA_EMPALME_IZQUIERDA;

    rlutil::locate(40, inicio+5);
    cout << (char)ASCII_BARRA_VERTICAL;
    centrar_texto("", ' ', 41);
    cout << (char)ASCII_BARRA_VERTICAL;

    for(int x = 0; x < can; x++) {
        rlutil::locate(40, (inicio+6) + (x * 2));
        cout << (char)ASCII_BARRA_VERTICAL;
        rlutil::setColor(rlutil::WHITE);
        centrar_texto(opciones[x], ' ', 41);
        rlutil::setColor(rlutil::MAGENTA);
        cout << (char)ASCII_BARRA_VERTICAL;

        rlutil::locate(40, (inicio+6) + (x * 2) + 1);
        cout << (char)ASCII_BARRA_VERTICAL;
        centrar_texto("", ' ', 41);
        cout << (char)ASCII_BARRA_VERTICAL;
    }

    rlutil::locate(40, (inicio+6) + 2 * can);
    cout << (char)ASCII_BARRA_EMPALME_IZQUIERDA_INFERIOR;
    centrar_texto("", (char)ASCII_BARRA_HORIZONTAL, 41);
    cout << (char)ASCII_BARRA_ESQUINA_DERECHA_INFERIOR;
}

void agregar(string title, int inicio, int can) {
    rlutil::locate(30, inicio);
    cout << (char)ASCII_ESQUINA_IZQUIERDA;
    centrar_texto("", (char)ASCII_BARRA_HORIZONTAL, 61);
    cout << (char)ASCII_ESQUINA_DERECHA;

    rlutil::locate(30, inicio + 1);
    cout << (char)ASCII_BARRA_VERTICAL;
    centrar_texto("", ' ', 61);
    cout << (char)ASCII_BARRA_VERTICAL;

    rlutil::locate(30, inicio + 2);
    cout << (char)ASCII_BARRA_VERTICAL;
    rlutil::setColor(rlutil::WHITE);
    centrar_texto(title, ' ', 61);
    rlutil::setColor(rlutil::MAGENTA);
    cout << (char)ASCII_BARRA_VERTICAL;

    rlutil::locate(30, inicio + 3);
    cout << (char)ASCII_BARRA_VERTICAL;
    centrar_texto("", ' ', 61);
    cout << (char)ASCII_BARRA_VERTICAL;

    rlutil::locate(30, inicio + 4);
    cout << (char)ASCII_BARRA_EMPALME_DERECHA;
    centrar_texto("", (char)ASCII_BARRA_HORIZONTAL, 61);
    cout << (char)ASCII_BARRA_EMPALME_IZQUIERDA;

    for (int fila = inicio + 5; fila < inicio + 5 + (can * 2); fila++) {
        rlutil::locate(30, fila);
        cout << (char)ASCII_BARRA_VERTICAL;
        centrar_texto("", ' ', 61);
        cout << (char)ASCII_BARRA_VERTICAL;
    }

    rlutil::locate(30, inicio + 5 + (can * 2));
    cout << (char)ASCII_BARRA_EMPALME_IZQUIERDA_INFERIOR;
    centrar_texto("", (char)ASCII_BARRA_HORIZONTAL, 61);
    cout << (char)ASCII_BARRA_ESQUINA_DERECHA_INFERIOR;
}

void agregar_opciones(string opciones[], int inicio, int can, string id) {
    rlutil::setColor(rlutil::GREY);
    for(int x = 0; x < can-1; x++) {
        rlutil::locate(32, inicio + (2 * x));
        cout << opciones[x];
        if(x == 0){
            rlutil::locate(75, inicio);
            cout << id;
        }
    }
}

void mostrar_encabezado(string opciones[], int posX, int posY, size_t can, size_t opciones_espacios[]) {
    rlutil::locate(posX, posY);
    cout << (char)ASCII_ESQUINA_IZQUIERDA;
    for(size_t x = 0; x < can; x++) {
        centrar_texto("", (char)ASCII_BARRA_HORIZONTAL, opciones_espacios[x]);
        if(x+1 != can) cout << (char)ASCII_BARRA_EMPALME_ABAJO;
    }
    cout << (char)ASCII_ESQUINA_DERECHA;


    rlutil::locate(posX, posY+1);
    for(size_t x = 0; x < can; x++) {
        rlutil::setColor(rlutil::MAGENTA);
        cout << (char)ASCII_BARRA_VERTICAL;
        rlutil::setColor(rlutil::GREY);
        cout << opciones[x];
    }
    rlutil::setColor(rlutil::MAGENTA);
    cout << (char)ASCII_BARRA_VERTICAL;


    rlutil::locate(posX, posY+2);
    cout << (char)ASCII_BARRA_EMPALME_DERECHA;
    for(size_t x = 0; x < can; x++) {
        centrar_texto("", (char)ASCII_BARRA_HORIZONTAL, opciones_espacios[x]);
        if(x+1 != can) cout << (char)ASCII_BARRA_DOBLE_CRUCE;
    }
    cout << (char)ASCII_BARRA_EMPALME_IZQUIERDA;
}

void barra_final(size_t can, int posX, int posY, size_t datos[]) {
    rlutil::locate(posX, posY);
    cout << (char)ASCII_BARRA_EMPALME_IZQUIERDA_INFERIOR;
    for(size_t x = 0; x < can; x++) {
        centrar_texto("", (char)ASCII_BARRA_HORIZONTAL, datos[x]);
        if(x+1 != can) cout << (char)ASCII_BARRA_EMPALME_HORIZONTAL_ARRIBA;
    }
    cout << (char)ASCII_BARRA_ESQUINA_DERECHA_INFERIOR;
}

void caja_eliminar(int *id, int posX, int posY){
    rlutil::locate(posX, posY);
    cout << (char)ASCII_ESQUINA_IZQUIERDA; centrar_texto("", (char)ASCII_BARRA_HORIZONTAL, 4); cout << (char)ASCII_BARRA_EMPALME_ABAJO;
    centrar_texto("", (char)ASCII_BARRA_HORIZONTAL, 10); cout << (char)187;

    rlutil::locate(posX, posY+1);
    cout << (char)ASCII_BARRA_VERTICAL; rlutil::setColor(rlutil::GREY); cout << " ID ";
    rlutil::setColor(rlutil::MAGENTA); cout << (char)ASCII_BARRA_VERTICAL;
    cout << "          " << (char)ASCII_BARRA_VERTICAL;

    rlutil::locate(posX, posY+2);
    cout << (char)ASCII_BARRA_EMPALME_IZQUIERDA_INFERIOR; centrar_texto("", (char)ASCII_BARRA_HORIZONTAL, 4); cout << (char)ASCII_BARRA_EMPALME_HORIZONTAL_ARRIBA;
    centrar_texto("", (char)ASCII_BARRA_HORIZONTAL, 10); cout << (char)ASCII_BARRA_ESQUINA_DERECHA_INFERIOR;

    rlutil::locate(59, posY+1);
    rlutil::showcursor();
    rlutil::setColor(rlutil::WHITE);
    *id = cargarInt(8);
    rlutil::hidecursor();
}


void limpiar_linea(int posX, int posY) {
    rlutil::locate(posX, posY);
    cout << "                                                    ";
}
