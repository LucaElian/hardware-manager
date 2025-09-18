#include <iostream>

#include "clsFecha.h"
#include "clsProducto.h"
#include "clsUsuario.h"

using namespace std;

int main(){

    Fecha fe(2, 9, 2025); // Ejemplo de fecha (día, mes, año)
    Producto p1(1, "TeClAdO", "pErIfErIcO", 10, 299.99f, fe);
    Usuario u1(1, "lUcA", "AbUlaFiA", "profornite", "user", fe);

    fe.mostrarFechaProducto();
    cout << "\n\n";

    p1.mostrar();
    cout << "\n\n";

    u1.mostrar();
    cout << "\n\n";

    /// Producto p2;
    /// p2.cargar();
    /// cout << "\n\n";
    /// p2.mostrar();

    Usuario u2;
    u2.cargar();
    cout << "\n\n";
    u2.mostrar();

    system("pause");

    return 0;
}
