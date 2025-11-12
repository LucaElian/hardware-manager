#include <iostream>
#include <cstring>
#include <limits>
#include <string>

#include "utilidades.h"
#include "constantes.h"

#define byte windows_byte
#include "rlutil.h"
#undef byte

using namespace std;

void cargarCadena(char *cadena, int maxDigits) {
    int i = 0;
    int key;
    char c;

    while (true) {
        key = rlutil::getkey();
        c = static_cast<char>(key);

        if (c == TECLA_ENTER && i > 0) {
            cadena[i] = '\0';
            break;
        }

        if (c == TECLA_BACKSPACE && i > 0) {
            i--;
            cout << "\b \b";
        }

        else if (i < maxDigits - TECLA_ENTER && c >= 
            TECLA_ESPACIO && c <= ASCII_IMPRIMIBLE_MAX) {
            cadena[i++] = c;
            cout << c;
        }
    }
}

void cargarCadenaConValor(char *cadena, int maxDigits) {
    int i = strlen(cadena);
    cout << cadena;
    int key;
    char c;

    while (true) {
        key = rlutil::getkey();
        c = static_cast<char>(key);

        if (c == TECLA_ENTER && i > 0) {
            cadena[i] = '\0';
            break;
        }

        if (c == TECLA_BACKSPACE && i > 0) {
            i--;
            cout << "\b \b";
        }

        else if (i < maxDigits - TECLA_ENTER && c >= 
            TECLA_ESPACIO && c <= ASCII_IMPRIMIBLE_MAX) {
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

        if (c == TECLA_ENTER && i > 0) {
            buffer[i] = '\0';
            break;
        }

        if (c == TECLA_BACKSPACE && i > 0) {
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

int cargarIntConValor(int maxDigits, int valorActual) {
    char buffer[10] = {0};
    sprintf(buffer, "%d", valorActual);
    int i = strlen(buffer);
    cout << buffer;
    int key;
    char c;

    while (true) {
        key = rlutil::getkey();
        c = static_cast<char>(key);

        if (c == TECLA_ENTER && i > 0) {
            buffer[i] = '\0';
            break;
        }

        if (c == TECLA_BACKSPACE && i > 0) {
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

int cargarIntConValorFormateado(int maxDigits, int valorActual) {
    char buffer[10] = {0};
    if(maxDigits == 2) {
        sprintf(buffer, "%02d", valorActual);
    } else {
        sprintf(buffer, "%d", valorActual);
    }
    int i = strlen(buffer);
    cout << buffer;
    int key;
    char c;

    while (true) {
        key = rlutil::getkey();
        c = static_cast<char>(key);

        if (c == TECLA_ENTER && i > 0) {
            buffer[i] = '\0';
            break;
        }

        if (c == TECLA_BACKSPACE && i > 0) {
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
    char buffer[10] = {0};
    int i = 0, decimales = 0;
    bool punto = false;
    int key;
    char c;

    while (true) {
        key = rlutil::getkey();
        c = static_cast<char>(key);

        if (c == TECLA_ENTER && i > 0) {
            buffer[i] = '\0';
            break;
        }

        if (c == TECLA_BACKSPACE && i > 0) {
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

double cargarDoubleConValor(int maxDigits, int maxDecimals, double valorActual) {
    char buffer[10] = {0};
    sprintf(buffer, "%.2f", valorActual);
    int i = strlen(buffer);
    cout << buffer;
    
    int decimales = 0;
    bool punto = false;
    for(int j = 0; j < i; j++) {
        if(buffer[j] == '.') {
            punto = true;
        } else if(punto) {
            decimales++;
        }
    }
    
    int key;
    char c;

    while (true) {
        key = rlutil::getkey();
        c = static_cast<char>(key);

        if (c == TECLA_ENTER && i > 0) {
            buffer[i] = '\0';
            break;
        }

        if (c == TECLA_BACKSPACE && i > 0) {
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
    if (palabra.length() >= cantidad) {
        // Si es más grande, la cortamos y la imprimimos
        cout << palabra.substr(0, cantidad);
        return;
    }
    // Si la palabra SÍ entra, hacemos la lógica de centrado normal
    size_t espacios_izq = (cantidad - palabra.length()) / 2;
    size_t espacios_der = cantidad - palabra.length() - espacios_izq;

    cout << string(espacios_izq, dato) << palabra << string(espacios_der, dato);
}