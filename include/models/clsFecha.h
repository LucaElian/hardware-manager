#ifndef FECHA_H_INCLUDED
#define FECHA_H_INCLUDED
#include<iostream>
using namespace std;

class Fecha {
    private:
        int dia;
        int mes;
        int anio;
    public:
        /// CONSTRUCTOR Y DESTRUCTOR
        Fecha(int _dia = 0, int _mes = 0, int _anio = 0);
        ~Fecha(){}

        /// SETTERS
        void setDia();
        void setMes();
        void setAnio();

        /// GETTERS
        int getDia() { return dia; }
        int getMes() { return mes; }
        int getAnio() { return anio; }

        /// METODOS
        void MostrarF() const;
};

#endif // FECHA_H_INCLUDED
