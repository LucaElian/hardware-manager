#ifndef PRODUCTOS_H_INCLUDED
#define PRODUCTOS_H_INCLUDED
#include <cstring>

#include "clsFecha.h"

class Producto {
    private:
        int id;
        char nombre[30];
        char tipo[20];
        float precio;
        int stock;
        Fecha ingresoProducto;
    public:
        /// CONSTRUCTOR Y DESTRUCTOR
        Producto( int _id = 0, const char *_nombre = "vacio", const char *_tipo = "vacio", int _stock = 0, float _precio = 0, Fecha _fecha = Fecha(0,0,0));
        ~Producto(){}

        /// SETTERS
        void setID(int);
        void setNombre(char *);
        void setTipo(char *);
        void setStock(int);
        void setPrecio(float);
        void setFecha(int, int , int );

        /// GETTERS
        int getID();
        const char *getNombre();
        const char *getTipo();
        float getPrecio();
        int getStock();
        Fecha getFecha();

        ///Otros metodos
        void CargarP();
        void MostrarP();
        int setearIdentificador(int);
};

#endif // PRODUCTOS_H_INCLUDED
