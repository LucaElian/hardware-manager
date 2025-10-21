#ifndef ARTWORKS_H_INCLUDED
#define ARTWORKS_H_INCLUDED

#include <string>

void titulo();
void menu(std::string title, std::string opciones[], int inicio, int can);
void agregar(std::string title, int inicio, int can);
void agregar_opciones(std::string opciones[], int inicio, int can, std::string id);

#endif // ARTWORKS_H_INCLUDED