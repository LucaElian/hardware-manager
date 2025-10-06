#ifndef PRODUCTOS_H_INCLUDED
#define PRODUCTOS_H_INCLUDED
#include <cstring>

#include "clsFecha.h"

class Producto {
    private:
        unsigned int idProducto;
        char nombre[30];
        char tipo[20];
        float precio;
        int stock;
        bool estado;
        Fecha ingresoProducto;
    public:
        /// CONSTRUCTOR Y DESTRUCTOR
        Producto(unsigned int _idProducto = 0,
                const char *_nombre = "vacio",
                const char *_tipo = "vacio",
                int _stock = 0,
                float _precio = 0,
                bool estado = true,
                Fecha _fecha = Fecha(1,1,1));
        ~Producto(){}

        /// SETTERS
        void setID(unsigned int);
        void setNombre(char *);
        void setTipo(char *);
        void setStock(int);
        void setPrecio(float);
        void setEstado(bool);
        void setFecha(int, int, int);

        /// GETTERS
        unsigned int getID() const;
        const char *getNombre() const;
        const char *getTipo() const;
        float getPrecio() const;
        int getStock() const;
        bool getEstado() const;
        Fecha getFecha() const;

        ///Otros metodos
        void CargarP();
        void MostrarP();
};
#endif // PRODUCTOS_H_INCLUDED
