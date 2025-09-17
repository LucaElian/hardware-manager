#ifndef FECHA_H_INCLUDED
#define FECHA_H_INCLUDED

class Fecha {
    private:
        int dia;
        int mes;
        int anio;
    public:
        /// CONSTRUCTOR Y DESTRUCTOR
        Fecha(int _dia, int _mes, int _anio);
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
        ///void autoCompletado();
};

#endif // FECHA_H_INCLUDED
