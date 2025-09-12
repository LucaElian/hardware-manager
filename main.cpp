#include <iostream>
#include <ctime>

#include "fecha.h"
#include "productos.h"

using namespace std;

Fecha::Fecha(int _dia, int _mes, int _anio){
    dia = _dia;
    mes = _mes;
    anio = _anio;
}

void Fecha::toString(){
    string d;
    string m;
    string a;
    if(dia < 10) d = "0" + to_string(dia);
    else d = to_string(dia);

    if(mes < 10) m = "0" + to_string(mes);
    else m = to_string(mes);

    a = to_string(anio);

    cout << d << "/" << m << "/" << a;
}

void Fecha::autoCompletado(){
    time_t t = time(0);
    tm* ahora = localtime(&t);

    dia = ahora->tm_mday;
    mes = ahora->tm_mon + 1;
    anio = ahora->tm_year + 1900;
}

int main(){
    Fecha fe(3, 10, 2005);
    fe.toString();
    cout << "\n\n";
    fe.autoCompletado();
    fe.toString();
    cout << "\n\n";

    return 0;
}
