#include <iostream>
using namespace std;

#include "utilidades.h"

void toUpperCase(char *texto){
    for(int x = 0; texto[x] != '\0'; ++x){
        if(texto[x] >= 'a' && texto[x] <= 'z'){
            texto[x] = texto[x] - 32;
        }
    }
}

void centrar_texto(string palabra, char dato, size_t cantidad){
    size_t espacios_izq = (cantidad - palabra.length()) / 2;
    size_t espacios_der = cantidad - palabra.length() - espacios_izq;

    cout << string(espacios_izq, dato) << palabra << string(espacios_der, dato);
}