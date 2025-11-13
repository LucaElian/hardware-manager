/*=======================
LIBRERÍAS ESTÁNDAR C++
=========================*/
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <map>
#include <iomanip>
#include <limits>
#include <algorithm>
#include <utility>

/*===================================================================
NÚCLEO DEL PROYECTO (DATOS)
===================================================================*/
#include "ContextoGestores.h"
#include "gestorVenta.h"
#include "archivoManager.h"
#include "clsVenta.h"
#include "clsDetalleVenta.h"
#include "clsCliente.h"
#include "clsVendedor.h"
#include "clsProducto.h"

/*===================================================================
INTERFAZ DE USUARIO (UI)
===================================================================*/
#include "artworks.h"
#include "rlutil.h"
#include "uiManager.h"
#include "constantes.h"

/*===================================================================
HACK DE COMPILACIÓN (rlutil vs C++)
===================================================================*/
#define byte windows_byte
#include "rlutil.h"
#undef byte

/*===================================================================
DECLARACIONES LOCALES
===================================================================*/
#include "menuReports.h"

using namespace std;

void menuReports(Contexto objetos, ContextoGestores& gestores)
{
    const int TAMANIO_MENU = 6;
    string opciones[TAMANIO_MENU] =
    {
        "VENTAS DEL ULTIMO CUATRIMESTRE",
        "CLIENTE CON MAS PRODUCTOS",
        "TOP 3 VENDEDORES",
        "PRODUCTO MAS VENDIDO",
        "VENTA CON MAYOR MONTO",
        "SALIR"
    };

    // Constantes de navegación del menú
    const int INICIO_MENU_Y = 7;
    const int POSICION_CURSOR_X = 44;
    const int ESPACIO_MENU = 13;
    const int OPCION_MAXIMA = 10;
    const int PASO_OPCION = 2;
    const int CURSOR_MENU = 175;

    while(true)
    {
        int opcionSeleccionada = 0;
        bool cursorActivo = true;
        system("cls");

        menu("R E P O R T E S", opciones, INICIO_MENU_Y, TAMANIO_MENU);

        while(cursorActivo == true)
        {
            rlutil::locate(POSICION_CURSOR_X, ESPACIO_MENU + opcionSeleccionada);
            cout << (char)CURSOR_MENU;

            int teclaPresionada = rlutil::getkey();

            switch(teclaPresionada)
            {
            case TECLA_ARRIBA:
                rlutil::locate(POSICION_CURSOR_X, ESPACIO_MENU + opcionSeleccionada);
                cout << " ";
                opcionSeleccionada -= PASO_OPCION;
                if(opcionSeleccionada < 0) opcionSeleccionada = OPCION_MAXIMA;
                break;

            case TECLA_ABAJO:
                rlutil::locate(POSICION_CURSOR_X, ESPACIO_MENU + opcionSeleccionada);
                cout << " ";
                opcionSeleccionada += PASO_OPCION;
                if(opcionSeleccionada > OPCION_MAXIMA) opcionSeleccionada = 0;
                break;

            case TECLA_ENTER:
                system("cls");
                cursorActivo = false;
                switch(opcionSeleccionada)
                {
                case 0:
                    opcion1(objetos, gestores);
                    break;
                case 2:
                    opcion2(objetos, gestores);
                    break;
                case 4:
                    opcion3(objetos, gestores);
                    break;
                case 6:
                    opcion4(objetos, gestores);
                    break;
                case 8:
                    opcion5(objetos, gestores);
                    break;
                case 10:
                    return;
                }
                rlutil::setColor(rlutil::BLACK); // Reset de color
                system("pause");
            }
        }
    }
}

//--- OPCIONES DE REPORTES ---

void opcion1(Contexto objetos, ContextoGestores& gestor)
{
    // Obtenemos la fecha actual
    time_t now = time(0);
    tm* ltm = localtime(&now);
    int anioActual = 1900 + ltm->tm_year;
    int mesActual = 1 + ltm->tm_mon;
    int diaActual = ltm->tm_mday;

    // Calculamos la fecha límite (4 meses atrás)
    int anioLimite = anioActual;
    int mesLimite = mesActual - 4;
    if (mesLimite <= 0)
    {
        mesLimite += 12;
        anioLimite -= 1;
    }

    // Convertimos a enteros YYYYMMDD para comparar
    int fechaActualInt = anioActual * 10000 + mesActual * 100 + diaActual;
    int fechaLimiteInt = anioLimite * 10000 + mesLimite * 100 + diaActual;

    vector<Venta> todasLasVentas;
    vector<Venta> ventasReporte;
    gestor.gestorVenta.leerTodos(todasLasVentas);

    for (size_t i = 0; i < todasLasVentas.size(); i++)
    {
        const Venta& vecVenta = todasLasVentas[i];

        if (!vecVenta.getEstado())
        {
            continue;
        }

        Fecha fechaVenta = vecVenta.getFecha();
        int fechaVentaInt = fechaVenta.getAnio() * 10000 + fechaVenta.getMes() * 100 + fechaVenta.getDia();

        // Filtramos por la ventana de 4 meses
        if (fechaVentaInt >= fechaLimiteInt && fechaVentaInt <= fechaActualInt)
        {
            ventasReporte.push_back(vecVenta);
        }
    }

    rlutil::setColor(rlutil::MAGENTA);
    rlutil::locate(15, 2);
    cout << "REPORTE: VENTAS DE LOS ULTIMOS 4 MESES (Desde " << diaActual << "/" << mesLimite << "/" << anioLimite << " hasta Hoy)";

    if (ventasReporte.empty())
    {
        rlutil::setColor(rlutil::RED);
        rlutil::locate(15, 6);
        cout << "No se encontraron ventas activas en este período." << endl;
        return;
    }

    const size_t OPCIONES = 6;
    const int posX = 15;
    const int posY = 4;
    string titulos[OPCIONES] =
    {
        " ID VENTA ", " ID CLIENTE ", "L.VENDEDOR", "    TOTAL    ", "   FECHA    ", "  ESTADO  "
    };
    size_t espacios[OPCIONES] = { 10, 12, 10, 15, 12, 10 };

    mostrar_encabezado(titulos, posX, posY, OPCIONES, espacios);

    int cont_lineas = 0;
    //hecho a mano porq llamando a los metodos de venta se corrompe todo
    for (const Venta& venta : ventasReporte)
    {
        int currentY = posY + 3 + cont_lineas;
        int currentX = posX; // Empieza en X=15

        //ID VENTA (Ancho 10)
        rlutil::locate(currentX, currentY);
        rlutil::setColor(rlutil::MAGENTA); std::cout << (char)ASCII_BARRA_VERTICAL;
        rlutil::setColor(rlutil::WHITE);
        rlutil::locate(currentX + 1, currentY); std::cout << venta.getIdVenta();
        currentX += espacios[0] + 1; // Avanza 10 + 1

        //ID CLIENTE (Ancho 12)
        rlutil::locate(currentX, currentY);
        rlutil::setColor(rlutil::MAGENTA); std::cout << (char)ASCII_BARRA_VERTICAL;
        rlutil::setColor(rlutil::WHITE);
        rlutil::locate(currentX + 1, currentY); std::cout << venta.getIdCliente();
        currentX += espacios[1] + 1; // Avanza 12 + 1

        //L.VENDEDOR (Ancho 10)
        rlutil::locate(currentX, currentY);
        rlutil::setColor(rlutil::MAGENTA); std::cout << (char)ASCII_BARRA_VERTICAL;
        rlutil::setColor(rlutil::WHITE);
        rlutil::locate(currentX + 1, currentY); std::cout << venta.getLegajoVendedor();
        currentX += espacios[2] + 1; // Avanza 10 + 1

        //TOTAL (Ancho 15)
        rlutil::locate(currentX, currentY);
        rlutil::setColor(rlutil::MAGENTA); std::cout << (char)ASCII_BARRA_VERTICAL;
        rlutil::setColor(rlutil::WHITE);
        rlutil::locate(currentX + 1, currentY); std::cout << std::fixed << std::setprecision(2) << venta.getTotal();
        currentX += espacios[3] + 1; // Avanza 15 + 1

        //FECHA (Ancho 12)
        rlutil::locate(currentX, currentY);
        rlutil::setColor(rlutil::MAGENTA); std::cout << (char)ASCII_BARRA_VERTICAL;
        rlutil::setColor(rlutil::WHITE);
        rlutil::locate(currentX + 1, currentY); venta.getFecha().MostrarF();
        currentX += espacios[4] + 1; // Avanza 12 + 1

        //ESTADO (Ancho 10)
        rlutil::locate(currentX, currentY);
        rlutil::setColor(rlutil::MAGENTA); std::cout << (char)ASCII_BARRA_VERTICAL;
        rlutil::setColor(rlutil::WHITE);
        rlutil::locate(currentX + 1, currentY); std::cout << (venta.getEstado() ? "PAGADO" : "ADEUDADO");
        currentX += espacios[5]; // Avanza 10

        // Barra final de la fila
        rlutil::locate(currentX + 1, currentY);
        rlutil::setColor(rlutil::MAGENTA); std::cout << (char)ASCII_BARRA_VERTICAL;

        cont_lineas++;
    }

    barra_final(OPCIONES, posX, posY + 3 + cont_lineas, espacios);
    rlutil::locate(posX, posY + 3 + cont_lineas + 2);
}

void opcion2(Contexto objetos, ContextoGestores& gestor)
{
    vector<DetalleVenta> detalles;
    gestor.gestorVenta.leerTodosDetalles(detalles);
    vector<Venta> ventas;
    gestor.gestorVenta.leerTodos(ventas);

    if (detalles.empty() || ventas.empty())
    {
        rlutil::setColor(rlutil::RED);
        rlutil::locate(15, 6);
        cout << "No hay ventas o detalles registrados para generar el reporte." << endl;
        return;
    }

    map<int, int> itemsPorVenta; // <idVenta, totalItems>
    map<int, int> ventaACliente; // <idVenta, idCliente>

    for (const Venta& v : ventas)
    {
        if (v.getEstado())
        {
            ventaACliente[v.getIdVenta()] = v.getIdCliente();
        }
    }

    //sumo items por cada venta activa
    for (const DetalleVenta& d : detalles)
    {
        if (ventaACliente.count(d.getIdVenta()))
        {
            itemsPorVenta[d.getIdVenta()] += d.getCantidad();
        }
    }

    //venta ganadora
    int maxItems = 0;
    int idVentaGanadora = 0;
    for (auto const& par : itemsPorVenta)
    {
        if (par.second > maxItems)
        {
            maxItems = par.second;
            idVentaGanadora = par.first;
        }
    }

    if (idVentaGanadora == 0)
    {
        rlutil::setColor(rlutil::RED);
        rlutil::locate(15, 6);
        cout << "No se encontraron items en las ventas activas." << endl;
        return;
    }

    int idClienteGanador = ventaACliente[idVentaGanadora];
    Cliente clienteGanador;
    Venta ventaInfoGanadora;
    for(const Venta& v : ventas)
    {
        if(v.getIdVenta() == idVentaGanadora)
        {
            ventaInfoGanadora = v;
            break;
        }
    }

    if (gestor.gestorC.leerPorID(idClienteGanador, clienteGanador))
    {
        rlutil::setColor(rlutil::WHITE);
        rlutil::locate(15, 2);
        cout << "REPORTE: CLIENTE CON MAS PRODUCTOS EN UNA VENTA";

        rlutil::setColor(rlutil::MAGENTA);
        rlutil::locate(15, 6);
        cout << "El cliente cuya compra individual tuvo mas items es:";

        rlutil::setColor(rlutil::WHITE);
        rlutil::locate(15, 8);
        cout << "ID Cliente: " << clienteGanador.getID();
        rlutil::locate(15, 9);
        cout << "Nombre:     " << clienteGanador.getNombre();
        rlutil::locate(15, 10);
        cout << "Telefono:   " << clienteGanador.getTelefono();

        rlutil::locate(15, 12);
        cout << "Compro un total de " << maxItems << " items en la Venta ID #" << idVentaGanadora << ":";

        rlutil::locate(17, 14);
        cout << "- ID Venta:    " << ventaInfoGanadora.getIdVenta();
        rlutil::locate(17, 15);
        cout << "- L. Vendedor: " << ventaInfoGanadora.getLegajoVendedor();
        rlutil::locate(17, 16);
        cout << "- Monto Total: $" << fixed << setprecision(2) << ventaInfoGanadora.getTotal();
        rlutil::locate(17, 17);
        cout << "- Fecha:       ";
        ventaInfoGanadora.getFecha().MostrarF();

        rlutil::locate(15, 19);

    }
    else
    {
        rlutil::setColor(rlutil::RED);
        rlutil::locate(15, 6);
        cout << "ERROR: Venta #" << idVentaGanadora << " encontrada, pero Cliente ID #" << idClienteGanador << " no." << endl;
    }
}

void opcion3(Contexto objetos, ContextoGestores& gestor)
{
    vector<Venta> ventas;
    gestor.gestorVenta.leerTodos(ventas);
    vector<Vendedor> vendedores;
    gestor.gestorV.leerTodos(vendedores);

    if (ventas.empty() || vendedores.empty())
    {
        rlutil::setColor(rlutil::RED);
        rlutil::locate(15, 6);
        cout << "No hay ventas o vendedores registrados." << endl;
        return;
    }

    // Vector contador paralelo al vector 'vendedores'
    vector<double> totalesVendedor(vendedores.size(), 0.0);
    bool huboVentasActivas = false;

    for (const Venta& v : ventas)
    {
        if (v.getEstado())
        {
            huboVentasActivas = true;
            for (size_t i = 0; i < vendedores.size(); ++i)
            {
                if (vendedores[i].getID() == v.getLegajoVendedor())
                {
                    totalesVendedor[i] += v.getTotal();
                    break;
                }
            }
        }
    }

    if (!huboVentasActivas)
    {
        rlutil::setColor(rlutil::RED);
        rlutil::locate(15, 6);
        cout << "No se encontraron ventas activas." << endl;
        return;
    }

    // Búsqueda manual del Top 3
    int topIndices[3] = {-1, -1, -1};
    double topTotales[3] = {-1.0, -1.0, -1.0};

    for (size_t i = 0; i < totalesVendedor.size(); ++i)
    {
        if (totalesVendedor[i] > topTotales[0])
        {
            topTotales[2] = topTotales[1];
            topIndices[2] = topIndices[1];
            topTotales[1] = topTotales[0];
            topIndices[1] = topIndices[0];
            topTotales[0] = totalesVendedor[i];
            topIndices[0] = i;
        }
        else if (totalesVendedor[i] > topTotales[1])
        {
            topTotales[2] = topTotales[1];
            topIndices[2] = topIndices[1];
            topTotales[1] = totalesVendedor[i];
            topIndices[1] = i;
        }
        else if (totalesVendedor[i] > topTotales[2])
        {
            topTotales[2] = totalesVendedor[i];
            topIndices[2] = i;
        }
    }

    // Mostrar Ranking
    rlutil::setColor(rlutil::WHITE);
    rlutil::locate(15, 2);
    cout << "REPORTE: TOP 3 VENDEDORES POR MONTO TOTAL VENDIDO";

    rlutil::setColor(rlutil::MAGENTA);
    rlutil::locate(15, 6);
    cout << "Puesto | Legajo | Nombre Vendedor        | Total Vendido";
    rlutil::locate(15, 7);
    cout << "-------|--------|------------------------|----------------";

    rlutil::setColor(rlutil::WHITE);
    int vendedoresMostrados = 0;
    for (int i = 0; i < 3; ++i)
    {
        if (topIndices[i] != -1 && topTotales[i] > 0)   // solo muestro si vendieron algo
        {
            vendedoresMostrados++;
            int indiceVendedor = topIndices[i];

            rlutil::locate(15, 8 + i);
            cout << "   " << (i + 1) << "   | "
                 << setw(6) << vendedores[indiceVendedor].getID() << " | "
                 << left << setw(22) << string(vendedores[indiceVendedor].getNombre()).substr(0, 22) << right << " | $"
                 << fixed << setprecision(2) << setw(12) << topTotales[i];
        }
    }

    if(vendedoresMostrados == 0)
    {
        rlutil::setColor(rlutil::RED);
        rlutil::locate(15, 8);
        cout << "No hay vendedores con ventas registradas." << endl;
    }
    rlutil::locate(15, 8 + vendedoresMostrados + 1);
}

void opcion4(Contexto objetos, ContextoGestores& gestor)
{
    vector<DetalleVenta> detalles;
    gestor.gestorVenta.leerTodosDetalles(detalles);
    vector<Producto> productos;
    gestor.gestorP.leerTodos(productos);
    vector<Venta> ventas;
    gestor.gestorVenta.leerTodos(ventas);

    if (detalles.empty() || productos.empty())
    {
        rlutil::setColor(rlutil::RED);
        rlutil::locate(15, 6);
        cout << "No hay detalles de venta o productos registrados." << endl;
        return;
    }

    // Vector contador paralelo al vector 'productos'
    vector<int> cantidadVendida(productos.size(), 0);
    bool huboVentasActivas = false;

    for (const DetalleVenta& d : detalles)
    {
        bool ventaEsActiva = false;
        // Optimizacion: Usar un map para chequear estado de venta si 'ventas' es muy grande
        for (const Venta& v : ventas)
        {
            if (v.getIdVenta() == d.getIdVenta())
            {
                if (v.getEstado())
                {
                    ventaEsActiva = true;
                    huboVentasActivas = true;
                }
                break;
            }
        }

        if (ventaEsActiva)
        {
            for (size_t i = 0; i < productos.size(); ++i)
            {
                if (productos[i].getID() == d.getIdProducto())
                {
                    cantidadVendida[i] += d.getCantidad();
                    break;
                }
            }
        }
    }

    if (!huboVentasActivas)
    {
        rlutil::setColor(rlutil::RED);
        rlutil::locate(15, 6);
        cout << "No se encontraron ventas activas con detalles." << endl;
        return;
    }

    // Buscamos el producto ganador
    int maxCantidad = 0; // Empezamos en 0
    int indiceGanador = -1;

    for (size_t i = 0; i < cantidadVendida.size(); ++i)
    {
        if (cantidadVendida[i] > maxCantidad)
        {
            maxCantidad = cantidadVendida[i];
            indiceGanador = i;
        }
    }

    rlutil::setColor(rlutil::WHITE);
    rlutil::locate(15, 2);
    cout << "REPORTE: PRODUCTO MAS VENDIDO (POR UNIDADES)";

    if (indiceGanador != -1)
    {
        rlutil::setColor(rlutil::MAGENTA);
        rlutil::locate(15, 6);
        cout << "El producto mas vendido en unidades es:";

        rlutil::setColor(rlutil::WHITE);
        rlutil::locate(15, 8);
        cout << "ID Producto: " << productos[indiceGanador].getID();
        rlutil::locate(15, 9);
        cout << "Nombre:      " << productos[indiceGanador].getNombre();
        rlutil::locate(15, 10);
        cout << "Precio Unit: $" << fixed << setprecision(2) << productos[indiceGanador].getPrecio();
        rlutil::locate(15, 12);
        cout << "Se vendieron un total de " << maxCantidad << " unidades.";
        rlutil::locate(15, 14);

    }
    else
    {
        rlutil::setColor(rlutil::RED);
        rlutil::locate(15, 6);
        cout << "No se registraron unidades vendidas en ventas activas." << endl;
        rlutil::locate(15, 8);
    }
}

void opcion5(Contexto objetos, ContextoGestores& gestor)
{
    vector<Venta> ventas;
    if (!gestor.gestorVenta.leerTodos(ventas))
    {
        rlutil::setColor(rlutil::RED);
        rlutil::locate(15, 6);
        cout << "Error: No se pudo leer el archivo ventas.dat." << endl;
        return;
    }

    if (ventas.empty())
    {
        rlutil::setColor(rlutil::RED);
        rlutil::locate(15, 6);
        cout << "No hay ventas registradas para generar el reporte." << endl;
        return;
    }

    // Buscamos la venta ganadora
    double maxTotal = -1.0;
    int indiceVentaGanadora = -1;

    for (size_t i = 0; i < ventas.size(); ++i)
    {
        if (ventas[i].getEstado() && ventas[i].getTotal() > maxTotal)
        {
            maxTotal = ventas[i].getTotal();
            indiceVentaGanadora = i;
        }
    }

    rlutil::setColor(rlutil::WHITE);
    rlutil::locate(15, 2);
    cout << "REPORTE: VENTA CON MAYOR MONTO TOTAL";

    if (indiceVentaGanadora != -1)
    {
        const Venta& ventaGanadora = ventas[indiceVentaGanadora];

        rlutil::setColor(rlutil::MAGENTA);
        rlutil::locate(15, 6);
        cout << "La venta registrada con el mayor monto total es:";

        rlutil::setColor(rlutil::WHITE);
        rlutil::locate(15, 8);
        cout << "ID Venta:      " << ventaGanadora.getIdVenta();
        rlutil::locate(15, 9);
        cout << "ID Cliente:    " << ventaGanadora.getIdCliente();
        rlutil::locate(15, 10);
        cout << "L. Vendedor:   " << ventaGanadora.getLegajoVendedor();
        rlutil::locate(15, 11);
        cout << "Monto Total:   $" << fixed << setprecision(2) << ventaGanadora.getTotal();
        rlutil::locate(15, 12);
        cout << "Fecha:         ";
        ventaGanadora.getFecha().MostrarF();
        rlutil::locate(15, 14);

    }
    else
    {
        rlutil::setColor(rlutil::RED);
        rlutil::locate(15, 6);
        cout << "No se encontraron ventas activas para generar el reporte." << endl;
        rlutil::locate(15, 8);
    }
}
