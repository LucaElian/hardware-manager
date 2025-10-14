#include <iostream>
#include <ctime>
using namespace std;

#include "clsFecha.h"
#include "clsProducto.h"
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
