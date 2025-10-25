#ifndef ARTWORKS_H_INCLUDED
#define ARTWORKS_H_INCLUDED

#include <string>

void titulo();
void menu(std::string title, std::string opciones[], int inicio, int can);
void agregar(std::string title, int inicio, int can);
void agregar_opciones(std::string opciones[], int inicio, int can, std::string id);
void mostrar_encabezado(std::string opciones[], int posX, int posY, size_t can, size_t opciones_espacios[]);
void barra_final(size_t can, int posX, int posY, size_t datos[]);
void caja_eliminar(int *id, int posX, int posY);
void limpiar_linea(int posX, int posY);

#endif // ARTWORKS_H_INCLUDED