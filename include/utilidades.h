#ifndef UTILIDADES_H_INCLUDED
#define UTILIDADES_H_INCLUDED

#include <string>
#include <cstddef>

#define byte windows_byte
#include "rlutil.h"
#undef byte

using namespace std;

void cargarCadena(char *, int);
int cargarInt(int);
double cargarDouble(int, int);
void toUpperCase(char *text);
void centrar_texto(string palabra, char dato, size_t cantidad);

#endif // UTILIDADES_H_INCLUDED
