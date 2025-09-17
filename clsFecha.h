#ifndef FECHA_H_INCLUDED
#define FECHA_H_INCLUDED

class Fecha {
    private:
        int dia;
        int mes;
        int anio;
    public:
        /// CONSTRUCTOR Y DESTRUCTOR
        Fecha(int _dia = 0, int _mes = 0, int _anio = 0);
        Fecha();
        ~Fecha(){}

        /// GETTERS
        int getDia() const;
        int getMes() const;
        int getAnio() const;

        /// SETTER
        void setFecha(int d, int m, int a){
            dia = d;
            mes = m;
            anio = a;
        }

        /// METODOS
        std::string formatToDate();
        void CargarFechaProducto();
        void Mostrar() const;
        ///void autoCompletado();
};

#endif // FECHA_H_INCLUDED
