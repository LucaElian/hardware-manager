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
        ~Fecha(){}

         /// SETTER
        void setFecha(int , int , int);

        /// GETTERS
        int getDia();
        int getMes();
        int getAnio();

        /// METODOS
        void setearFechaActual();
        std::string formatToDate();
        void CargarF();
        void MostrarF() const;
        ///void autoCompletado();
};

#endif // FECHA_H_INCLUDED
