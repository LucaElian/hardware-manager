#include <iostream>
#include <ctime>

#include "clsFecha.h"
#include "clsProducto.h"

using namespace std;

///Constructor de la clase fecha
Fecha::Fecha(int _dia, int _mes, int _anio){
    dia = _dia;
    mes = _mes;
    anio = _anio;
}

///Constructor por defecto que crea con la fecha actual
Fecha::Fecha(){
    time_t t = time(0);
    tm* ahora = localtime(&t);

    dia = ahora->tm_mday;
    mes = ahora->tm_mon + 1;
    anio = ahora->tm_year + 1900;
}

///Metodo para "pasarlo a date"
string Fecha::formatToDate(){
    //Crea los 3 al aire, no deberia recibirlos desde un objeto'?
    string diaString;
    string mesString;
    string anioString;
    //Correccion para el muestreo, si el dia es menor a dos cifras, se a�ade un 0 antes, lo mismo con los meses
    if(dia < 10) diaString = "0" + to_string(dia);
    else diaString = to_string(dia);

    if(mes < 10) mesString = "0" + to_string(mes);
    else mesString = to_string(mes);

    anioString = to_string(anio);

    return diaString + "/" + mesString + "/" + anioString;

}

void Fecha::Mostrar() const {
    std::cout << dia << "/" << mes << "/" << anio;
}
