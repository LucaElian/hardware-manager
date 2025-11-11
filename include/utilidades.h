#ifndef UTILIDADES_H_INCLUDED
#define UTILIDADES_H_INCLUDED

#include <string>
#include <cstddef>

#define byte windows_byte
#include "rlutil.h"
#undef byte

using namespace std;

void cargarCadena(char *, int);
void cargarCadenaConValor(char *, int);
int cargarInt(int);
int cargarIntConValor(int, int);
int cargarIntConValorFormateado(int, int);
double cargarDouble(int, int);
double cargarDoubleConValor(int, int, double);
void toUpperCase(char *text);
void centrar_texto(string palabra, char dato, size_t cantidad);

#endif // UTILIDADES_H_INCLUDED
