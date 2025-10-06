#include <iostream>
#include <cstring>
using namespace std;

#include "utilidades.h"

void cargarCadena(char* palabra, int maxLen) {
    int i = 0;
    int ch;  // Use int to store cin.get() result
    // Limpiar cualquier whitespace residual del buffer, es como cin.ignore(1000, '\n');
    std::cin >> std::ws;

    while (i < maxLen - 1)    // Leave space for null terminator
    {
        ch = std::cin.get();
        if (ch == EOF || ch == '\n')    // Stop on EOF or newline
        {
            break;
        }
        palabra[i] = static_cast<char>(ch);  // Safe explicit cast
        ++i;
    }
    palabra[i] = '\0';  // Null-terminate the string
}

void toUpperCase(char *texto) {
    for(int x = 0; texto[x] != '\0'; ++x)
    {
        if(texto[x] >= 'a' && texto[x] <= 'z')
        {
            texto[x] = texto[x] - 32;
        }
    }
}

void centrar_texto(string palabra, char dato, size_t cantidad) {
    size_t espacios_izq = (cantidad - palabra.length()) / 2;
    size_t espacios_der = cantidad - palabra.length() - espacios_izq;

    cout << string(espacios_izq, dato) << palabra << string(espacios_der, dato);
}
