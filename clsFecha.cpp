#include <iostream>
#include <ctime>
using namespace std;

#include "clsFecha.h"
#include "clsProducto.h"

///Constructor de la clase fecha
Fecha::Fecha(int _dia, int _mes, int _anio){
    dia = _dia;
    mes = _mes;
    anio = _anio;
}

///Constructor por defecto que crea con la fecha actual
void Fecha::setearFechaActual(){
    time_t t = time(0);
    tm* ahora = localtime(&t);

    dia = ahora->tm_mday;
    mes = ahora->tm_mon + 1;
    anio = ahora->tm_year + 1900;
}

//el metodo q habias hecho es igual al de aca arriba


///Metodo para "pasarlo a date", aun no tiene ningun uso objetivo
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

void Fecha::setFecha(int _dia, int _mes, int _anio){
            dia = _dia;
            mes = _mes;
            anio = _anio;
}

int Fecha::getDia(){
    return dia;
}
int Fecha::getMes(){
    return mes;
}
int Fecha::getAnio(){
    return anio;
}

void Fecha::cargarDia(){
    cout << "INGRESE EL DIA: "; cin >> dia;
    while(dia < 1 || dia > 31){
        cout << "DIA INVALIDO. INGRESE EL DIA: "; cin >> dia;
    }
}

void Fecha::cargarMes(){
    cout << "INGRESE EL MES: "; cin >> mes;
    while(mes < 1 || mes > 12){
        cout << "MES INVALIDO. INGRESE EL MES: "; cin >> mes;
}
}

void Fecha::cargarAnio(){
    cout << "INGRESE EL ANIO: "; cin >> anio;
    while(anio < 1){
        cout << "ANIO INVALIDO. INGRESE EL ANIO: "; cin >> anio;
}
}

void Fecha::CargarF(){
cout << "Cargue la fecha del producto ->" << endl;
cargarDia();
cargarMes();
cargarAnio();
}

void Fecha::MostrarF() const {
cout << dia << "/" << mes << "/" << anio;
//fijate thiago como hacer que aca reciba el format to date o algo asi
}
