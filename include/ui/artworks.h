#ifndef ARTWORKS_H_INCLUDED
#define ARTWORKS_H_INCLUDED

#include <string>

void titulo();
void menu(std::string title, std::string opciones[], int inicio, int can);
void agregar(std::string title, int inicio, int can);
void agregar_opciones(std::string opciones[], int inicio, int can, std::string id);
void mostrar_encabezado(std::string opciones[], int posX, int posY, int can, int opciones_espacios[]);
void barra_final(int can, int posY, int datos[]);

#endif // ARTWORKS_H_INCLUDED