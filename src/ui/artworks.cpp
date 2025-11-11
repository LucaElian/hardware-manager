#include <iostream>
#include <iomanip>

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

void agregar_opciones(string opciones[], int inicio, int can, string id, int posx) {
    rlutil::setColor(rlutil::GREY);
    for(int x = 0; x < can-1; x++) {
        rlutil::locate(32, inicio + (2 * x));
        cout << opciones[x];
        if(x == 0){
            rlutil::locate(posx, inicio);
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

void mostrar_carrito(int cantidad, int posY, int *terminacion, double total){
    rlutil::locate(13, posY);
    centrar_texto("CARRITO DE COMPRAS", ' ', 100);

    rlutil::setColor(rlutil::MAGENTA);
    rlutil::locate(13, posY+2);
    cout << (char)ASCII_ESQUINA_IZQUIERDA;
    centrar_texto("", (char)205, 93);
    cout << (char)ASCII_ESQUINA_DERECHA;


    rlutil::locate(13, posY+3);
    cout << (char)ASCII_BARRA_VERTICAL;
    rlutil::setColor(rlutil::WHITE);
    cout << " ID PRODUCTO ";

    rlutil::setColor(rlutil::MAGENTA);
    cout << (char)ASCII_BARRA_VERTICAL;

    rlutil::setColor(rlutil::WHITE);
    cout << "            NOMBRE             ";

    rlutil::setColor(rlutil::MAGENTA);
    cout << (char)ASCII_BARRA_VERTICAL;

    rlutil::setColor(rlutil::WHITE);
    cout << " CANTIDAD  ";

    rlutil::setColor(rlutil::MAGENTA);
    cout << (char)ASCII_BARRA_VERTICAL;

    rlutil::setColor(rlutil::WHITE);
    cout << " PRECIO UNITARIO ";

    rlutil::setColor(rlutil::MAGENTA);
    cout << (char)ASCII_BARRA_VERTICAL;

    rlutil::setColor(rlutil::WHITE);
    cout << "     SUBTOTAL    ";

    rlutil::setColor(rlutil::MAGENTA);
    cout << (char)ASCII_BARRA_VERTICAL;

    rlutil::locate(13, posY+4);
    cout << (char)ASCII_BARRA_EMPALME_DERECHA;
    centrar_texto("", (char)205, 93);
    cout << (char)ASCII_BARRA_EMPALME_IZQUIERDA;

    int x = 0;
    for(x = 0; x < cantidad; x++){
        rlutil::locate(13, posY+5+x);
        cout << (char)ASCII_BARRA_VERTICAL;
        rlutil::locate(27, posY+5+x);
        cout << (char)ASCII_BARRA_VERTICAL;
        rlutil::locate(59, posY+5+x);
        cout << (char)ASCII_BARRA_VERTICAL;
        rlutil::locate(71, posY+5+x);
        cout << (char)ASCII_BARRA_VERTICAL;
        rlutil::locate(89, posY+5+x);
        cout << (char)ASCII_BARRA_VERTICAL;
        rlutil::locate(107, posY+5+x);
        cout << (char)ASCII_BARRA_VERTICAL;
    }

    rlutil::locate(13, posY + 5 + x);
    cout << (char)ASCII_BARRA_EMPALME_IZQUIERDA_INFERIOR;
    centrar_texto("", (char)ASCII_BARRA_HORIZONTAL, 93);
    cout << (char)ASCII_BARRA_ESQUINA_DERECHA_INFERIOR;

    rlutil::setColor(rlutil::GREEN);
    rlutil::locate(12, posY + 5 + x + 1);
    cout << " TOTAL: $" << fixed << setprecision(2) << total;

    *terminacion = x;

}

void caja_producto_cantidad(int *id, int *cantidad, int *posY){
    rlutil::setColor(rlutil::MAGENTA);
    rlutil::locate(32, *posY);
    cout << (char)ASCII_ESQUINA_IZQUIERDA; centrar_texto("", (char)ASCII_BARRA_HORIZONTAL, 13); cout << (char)ASCII_BARRA_EMPALME_ABAJO;
    centrar_texto("", (char)ASCII_BARRA_HORIZONTAL, 10); cout << (char)ASCII_ESQUINA_DERECHA;

    rlutil::locate(32, *posY+1);
    cout << (char)ASCII_BARRA_VERTICAL; rlutil::setColor(rlutil::GREY); cout << " ID PRODUCTO ";
    rlutil::setColor(rlutil::MAGENTA); cout << (char)ASCII_BARRA_VERTICAL;
    cout << "          " << (char)ASCII_BARRA_VERTICAL;

    rlutil::locate(32, *posY+2);
    cout << (char)ASCII_BARRA_EMPALME_IZQUIERDA_INFERIOR; centrar_texto("", (char)ASCII_BARRA_HORIZONTAL, 13); cout << (char)ASCII_BARRA_EMPALME_HORIZONTAL_ARRIBA;
    centrar_texto("", (char)ASCII_BARRA_HORIZONTAL, 10); cout << (char)ASCII_BARRA_ESQUINA_DERECHA_INFERIOR;

    rlutil::locate(62, *posY);
    cout << (char)ASCII_ESQUINA_IZQUIERDA; centrar_texto("", (char)ASCII_BARRA_HORIZONTAL, 13); cout << (char)ASCII_BARRA_EMPALME_ABAJO;
    centrar_texto("", (char)ASCII_BARRA_HORIZONTAL, 10); cout << (char)ASCII_ESQUINA_DERECHA;

    rlutil::locate(62, *posY+1);
    cout << (char)ASCII_BARRA_VERTICAL; rlutil::setColor(rlutil::GREY); cout << " CANTIDAD    ";
    rlutil::setColor(rlutil::MAGENTA); cout << (char)ASCII_BARRA_VERTICAL;
    cout << "          " << (char)ASCII_BARRA_VERTICAL;

    rlutil::locate(62, *posY+2);
    cout << (char)ASCII_BARRA_EMPALME_IZQUIERDA_INFERIOR; centrar_texto("", (char)ASCII_BARRA_HORIZONTAL, 13); cout << (char)ASCII_BARRA_EMPALME_HORIZONTAL_ARRIBA;
    centrar_texto("", (char)ASCII_BARRA_HORIZONTAL, 10); cout << (char)ASCII_BARRA_ESQUINA_DERECHA_INFERIOR;


    rlutil::locate(48, *posY+1);
    rlutil::showcursor();
    rlutil::setColor(rlutil::WHITE);
    *id = cargarInt(8);

    if(*id == 0) return;

    rlutil::locate(78, *posY+1);
    *cantidad = cargarInt(8);
    rlutil::hidecursor();

    *posY+=2;
}


void limpiar_linea(int posX, int posY) {
    rlutil::locate(posX, posY);
    cout << "                                                    ";
}
