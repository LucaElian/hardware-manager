#ifndef FECHA_H_INCLUDED
#define FECHA_H_INCLUDED

class Fecha{
    private:
        int dia;
        int mes;
        int anio;
    public:
        Fecha(int _dia, int _mes, int _anio);
        ~Fecha(){}

        void toString();
        void autoCompletado();
};

#endif // FECHA_H_INCLUDED
