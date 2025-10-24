#include <iostream>
using namespace std;

#include "artworks.h"
#include "utilidades.h"

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
    cout << (char)201;
    centrar_texto("", (char)205, 41);
    cout << (char)187;

    rlutil::locate(40, inicio+1);
    cout << (char)186;
    centrar_texto("", ' ', 41);
    cout << (char)186;

    rlutil::locate(40, inicio+2);
    cout << (char)186;
    rlutil::setColor(rlutil::WHITE);
    centrar_texto(title, ' ', 41);
    rlutil::setColor(rlutil::MAGENTA);
    cout << (char)186;

    rlutil::locate(40, inicio+3);
    cout << (char)186;
    centrar_texto("", ' ', 41);
    cout << (char)186;

    rlutil::locate(40, inicio+4);
    cout << (char)204;
    centrar_texto("", (char)205, 41);
    cout << (char)185;

    rlutil::locate(40, inicio+5);
    cout << (char)186;
    centrar_texto("", ' ', 41);
    cout << (char)186;

    for(int x = 0; x < can; x++) {
        rlutil::locate(40, (inicio+6) + (x * 2));
        cout << (char)186;
        rlutil::setColor(rlutil::WHITE);
        centrar_texto(opciones[x], ' ', 41);
        rlutil::setColor(rlutil::MAGENTA);
        cout << (char)186;

        rlutil::locate(40, (inicio+6) + (x * 2) + 1);
        cout << (char)186;
        centrar_texto("", ' ', 41);
        cout << (char)186;
    }

    rlutil::locate(40, (inicio+6) + 2 * can);
    cout << (char)200;
    centrar_texto("", (char)205, 41);
    cout << (char)188;
}

void agregar(string title, int inicio, int can) {
    rlutil::locate(30, inicio);
    cout << (char)201;
    centrar_texto("", (char)205, 61);
    cout << (char)187;

    rlutil::locate(30, inicio + 1);
    cout << (char)186;
    centrar_texto("", ' ', 61);
    cout << (char)186;

    rlutil::locate(30, inicio + 2);
    cout << (char)186;
    rlutil::setColor(rlutil::WHITE);
    centrar_texto(title, ' ', 61);
    rlutil::setColor(rlutil::MAGENTA);
    cout << (char)186;

    rlutil::locate(30, inicio + 3);
    cout << (char)186;
    centrar_texto("", ' ', 61);
    cout << (char)186;

    rlutil::locate(30, inicio + 4);
    cout << (char)204;
    centrar_texto("", (char)205, 61);
    cout << (char)185;

    for (int fila = inicio + 5; fila < inicio + 5 + (can * 2); fila++) {
        rlutil::locate(30, fila);
        cout << (char)186;
        centrar_texto("", ' ', 61);
        cout << (char)186;
    }

    rlutil::locate(30, inicio + 5 + (can * 2));
    cout << (char)200;
    centrar_texto("", (char)205, 61);
    cout << (char)188;
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

void mostrar_encabezado(string opciones[], int posX, int posY, int can, int opciones_espacios[]) {
    rlutil::locate(posX, posY);
    cout << (char)201;
    for(int x = 0; x < can; x++) {
        centrar_texto("", (char)205, opciones_espacios[x]);
        if(x+1 != can) cout << (char)203;
    }
    cout << (char)187;


    rlutil::locate(posX, posY+1);
    for(int x = 0; x < can; x++) {
        rlutil::setColor(rlutil::MAGENTA);
        cout << (char)186;
        rlutil::setColor(rlutil::GREY);
        cout << opciones[x];
    }
    rlutil::setColor(rlutil::MAGENTA);
    cout << (char)186;


    rlutil::locate(posX, posY+2);
    cout << (char)204;
    for(int x = 0; x < can; x++) {
        centrar_texto("", (char)205, opciones_espacios[x]);
        if(x+1 != can) cout << (char)206;
    }
    cout << (char)185;
}

void barra_final(int can, int posX, int posY, int datos[]) {
    rlutil::locate(posX, posY);
    cout << (char)200;
    for(int x = 0; x < can; x++) {
        centrar_texto("", (char)205, datos[x]);
        if(x+1 != can) cout << (char)202;
    }
    cout << (char)188;
}

void caja_eliminar(int *id, int posX, int posY){
    rlutil::locate(posX, posY);
    cout << (char)201; centrar_texto("", (char)205, 4); cout << (char)203;
    centrar_texto("", (char)205, 10); cout << (char)187;

    rlutil::locate(posX, posY+1);
    cout << (char)186; rlutil::setColor(rlutil::GREY); cout << " ID ";
    rlutil::setColor(rlutil::MAGENTA); cout << (char)186;
    cout << "          " << (char)186;

    rlutil::locate(posX, posY+2);
    cout << (char)200; centrar_texto("", (char)205, 4); cout << (char)202;
    centrar_texto("", (char)205, 10); cout << (char)188;

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