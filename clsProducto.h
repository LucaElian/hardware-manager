#ifndef PRODUCTOS_H_INCLUDED
#define PRODUCTOS_H_INCLUDED
#include <cstring>

#include "clsFecha.h"

class Producto {
    private:
        int id;
        char nombre[20];
        char tipo[20];
        float precio;
        int stock;
        Fecha ingreso;
    public:
        /// CONSTRUCTOR Y DESTRUCTOR
        Producto( int _id = 0, const char *_nombre = "vacio", const char *_tipo = "vacio", int _stock = 0, float _precio = 0, Fecha _fecha);
        Producto();
        ~Producto(){}

        /// GETTERS
        const char *getNombre();
        const char *getTipo();
        int getId();
        float getPrecio();
        int getStock();
        Fecha getFecha();

        /// SETTERS
        void setNombre(char n[20]) {strcpy(nombre, n);}
        void setTipo(char t[20]) {strcpy(tipo, t);}
        void setID(int i) {id = i;}
        void setPrecio(float p) {precio = p;}
        void setStock(int s) {stock = s;}
        void setFecha(int d, int m, int a) {ingreso.setFecha(d, m, a);}

        ///Otros metodos
        void Cargar();
        void Mostrar();
};

#endif // PRODUCTOS_H_INCLUDED
