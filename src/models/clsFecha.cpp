#include <iostream>
#include <ctime>
using namespace std;

#include "clsFecha.h"
#include "utilidades.h"

///Constructor de la clase fecha
Fecha::Fecha(int _dia, int _mes, int _anio) {
    dia = _dia;
    mes = _mes;
    anio = _anio;
}

void Fecha::setDia() { dia = cargarInt(2); }
void Fecha::setMes() { mes = cargarInt(2); }
void Fecha::setAnio() { anio = cargarInt(4); }

void Fecha::setDiaConValor() { dia = cargarIntConValorFormateado(2, dia); }
void Fecha::setMesConValor() { mes = cargarIntConValorFormateado(2, mes); }
void Fecha::setAnioConValor() { anio = cargarIntConValorFormateado(4, anio); }

///Metodo para "pasarlo a date"
void Fecha::MostrarF() const {
    string diaString;
    string mesString;
    string anioString;
    /// Correccion para el muestreo, si el dia es menor a dos cifras, se aniade un 0 antes, lo mismo con los meses
    if(dia < 10) diaString = "0" + to_string(dia);
    else diaString = to_string(dia);

    if(mes < 10) mesString = "0" + to_string(mes);
    else mesString = to_string(mes);

    anioString = to_string(anio);

    cout << diaString + "/" + mesString + "/" + anioString;
}

bool Fecha::EsBisiesto(int y) {
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

int Fecha::diasDelMes(int m, int y) {
    switch (m) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12: // ENERO - MARZO - MAYO - JULIO - AGOSTO - OCTUBRE - DICIEMBRE
            return 31; // 31 DIAS MAXIMO
        case 4: case 6: case 9: case 11: // ABRIL - JUNIO - SEPTIEMBRE - NOVIEMBRE
            return 30; // 30 DIAS MAXIMO
        case 2: // FEBRERO
            return EsBisiesto(y) ? 29 : 28; // SI ES ANIO BISIESTO 29, SINO 28
        default:
            return 0; // MES INVALIDO
    }
}