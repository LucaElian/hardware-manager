#ifndef FECHA_H_INCLUDED
#define FECHA_H_INCLUDED

class Fecha {
    private:
        int dia;
        int mes;
        int anio;
    public:
        /// CONSTRUCTOR Y DESTRUCTOR
        Fecha(int _dia = 1, int _mes = 1, int _anio = 1);
        ///Fecha();
        ~Fecha(){}

        /// SETTER
        void setFecha(int d, int m, int a){
            dia = d;
            mes = m;
            anio = a;
        }

        /// METODOS
        std::string formatToDate() const;
        void cargarFechaProducto();
        void mostrarFechaProducto();
};

#endif // FECHA_H_INCLUDED
