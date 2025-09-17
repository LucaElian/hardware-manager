#include <iostream>

#include "clsFecha.h"
#include "clsProducto.h"
#include "clsUsuario.h"

using namespace std;

int main(){

    Fecha fechaIngreso(2, 9, 2025); // Ejemplo de fecha (día, mes, año)
    Producto producto1("Teclado", "Periférico", 1, 10, 299.99, fechaIngreso);

    Fecha fechaIngresa(1,3,2022);
    Usuario usuario1("juan","123","admin",fechaIngresa);

    usuario1.Mostrar();
    producto1.Mostrar();

    cout << "lol" << endl;
    cout << "Ahora si se viene lo chido 2222222hkcigpih"<<endl;

    return 0;
}
