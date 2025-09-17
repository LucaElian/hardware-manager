#ifndef PRODUCTOS_H_INCLUDED
#define PRODUCTOS_H_INCLUDED
#include <cstring>

#include "clsFecha.h"

class Producto {
    private:
        char nombre[20];
        char tipo[20];
        int id;
        float precio;
        int stock;
        Fecha ingreso;
    public:
        /// CONSTRUCTOR Y DESTRUCTOR
        Producto(const char *_nombre, const char *_tipo, int _id, int _stock, float _precio, Fecha _fecha);
        ~Producto(){}

        /// GETTERS
        const char *getNombre() const {return nombre;}
        const char *getTipo() const {return tipo;}
        int getId() const {return id;}
        float getPrecio() const {return precio;}
        int getStock() const {return stock;}
        Fecha getFecha() const {return ingreso;}

        /// SETTERS
        void setNombre(char n[20]) {strcpy(nombre, n);}
        void setTipo(char t[20]) {strcpy(tipo, t);}
        void setID(int i) {id = i;}
        void setPrecio(float p) {precio = p;}
        void setStock(int s) {stock = s;}
        void setFecha(int d, int m, int a) {ingreso.setFecha(d, m, a);}
};

#endif // PRODUCTOS_H_INCLUDED
