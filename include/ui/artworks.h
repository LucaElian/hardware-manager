#ifndef ARTWORKS_H_INCLUDED
#define ARTWORKS_H_INCLUDED

void titulo();
void menu(string title, string opciones[], int inicio, int can);

void agregar(string title, int inicio, int can);
void agregar_opciones(string opciones[], int inicio, int can, string id);
void mostrar_encabezado(string opciones[], int inicio, int can, int datos[]);

#endif // ARTWORKS_H_INCLUDED
