#include <iostream>

#include "fecha.h"
#include "producto.h"
#include "usuario.h"

using namespace std;

int main(){
    Fecha fe(3, 10, 2005);
    cout << fe.toString() << "\n\n";
    Fecha fe1;
    cout << fe1.toString() << "\n\n";

    return 0;
}
