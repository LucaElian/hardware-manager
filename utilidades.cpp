#include <iostream>
#include <cstring>
#include <limits>
using namespace std;

#include "utilidades.h"


#define byte windows_byte
#include "rlutil.h"
#undef byte

void cargarCadena(char *cadena, int maxDigits) {
    int i = 0;
    int key;
    char c;

    while (true) {
        key = rlutil::getkey();
        c = static_cast<char>(key);

        if (c == 1 && i > 0) { /// 1 == ENTER
            cadena[i] = '\0';
            break;
        }

        if (c == 8 && i > 0) { /// 8 == BACKSPACE
            i--;
            cout << "\b \b"; /// BORRA CARACTER EN PANTALLA
        }

        else if (i < maxDigits - 1 && c >= 32 && c <= 126) { /// CARACTERES IMPRIMIBLES
            cadena[i++] = c;
            cout << c;
        }
    }
}

int cargarInt(int maxDigits) {
    char buffer[10] = {0};
    int i = 0;
    int key;
    char c;

    while (true) {
        key = rlutil::getkey();
        c = static_cast<char>(key);

        if (c == 1 && i > 0) {
            buffer[i] = '\0';
            break;
        }

        if (c == 8 && i > 0) {
            i--;
            cout << "\b \b";
        }

        else if (i < maxDigits && c >= '0' && c <= '9') {
            buffer[i++] = c;
            cout << c;
        }
    }
    return atoi(buffer);
}

double cargarDouble(int maxDigits, int maxDecimals) {
    char buffer[16] = {0};
    int i = 0, decimales = 0;
    bool punto = false;
    int key;
    char c;

    while (true) {
        key = rlutil::getkey();
        c = static_cast<char>(key);

        if (c == 1 && i > 0) {  /// 13 == ENTER
            buffer[i] = '\0';
            break;
        }

        if (c == 8 && i > 0) {  /// 8 == BACKSPACE
            i--;
            if (buffer[i] == '.') punto = false;
            else if (punto && decimales > 0) decimales--;
            cout << "\b \b";
        }

        else if ((c == '.' || c == ',') && !punto && i > 0 && i < maxDigits - 1) {
            buffer[i++] = '.';
            punto = true;
            cout << c;
        }

        else if ((c >= '0' && c <= '9') && i < maxDigits) {
            if (!punto) {
                buffer[i++] = c;
                cout << c;
            }
            else {
                if (decimales < maxDecimals) {
                    buffer[i++] = c;
                    decimales++;
                    cout << c;
                }
            }
        }
    }
    return atof(buffer);
}

void toUpperCase(char *texto) {
    for(int x = 0; texto[x] != '\0'; ++x) {
        if(texto[x] >= 'a' && texto[x] <= 'z') {
            texto[x] = texto[x] - 32;
        }
    }
}

void centrar_texto(string palabra, char dato, size_t cantidad) {
    size_t espacios_izq = (cantidad - palabra.length()) / 2;
    size_t espacios_der = cantidad - palabra.length() - espacios_izq;

    cout << string(espacios_izq, dato) << palabra << string(espacios_der, dato);
}
