#include "menuReports.h"
#include "artworks.h"
#include <iostream>
#include "archivoManager.h"
#include "rlutil.h"
#include "uiManager.h"
#include <string>
#include "ContextoGestores.h"
#include "gestorVenta.h"
#define byte windows_byte
#include "rlutil.h"
#undef byte

void menuReports(Contexto objetos, ContextoGestores& gestores) {
    const int TAMANIO_MENU = 6;
    std::string opciones[TAMANIO_MENU] = {
        "VENTAS DEL ULTIMO CUATRIMESTRE",
        "CLIENTE CON MAS PRODUCTOS",
        "TOP 3 VENDEDORES",
        "PRODUCTO MAS VENDIDO",
        "VENTA CON MAYOR MONTO",
        "SALIR"
    };

    const int INICIO_MENU_Y = 7;
    const int POSICION_CURSOR_X = 44;
    const int ESPACIO_MENU = 13;
    const int OPCION_MAXIMA = 10;

    while(true) {
        int opcionSeleccionada = 0;
        bool cursorActivo = true;
        system("cls");

        menu("R E P O R T E S", opciones, INICIO_MENU_Y, TAMANIO_MENU);

        while(cursorActivo == true) {
            rlutil::locate(POSICION_CURSOR_X, ESPACIO_MENU + opcionSeleccionada);
            std::cout << (char)175;

            int teclaPresionada = rlutil::getkey();
            const int PASO_OPCION = 2;
            const int PASO_ABAJO = 2;

            switch(teclaPresionada) {
                case 14: // Flecha arriba
                    rlutil::locate(POSICION_CURSOR_X, ESPACIO_MENU + opcionSeleccionada);
                    std::cout << " ";
                    opcionSeleccionada -= PASO_OPCION;
                    if(opcionSeleccionada < 0) opcionSeleccionada = OPCION_MAXIMA;
                    break;

                case 15: // Flecha abajo
                    rlutil::locate(POSICION_CURSOR_X, ESPACIO_MENU + opcionSeleccionada);
                    std::cout << " ";
                    opcionSeleccionada += PASO_ABAJO;
                    if(opcionSeleccionada > OPCION_MAXIMA) opcionSeleccionada = 0;
                    break;

                case 1: // Enter
                    system("cls");
                    cursorActivo = false;
                    switch(opcionSeleccionada) {
                        case 0:
                            std::cout << "Mostrando ventas del ultimo cuatrimestre..." << std::endl;
                            opcion1(objetos,gestores);
                            break;
                        case 2:
                            std::cout << "Mostrando cliente con mas productos..." << std::endl;
                            break;
                        case 4:
                            std::cout << "Mostrando top 3 vendedores..." << std::endl;
                            break;
                        case 6:
                            std::cout << "Mostrando producto más vendido..." << std::endl;
                            break;
                        case 8:
                            std::cout << "Mostrando venta con mayor monto..." << std::endl;
                            break;
                        case 10:
                            return;
                    }
                    system("pause");
            }
        }
    }
}


//Opción 1: Ventas del último cuatrimestr

void opcion1(Contexto objetos, ContextoGestores& gestor) {

    // --- 1. OBTENER FECHA ACTUAL Y LÍMITE ---

    // Obtenemos la fecha actual del sistema
    time_t now = time(0);
    tm* ltm = localtime(&now);
    int anioActual = 1900 + ltm->tm_year;
    int mesActual = 1 + ltm->tm_mon;
    int diaActual = ltm->tm_mday;

    // Calculamos la fecha límite (4 meses atrás)
    int anioLimite = anioActual;
    int mesLimite = mesActual - 4; // Restamos 4 meses
    // Si el mes da 0 o negativo, ajustamos el año
    if (mesLimite <= 0) {
        mesLimite += 12; // Ej: Mes 3 (Marzo) - 4 = -1.  -1 + 12 = 11 (Noviembre)
        anioLimite -= 1; // Y bajamos un año (ej: 2025 -> 2024)
    }

    // Convertimos las fechas a un entero (YYYYMMDD) para compararlas fácil
    int fechaActualInt = anioActual * 10000 + mesActual * 100 + diaActual;
    int fechaLimiteInt = anioLimite * 10000 + mesLimite * 100 + diaActual;


    // --- 2. LEER Y FILTRAR LAS VENTAS ---

    vector<Venta> todasLasVentas;
    vector<Venta> ventasReporte; // Aquí guardamos solo las que cumplen la condición

    // Leemos todas las ventas del archivo
    // Leemos todas las ventas del archivo
    gestor.gestorVenta.leerTodos(todasLasVentas);

    // Recorremos las ventas y filtramos
    for (const Venta& v : todasLasVentas) {
        // Ignoramos ventas inactivas (eliminadas)
        if (!v.getEstado()) {
            continue;
        }

        Fecha fechaVenta = v.getFecha(); // Obtenemos la fecha de la venta
        int fechaVentaInt = fechaVenta.getAnio() * 10000 + fechaVenta.getMes() * 100 + fechaVenta.getDia();

        // Comprobamos si la venta está dentro de nuestra "ventana" de 4 meses
        if (fechaVentaInt >= fechaLimiteInt && fechaVentaInt <= fechaActualInt) {
            ventasReporte.push_back(v); // ¡La añadimos al reporte!
        }
    }


    // --- 3. MOSTRAR LA TABLA FILTRADA ---

    rlutil::setColor(rlutil::WHITE);
    rlutil::locate(15, 2);
    std::cout << "REPORTE: VENTAS DE LOS ULTIMOS 4 MESES (Desde " << diaActual << "/" << mesLimite << "/" << anioLimite << " hasta Hoy)";

    // Si el vector de reporte está vacío, avisamos y terminamos
    if (ventasReporte.empty()) {
        rlutil::setColor(rlutil::RED);
        rlutil::locate(15, 6);
        std::cout << "No se encontraron ventas activas en este período." << std::endl;
        return;
    }

    // Definimos el layout (el mismo que usaste en listarVentas)
    const size_t OPCIONES = 6; // 6 columnas (sin el ID base)
    const int posX = 15;
    const int posY = 4;
    std::string titulos[OPCIONES] = {
        " ID VENTA ", " ID CLIENTE ", " LEGAJO VEND ", "    TOTAL    ", "   FECHA    ", "  ESTADO  "
    };
    size_t espacios[OPCIONES] = { 10, 12, 12, 15, 12, 10 };

    // Dibujamos el encabezado
    mostrar_encabezado(titulos, posX, posY, OPCIONES, espacios);

    // Recorremos el vector FILTRADO y dibujamos cada fila
    int cont_lineas = 0;
    for (const Venta& venta : ventasReporte) {
        venta.mostrarFila(posX, posY + 3 + cont_lineas);
        cont_lineas++;
        // (Omitimos la paginación para el reporte, pero podés agregarla si querés)
    }

    // Dibujamos la barra final
    barra_final(OPCIONES, posX, posY + 3 + cont_lineas, espacios);

    rlutil::locate(posX, posY + 3 + cont_lineas + 2); // Dejamos el cursor abajo
}
/*
Opción 2: Cliente con más productos
*/
// void opcion2(ContextoGestores& contextoGestores) {
//     // Obtener el cliente con más productos comprados
//     id
// }
