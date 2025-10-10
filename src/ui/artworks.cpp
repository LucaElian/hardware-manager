#include <iostream>
using namespace std;

#include "artworks.h"
#include "utilidades.h"

#define byte windows_byte
#include "rlutil.h"
#undef byte

void titulo()
{
    const string title[5] =
    {
        ",--.   ,--. ,------. ,--.   ,--. ,--.   ,--.  ",
        "|   `.'   | |  .---'  \\  `.'  /   \\  `.'  / ",
        "|  |'.'|  | |  `--,    .'    \\     .'    \\  ",
        "|  |   |  | |  `---.  /  .'.  \\   /  .'.  \\ ",
        "`--'   `--' `------' '--'   '--' '--'   '--'  "
    };

    rlutil::setColor(rlutil::GREEN);

    for(int x = 0; x < 5; x++)
    {
        rlutil::locate(40, 3+x);
        cout << title[x] << "\n";
    }
}

void menu(string title, string opciones[], int inicio, int can)
{
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
    rlutil::setColor(rlutil::GREEN);
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

    for(int x = 0; x < can; x++)
    {
        rlutil::locate(40, (inicio+6) + (x * 2));
        cout << (char)186;
        rlutil::setColor(rlutil::WHITE);
        centrar_texto(opciones[x], ' ', 41);
        rlutil::setColor(rlutil::GREEN);
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
