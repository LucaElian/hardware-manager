#include <iostream>
#include <ctime>

#include "clsFecha.h"
#include "clsProducto.h"

using namespace std;

/// CONSTRUCTOR
Fecha::Fecha(int _dia, int _mes, int _anio){
    dia = _dia;
    mes = _mes;
    anio = _anio;
}

//Constructor por defecto que crea con la fecha actual
//Fecha::Fecha(){
//    time_t t = time(0);
//    tm* ahora = localtime(&t);
//
//    dia = ahora->tm_mday;
//    mes = ahora->tm_mon + 1;
//    anio = ahora->tm_year + 1900;
//
//}

/// Metodo para normalizar la fecha a dd/mm/aaaa
string Fecha::formatToDate() const{
    //Crea los 3 al aire, no deberia recibirlos desde un objeto'?
    string diaString;
    string mesString;
    string anioString;

    // CORRECCION DE MUESTREO
    if(dia < 10) diaString = "0" + to_string(dia);
    else diaString = to_string(dia);

    if(mes < 10) mesString = "0" + to_string(mes);
    else mesString = to_string(mes);

    anioString = to_string(anio);

    return diaString + "/" + mesString + "/" + anioString;
}

void Fecha::cargarFechaProducto(){
    cout << "INGRESE EL DIA: "; cin >> dia;
    while(dia < 1 || dia > 31){ 
        cout << "DIA INVALIDO. INGRESE EL DIA: "; cin >> dia;
    }

    cout << "INGRESE EL MES: "; cin >> mes;
    while(dia < 1 || dia > 12){ 
        cout << "MES INVALIDO. INGRESE EL DIA: "; cin >> mes;
    }

    cout << "INGRESE EL ANIO: "; cin >> anio;
    while(dia < 1){
        cout << "ANIO INVALIDO. INGRESE EL ANIO: "; cin >> anio;
    }
}

void Fecha::mostrarFechaProducto() {
    cout << formatToDate();
}
