/*=======================
LIBRERÍAS ESTÁNDAR C++
=========================*/
#include <iostream>   // Para usar std::cout y std::endl (imprimir en consola).
#include <string>     // Para poder usar la clase std::string (para los títulos y opciones).
#include <vector>     // Para crear los listados (vectores) de Ventas, Clientes, etc., al leer los archivos.
#include <ctime>      // Para opcion1: Permite obtener la fecha actual del sistema (time, localtime).
#include <map>        // Para opcion2: Permite crear "diccionarios" para contar items y asociar ventas con clientes.
#include <iomanip> // Para opcion 3: para std::setw y std::setprecision
#include <limits> // Para opcion 5: para numeric_limits (para sacar el maximo)
/*===================================================================
NÚCLEO DEL PROYECTO (DATOS)
===================================================================*/
#include "ContextoGestores.h" // Objeto CLAVE. Nos da acceso a todos los gestores de archivos (gestorP, gestorC, gestorV, gestorVenta).
#include "gestorVenta.h"    // Para acceder a la lógica de ventas y, (importante), a la función 'leerTodos' de ventas.
#include "archivoManager.h" // (Incluido por ContextoGestores) Es la plantilla base que maneja los archivos .dat.
#include "clsVenta.h"       // Para poder crear std::vector<Venta> y entender la estructura de una Venta.
#include "clsDetalleVenta.h"// Para poder crear std::vector<DetalleVenta> y contar los items.
#include "clsCliente.h"     // Para poder crear objetos Cliente y mostrar al ganador de opcion2.
#include "clsVendedor.h" //Para la opcion 3
#include "clsProducto.h" // Para la opcion4
/*===================================================================
INTERFAZ DE USUARIO (UI)
===================================================================*/
#include "artworks.h"     // Para dibujar las cajas del menú ('menu()') y las tablas de resultados ('mostrar_encabezado()', 'barra_final()').
#include "rlutil.h"       // Para la navegación del menú (getkey) y los colores (setColor).
#include "uiManager.h"    // Contiene la plantilla 'mostrarRegistros' (aunque los reportes usan 'artworks' directamente).
/*===================================================================
HACK DE COMPILACIÓN (rlutil vs C++)
===================================================================*/
// Este bloque soluciona el conflicto de la palabra 'byte' entre rlutil.h (que es C viejo) y C++ moderno.
#define byte windows_byte
#include "rlutil.h"
#undef byte
/*===================================================================
DECLARACIONES LOCALES
===================================================================*/
#include "menuReports.h"  // El .h de este .cpp. Contiene las declaraciones de 'menuReports()', 'opcion1()', 'opcion2()', etc.


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
                            opcion1(objetos,gestores);
                            break;
                        case 2:
                            opcion2(objetos, gestores);
                            break;
                        case 4:
                            opcion3(objetos, gestores);
                            break;
                        case 6:
                            opcion4(objetos,gestores);
                            break;
                        case 8:
                            opcion5(objetos, gestores);
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
    gestor.gestorVenta.leerTodos(todasLasVentas);

    // Obtenemos el total de ventas para usarlo en el bucle
    size_t totalVentas = todasLasVentas.size();

    // Recorremos las ventas y filtramos (estilo "antiguo")
    for (size_t i = 0; i < totalVentas; i++) {

        // Accedemos a la venta actual usando el índice 'i'
        const Venta& vecVenta = todasLasVentas[i];

        // Ignoramos ventas inactivas (eliminadas)
        if (!vecVenta.getEstado()) {
            continue;
        }

        Fecha fechaVenta = vecVenta.getFecha(); // Obtenemos la fecha de la venta
        int fechaVentaInt = fechaVenta.getAnio() * 10000 + fechaVenta.getMes() * 100 + fechaVenta.getDia();

        // Comprobamos si la venta está dentro de nuestra "ventana" de 4 meses
        if (fechaVentaInt >= fechaLimiteInt && fechaVentaInt <= fechaActualInt) {
            ventasReporte.push_back(vecVenta); // ¡La añadimos al reporte!
        }
    }

    // --- 3. MOSTRAR LA TABLA FILTRADA ---

    rlutil::setColor(rlutil::MAGENTA);
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
        " ID VENTA ", " ID CLIENTE ", "L.VENDEDOR", "     TOTAL     ", "    FECHA   ", "  ESTADO  "
    };
    size_t espacios[OPCIONES] = { 10, 12, 10, 15, 12, 10 };

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

//opcion 2 cliente con mas productos elegidos en una venta

void opcion2(Contexto objetos, ContextoGestores& gestor) {

    // --- 1. READ DATA FROM FILES ---

    std::vector<DetalleVenta> detalles;
    // Attempt to read all detail records
    if (!gestor.gestorVenta.leerTodosDetalles(detalles)) {
        rlutil::setColor(rlutil::RED);
        rlutil::locate(15, 6);
        std::cout << "Error: No se pudo leer el archivo detalles_venta.dat." << std::endl;
        return;
    }

    std::vector<Venta> ventas;
    // Attempt to read all sale records
    if (!gestor.gestorVenta.leerTodos(ventas)) {
        rlutil::setColor(rlutil::RED);
        rlutil::locate(15, 6);
        std::cout << "Error: No se pudo leer el archivo ventas.dat." << std::endl;
        return;
    }

    // Check if there's any data to process
    if (detalles.empty() || ventas.empty()) {
        rlutil::setColor(rlutil::RED);
        rlutil::locate(15, 6);
        std::cout << "No hay ventas o detalles registrados para generar el reporte." << std::endl;
        return;
    }

    // --- 2. PROCESS DATA: COUNT ITEMS PER SALE & LINK SALE TO CLIENT ---

    // Map 1: Stores total items per Sale ID (key: idVenta, value: totalQuantity)
    std::map<int, int> itemsPorVenta;
    // Map 2: Stores which Client ID made which Sale ID (key: idVenta, value: idCliente)
    std::map<int, int> ventaACliente;

    // Populate the sale-to-client map, only including active sales
    for (const Venta& v : ventas) {
        if (v.getEstado()) { // Only consider active sales
            ventaACliente[v.getIdVenta()] = v.getIdCliente();
        }
    }

    // Sum quantities from details, but only for sales present in ventaACliente (i.e., active sales)
    for (const DetalleVenta& d : detalles) {
        // Check if the sale ID exists in our map of active sales
        if (ventaACliente.count(d.getIdVenta())) {
            // Add the quantity to the total for that specific sale ID
            itemsPorVenta[d.getIdVenta()] += d.getCantidad();
        }
    }

    // --- 3. FIND THE SALE WITH THE MOST ITEMS ---

    int maxItems = 0;           // To store the highest quantity found so far
    int idVentaGanadora = 0; // To store the ID of the sale with the most items

    // Iterate through the itemsPerVenta map to find the entry with the highest value
    for (auto const& par : itemsPorVenta) { // 'par' is a key-value pair (idVenta, totalQuantity)
        if (par.second > maxItems) {        // If current sale's quantity is higher than the max found...
            maxItems = par.second;          // ...update the max quantity
            idVentaGanadora = par.first;    // ...and store the ID of this winning sale
        }
    }

    // Check if we actually found a winning sale (i.e., if there were any items counted)
    if (idVentaGanadora == 0) {
        rlutil::setColor(rlutil::RED);
        rlutil::locate(15, 6);
        std::cout << "No se encontraron items en las ventas activas para generar el reporte." << std::endl;
        return;
    }

    // --- 4. FIND THE CLIENT AND DISPLAY RESULTS ---

    // Use the winning sale ID to find the corresponding client ID from our map
    int idClienteGanador = ventaACliente[idVentaGanadora];

    Cliente clienteGanador; // Create a client object to store the winner's data
    // Try to read the client's data from clientes.dat using their ID
    if (gestor.gestorC.leerPorID(idClienteGanador, clienteGanador)) {
        // Success! We found the client. Display the report.
        rlutil::setColor(rlutil::WHITE);
        rlutil::locate(15, 2);
        std::cout << "REPORTE: CLIENTE CON MAS PRODUCTOS EN UNA VENTA";

        rlutil::setColor(rlutil::MAGENTA);
        rlutil::locate(15, 6);
        std::cout << "El cliente cuya compra individual tuvo mas items es:";

        // Display client details
        rlutil::setColor(rlutil::WHITE);
        rlutil::locate(15, 8);
        std::cout << "ID Cliente: " << clienteGanador.getID();
        rlutil::locate(15, 9);
        std::cout << "Nombre:     " << clienteGanador.getNombre();
        rlutil::locate(15, 10);
        std::cout << "Telefono:   " << clienteGanador.getTelefono();

        // Display the winning sale details
        rlutil::locate(15, 12);
        std::cout << "Compro un total de " << maxItems << " items en la Venta ID #" << idVentaGanadora << ".";

        // Buscamos la venta ganadora en el vector 'ventas' para mostrar sus detalles
        Venta ventaInfoGanadora; // Objeto temporal para guardar la venta
        bool encontrada = false;
        for(const Venta& v : ventas){
            if(v.getIdVenta() == idVentaGanadora){
                ventaInfoGanadora = v;
                encontrada = true;
                break;
            }
        }
      if(encontrada){
            rlutil::locate(17, 14); std::cout << "- ID Venta:    " << ventaInfoGanadora.getIdVenta();
            rlutil::locate(17, 15); std::cout << "- L. Vendedor: " << ventaInfoGanadora.getLegajoVendedor();
            rlutil::locate(17, 16); std::cout << "- Monto Total: $" << std::fixed << std::setprecision(2) << ventaInfoGanadora.getTotal();
            rlutil::locate(17, 17); std::cout << "- Fecha:       "; ventaInfoGanadora.getFecha().MostrarF();
        } else {
             rlutil::locate(17, 14); std::cout << "(No se encontraron detalles adicionales de la venta)";
        }

        // Ajusta también la posición final del cursor
        rlutil::locate(15, 19); // Deja el cursor más abajo

        rlutil::locate(15, 18); // Deja el cursor más abajo

    } else {
        // Error case: The sale exists, but the client record is missing or deleted
        rlutil::setColor(rlutil::RED);
        rlutil::locate(15, 6);
        std::cout << "ERROR: Se encontro la Venta ID #" << idVentaGanadora
                  << " con " << maxItems << " items," << std::endl;
        rlutil::locate(15, 7);
        std::cout << "       pero no se pudo encontrar al Cliente ID #" << idClienteGanador
                  << " en el archivo." << std::endl;
    }
}

// --- Reporte 3: TOP 3 VENDEDORES ---
void opcion3(Contexto objetos, ContextoGestores& gestor) {

    // --- 1. LEER DATOS ---
    std::vector<Venta> ventas;
    if (!gestor.gestorVenta.leerTodos(ventas)) {
        rlutil::setColor(rlutil::RED); rlutil::locate(15, 6);
        std::cout << "Error: No se pudo leer el archivo ventas.dat." << std::endl;
        return;
    }

    std::vector<Vendedor> vendedores;
    // Leemos TODOS los vendedores (activos e inactivos)
    // porque una venta vieja podría apuntar a un vendedor ahora inactivo.
    if (!gestor.gestorV.leerTodos(vendedores)) {
        rlutil::setColor(rlutil::RED); rlutil::locate(15, 6);
        std::cout << "Error: No se pudo leer el archivo vendedores.dat." << std::endl;
        return;
    }

    if (ventas.empty() || vendedores.empty()) {
        rlutil::setColor(rlutil::RED); rlutil::locate(15, 6);
        std::cout << "No hay ventas o vendedores registrados para generar el reporte." << std::endl;
        return;
    }

    // --- 2. ACUMULAR VENTAS POR VENDEDOR (Estilo Array) ---
    // Creamos un vector para guardar los totales, del mismo tamaño que el de vendedores.
    // El índice 'i' en 'totalesVendedor' corresponde al vendedor en 'vendedores[i]'.
    std::vector<double> totalesVendedor(vendedores.size(), 0.0);
    bool huboVentasActivas = false; // Bandera para saber si encontramos alguna venta válida

    for (const Venta& v : ventas) {
        if (v.getEstado()) { // Solo ventas activas
            huboVentasActivas = true;
            int legajoActual = v.getLegajoVendedor();

            // Buscamos el índice del vendedor con ese legajo
            for (size_t i = 0; i < vendedores.size(); ++i) {
                // Asumimos que getID() en Vendedor devuelve el legajo
                if (vendedores[i].getID() == legajoActual) {
                    totalesVendedor[i] += v.getTotal(); // Sumamos al total de ese índice
                    break; // Encontramos al vendedor, pasamos a la siguiente venta
                }
            }
            // Si el legajo de la venta no corresponde a ningún vendedor, se ignora.
        }
    }

    if (!huboVentasActivas) {
        rlutil::setColor(rlutil::RED); rlutil::locate(15, 6);
        std::cout << "No se encontraron ventas activas para generar el reporte." << std::endl;
        return;
    }

    // --- 3. ENCONTRAR EL TOP 3 (Manualmente) ---
    // Guardamos los índices (posición en el vector 'vendedores') de los 3 mejores
    int topIndices[3] = {-1, -1, -1};
    // Guardamos los totales de esos 3 mejores
    double topTotales[3] = {-1.0, -1.0, -1.0}; // Usamos -1 para saber si encontramos alguno

    for (size_t i = 0; i < totalesVendedor.size(); ++i) {
        // Si el total actual es mayor que el 1ro del ranking...
        if (totalesVendedor[i] > topTotales[0]) {
            // Bajamos el 1ro a 2do, y el 2do a 3ro
            topTotales[2] = topTotales[1]; topIndices[2] = topIndices[1];
            topTotales[1] = topTotales[0]; topIndices[1] = topIndices[0];
            // Ponemos el nuevo como 1ro
            topTotales[0] = totalesVendedor[i]; topIndices[0] = i;
        }
        // Si no es mayor que el 1ro, pero sí mayor que el 2do...
        else if (totalesVendedor[i] > topTotales[1]) {
            // Bajamos el 2do a 3ro
            topTotales[2] = topTotales[1]; topIndices[2] = topIndices[1];
            // Ponemos el nuevo como 2do
            topTotales[1] = totalesVendedor[i]; topIndices[1] = i;
        }
        // Si no es mayor que 1ro ni 2do, pero sí mayor que el 3ro...
        else if (totalesVendedor[i] > topTotales[2]) {
            // Lo ponemos como 3ro
            topTotales[2] = totalesVendedor[i]; topIndices[2] = i;
        }
    }

    // --- 4. MOSTRAR RESULTADOS ---
    rlutil::setColor(rlutil::WHITE);
    rlutil::locate(15, 2);
    std::cout << "REPORTE: TOP 3 VENDEDORES POR MONTO TOTAL VENDIDO (SIMPLE)";

    rlutil::setColor(rlutil::MAGENTA);
    rlutil::locate(15, 6); std::cout << "Puesto | Legajo | Nombre Vendedor        | Total Vendido";
    rlutil::locate(15, 7); std::cout << "-------|--------|------------------------|----------------";

    rlutil::setColor(rlutil::WHITE);
    int vendedoresMostrados = 0;
    for (int i = 0; i < 3; ++i) {
        // Si encontramos un vendedor en esta posición del ranking (índice != -1)...
        if (topIndices[i] != -1) {
            vendedoresMostrados++;
            int indiceVendedor = topIndices[i];
            double totalVendido = topTotales[i];

            // Obtenemos los datos del vendedor usando el índice
            int legajo = vendedores[indiceVendedor].getID();
            std::string nombre = vendedores[indiceVendedor].getNombre();

            // Mostramos la línea
            rlutil::locate(15, 8 + i);
            std::cout << "   " << (i + 1) << "   | "          // Puesto
                      << std::setw(6) << legajo << " | "     // Legajo
                      << std::left << std::setw(22) << nombre.substr(0, 22) << std::right << " | $" // Nombre
                      << std::fixed << std::setprecision(2) << std::setw(12) << totalVendido; // Total
        }
    }

    // Si no se mostró ningún vendedor (raro, pero posible si todos tienen total 0)
    if(vendedoresMostrados == 0){
        rlutil::setColor(rlutil::RED); rlutil::locate(15, 8);
        std::cout << "No hay vendedores con ventas registradas." << std::endl;
    }

    rlutil::locate(15, 8 + vendedoresMostrados + 1); // Deja el cursor abajo
}

// --- Reporte 4: PRODUCTO MÁS VENDIDO (Versión Simple) ---
void opcion4(Contexto objetos, ContextoGestores& gestor) {

    // --- 1. LEER DATOS ---
    std::vector<DetalleVenta> detalles;
    if (!gestor.gestorVenta.leerTodosDetalles(detalles)) {
        rlutil::setColor(rlutil::RED); rlutil::locate(15, 6);
        std::cout << "Error: No se pudo leer el archivo detalles_venta.dat." << std::endl;
        return;
    }

    std::vector<Producto> productos;
    // Leemos TODOS los productos
    if (!gestor.gestorP.leerTodos(productos)) {
        rlutil::setColor(rlutil::RED); rlutil::locate(15, 6);
        std::cout << "Error: No se pudo leer el archivo productos.dat." << std::endl;
        return;
    }

    std::vector<Venta> ventas;
    // Leemos todas las ventas para chequear el estado
    if (!gestor.gestorVenta.leerTodos(ventas)) {
        rlutil::setColor(rlutil::RED); rlutil::locate(15, 6);
        std::cout << "Error: No se pudo leer el archivo ventas.dat." << std::endl;
        return;
    }

    if (detalles.empty() || productos.empty()) {
        rlutil::setColor(rlutil::RED); rlutil::locate(15, 6);
        std::cout << "No hay detalles de venta o productos registrados." << std::endl;
        return;
    }

    // --- 2. ACUMULAR CANTIDADES VENDIDAS POR PRODUCTO ---
    // Vector para guardar la cantidad vendida. El índice 'i' corresponde a 'productos[i]'.
    std::vector<int> cantidadVendida(productos.size(), 0);
    bool huboVentasActivas = false;

    // Recorremos cada detalle de venta
    for (const DetalleVenta& d : detalles) {
        bool ventaEsActiva = false;
        // Buscamos la venta correspondiente a este detalle
        for (const Venta& v : ventas) {
            if (v.getIdVenta() == d.getIdVenta()) {
                if (v.getEstado()) { // Si la encontramos y está activa...
                    ventaEsActiva = true;
                    huboVentasActivas = true;
                }
                break; // Encontramos la venta, no hace falta seguir buscando
            }
        }

        // Si la venta del detalle estaba activa...
        if (ventaEsActiva) {
            int idProductoActual = d.getIdProducto();
            // Buscamos el índice de este producto en nuestro vector de productos
            for (size_t i = 0; i < productos.size(); ++i) {
                if (productos[i].getID() == idProductoActual) {
                    cantidadVendida[i] += d.getCantidad(); // Sumamos la cantidad
                    break; // Encontramos el producto, pasamos al siguiente detalle
                }
            }
            // Si el idProducto del detalle no existe en productos.dat, se ignora.
        }
    }

    if (!huboVentasActivas) {
        rlutil::setColor(rlutil::RED); rlutil::locate(15, 6);
        std::cout << "No se encontraron ventas activas con detalles." << std::endl;
        return;
    }

    // --- 3. ENCONTRAR EL PRODUCTO MÁS VENDIDO ---
    int maxCantidad = -1; // Empezamos con -1 para asegurarnos de encontrar el primero
    int indiceGanador = -1; // Índice del producto más vendido en el vector 'productos'

    for (size_t i = 0; i < cantidadVendida.size(); ++i) {
        if (cantidadVendida[i] > maxCantidad) {
            maxCantidad = cantidadVendida[i];
            indiceGanador = i;
        }
    }

    // --- 4. MOSTRAR RESULTADOS ---
    rlutil::setColor(rlutil::WHITE);
    rlutil::locate(15, 2);
    std::cout << "REPORTE: PRODUCTO MAS VENDIDO (POR UNIDADES)";

    // Si encontramos un ganador (maxCantidad >= 0)...
    if (indiceGanador != -1 && maxCantidad >= 0) {
        // Obtenemos los datos del producto usando el índice ganador
        int idProd = productos[indiceGanador].getID();
        std::string nombreProd = productos[indiceGanador].getNombre();
        double precioProd = productos[indiceGanador].getPrecio(); // Info extra

        rlutil::setColor(rlutil::MAGENTA);
        rlutil::locate(15, 6); std::cout << "El producto mas vendido en unidades es:";

        rlutil::setColor(rlutil::WHITE);
        rlutil::locate(15, 8); std::cout << "ID Producto: " << idProd;
        rlutil::locate(15, 9); std::cout << "Nombre:      " << nombreProd;
        rlutil::locate(15, 10); std::cout << "Precio Unit: $" << std::fixed << std::setprecision(2) << precioProd;
        rlutil::locate(15, 12); std::cout << "Se vendieron un total de " << maxCantidad << " unidades.";

         rlutil::locate(15, 14); // Deja el cursor abajo

    } else {
        // Si no se vendió ningún producto (raro, pero posible)
        rlutil::setColor(rlutil::RED);
        rlutil::locate(15, 6);
        std::cout << "No se registraron unidades vendidas en ventas activas." << std::endl;
         rlutil::locate(15, 8); // Deja el cursor abajo
    }
}

// --- Reporte 5: VENTA CON MAYOR MONTO (Versión Simple) ---
void opcion5(Contexto objetos, ContextoGestores& gestor) {

    // --- 1. LEER DATOS ---
    std::vector<Venta> ventas;
    if (!gestor.gestorVenta.leerTodos(ventas)) {
        rlutil::setColor(rlutil::RED); rlutil::locate(15, 6);
        std::cout << "Error: No se pudo leer el archivo ventas.dat." << std::endl;
        return;
    }

    if (ventas.empty()) {
        rlutil::setColor(rlutil::RED); rlutil::locate(15, 6);
        std::cout << "No hay ventas registradas para generar el reporte." << std::endl;
        return;
    }

    // --- 2. ENCONTRAR LA VENTA CON MAYOR MONTO ---
    double maxTotal = -1.0; // Empezamos con -1 para encontrar la primera venta válida
    int indiceVentaGanadora = -1; // Índice de la venta ganadora en el vector 'ventas'

    for (size_t i = 0; i < ventas.size(); ++i) {
        if (ventas[i].getEstado()) { // Solo ventas activas
            if (ventas[i].getTotal() > maxTotal) {
                maxTotal = ventas[i].getTotal();
                indiceVentaGanadora = i;
            }
        }
    }

    // --- 3. MOSTRAR RESULTADOS ---
    rlutil::setColor(rlutil::WHITE);
    rlutil::locate(15, 2);
    std::cout << "REPORTE: VENTA CON MAYOR MONTO TOTAL";

    // Si encontramos una venta ganadora...
    if (indiceVentaGanadora != -1) {
        // Obtenemos el objeto Venta ganador usando el índice
        const Venta& ventaGanadora = ventas[indiceVentaGanadora];

        rlutil::setColor(rlutil::MAGENTA);
        rlutil::locate(15, 6); std::cout << "La venta registrada con el mayor monto total es:";

        // Mostramos los detalles de la venta
        rlutil::setColor(rlutil::WHITE);
        rlutil::locate(15, 8);  std::cout << "ID Venta:      " << ventaGanadora.getIdVenta();
        rlutil::locate(15, 9);  std::cout << "ID Cliente:    " << ventaGanadora.getIdCliente();
        rlutil::locate(15, 10); std::cout << "L. Vendedor:   " << ventaGanadora.getLegajoVendedor();
        rlutil::locate(15, 11); std::cout << "Monto Total:   $" << std::fixed << std::setprecision(2) << ventaGanadora.getTotal();
        rlutil::locate(15, 12); std::cout << "Fecha:         "; ventaGanadora.getFecha().MostrarF();

        rlutil::locate(15, 14); // Deja el cursor abajo

    } else {
        // Si no se encontró ninguna venta activa
        rlutil::setColor(rlutil::RED);
        rlutil::locate(15, 6);
        std::cout << "No se encontraron ventas activas para generar el reporte." << std::endl;
        rlutil::locate(15, 8); // Deja el cursor abajo
    }
}
