#include <iostream>
#include <iomanip>

using namespace std;

#include "clsVenta.h"
#include "clsCliente.h"
#include "clsVendedor.h"
#include "clsProducto.h"
#include "utilidades.h"
#include "ContextoGestores.h"
#include "uiManager.h"
#include "artworks.h"
#include "constantes.h"
#include "gestorVenta.h"

#define byte windows_byte
#include "rlutil.h"
#undef byte

static ArchivoManager<Venta> archivo(ARCHIVO_VENTAS);

Venta::Venta(int _id,
             int _idVenta,
             int _idCliente,
             int _legajoVendedor,
             double _total,
             bool _estado,
             Fecha _fechaVenta)
    : Entidad(_id, _estado, _fechaVenta)
{
    idVenta = _idVenta;
    idCliente = _idCliente;
    legajoVendedor = _legajoVendedor;
    total = _total;

    // Revisa si la fecha que llegó es la default (1/1/1)
    if (_fechaVenta.getDia() == 1 && _fechaVenta.getMes() == 1 && _fechaVenta.getAnio() == 1)
    {

        // 4. Si era default, la pisa con la fecha actual del sistema
        time_t now = time(0);
        tm* ltm = localtime(&now);
        Fecha fechaActual(ltm->tm_mday, ltm->tm_mon + 1, 1900 + ltm->tm_year);

        this->fechaVenta = fechaActual; // Actualiza el miembro local
        setFecha(fechaActual.getDia(), fechaActual.getMes(), fechaActual.getAnio()); // Actualiza el miembro de la clase base (Entidad)

    }
    else
    {
        // 5. Si no era default, solo setea el miembro local
        this->fechaVenta = _fechaVenta;
    }
}

// Destructor
Venta::~Venta() {}

// Metodos virtuales heredados

void Venta::cargar()
{
    string datos[VENTA_OPCIONES-1] =
    {
        "ID CLIENTE: [           ]",
        "LEGAJO VENDEDOR: [           ]",
        "PAGADO: [    ]",
        "FECHA: [ __/__/____ ]",
        "ID VENTA: [           ]"
    };

    agregar("A G R E G A R  V E N T A", VENTA_INICIO_TITULO, VENTA_OPCIONES-2);
    agregar_opciones(datos, VENTA_INICIO_TABLA, VENTA_OPCIONES-1, datos[VENTA_OPCIONES-2], 58);

    rlutil::setColor(rlutil::RED);
    rlutil::locate(55, 12);
    cout << "SOLO ACEPTADO: SI/si o NO/no";

    rlutil::locate(54, 14);
    cout << "FECHA ACEPTADA: dd/mm/aaaa o d/m/aaaa";

    rlutil::setColor(rlutil::MAGENTA);
    rlutil::showcursor();

    ContextoGestores contexto;
    int cantidad = contexto.gestorVenta.cantidadRegistros();
    setIdVenta(cantidad + 1);
    rlutil::locate(70, 8); /// ID VENTA
    cout << idVenta;

    bool valido = false;
    Cliente cliente;

    while(!valido)
    {
        rlutil::locate(46, 8); /// ID CLIENTE
        idCliente = cargarInt(9);

        if(contexto.gestorC.leerPorID(idCliente, cliente))
        {
            break;
        }

        else
        {
            rlutil::setColor(rlutil::RED);
            rlutil::locate(44, 20);
            cout << "ERROR: NO EXISTE CLIENTE CON ESE ID";

            rlutil::setColor(rlutil::MAGENTA);
            rlutil::locate(46, 8);
            cout << "          ";
        }
    }
    limpiar_linea(44, 22);
    Vendedor vendedor;

    while(!valido)
    {
        rlutil::locate(51, 10); /// LEGAJO VENDEDOR
        legajoVendedor = cargarInt(9);

        if(contexto.gestorV.leerPorID(legajoVendedor, vendedor) && vendedor.getEstado())
        {
            break;
        }

        else
        {
            rlutil::setColor(rlutil::RED);
            rlutil::locate(32, 20);
            cout << "ERROR: NO EXISTE VENDEDOR CON ESE LEGAJO O ESTA INACTIVO";

            rlutil::setColor(rlutil::MAGENTA);
            rlutil::locate(51, 10);
            cout << "          ";
        }
    }
    limpiar_linea(44, 22);


    char est[3];
    while(!valido)
    {
        rlutil::setColor(rlutil::MAGENTA);
        rlutil::locate(42, 12); /// PAGADO (si) O ADEUDADO (no).
        cargarCadena(est, 3);
        toUpperCase(est);
        if(strcmp(est, "SI") != 0 && strcmp(est, "NO") != 0)
        {
            rlutil::setColor(rlutil::RED);
            rlutil::locate(47, 20);
            cout << "ERROR: DEBE INGRESAR SI O NO";

            rlutil::locate(42, 12);
            cout << "  ";
        }

        else valido = true;

        if(strcmp(est, "SI") == 0) estado = true;
        else estado = false;
    }
    limpiar_linea(44, 20);



    rlutil::locate(41, 14); /// DIA
    fechaIngreso.setDia();

    while (fechaIngreso.getDia() < 1 || fechaIngreso.getDia() > 31)
    {
        rlutil::setColor(rlutil::RED);
        rlutil::locate(45, 20);
        cout << "ERROR: ESCRIBA DIA ENTRE 01 A 31";

        rlutil::locate(41, 14);
        rlutil::setColor(rlutil::GREY);
        cout << "__";
        rlutil::locate(41, 14);
        rlutil::setColor(rlutil::MAGENTA);
        fechaIngreso.setDia();
    }
    limpiar_linea(43, 20);



    rlutil::locate(44, 14); /// MES
    fechaIngreso.setMes();
    while (fechaIngreso.getMes() < 1 || fechaIngreso.getMes() > 12)
    {
        rlutil::setColor(rlutil::RED);
        rlutil::locate(45, 20);
        cout << "ERROR: ESCRIBA MES ENTRE 01 A 12";

        rlutil::locate(44, 14);
        rlutil::setColor(rlutil::GREY);
        cout << "__";
        rlutil::locate(44, 14);
        rlutil::setColor(rlutil::MAGENTA);
        fechaIngreso.setMes();
    }
    limpiar_linea(43, 20);



    rlutil::locate(47, 14); /// ANIO
    fechaIngreso.setAnio();
    while (fechaIngreso.getAnio() < 1)
    {
        rlutil::setColor(rlutil::RED);
        rlutil::locate(45, 20);
        cout << "ERROR: ESCRIBA UN ANIO MAYOR A 0";

        rlutil::locate(47, 14);
        rlutil::setColor(rlutil::GREY);
        cout << "____";
        rlutil::locate(47, 14);
        rlutil::setColor(rlutil::MAGENTA);
        fechaIngreso.setAnio();
    }
    limpiar_linea(43, 20);

///-------------------------------------------------------------------------
    system("cls");

    rlutil::hidecursor();

    vector<Producto> productos;
    contexto.gestorP.leerTodosActivos(productos);

    GestorVenta gestorVenta;
    gestorVenta.iniciarNuevaVenta(idCliente, legajoVendedor);
    int idProducto = -1;
    int terminacion = 0;

    Producto producto;
    while(idProducto != 0 || gestorVenta.cantidadPedida() != 0 || gestorVenta.cantidadPedida() > 10)
    {
        system("cls");
        rlutil::hidecursor();
        producto.mostrar();
        //gestorVenta.mostrarProductosDisponibles(); SOLUCIONAR INTERFAZ

        cin.ignore();
        system("cls");

        rlutil::setColor(rlutil::WHITE);
        rlutil::showcursor();
        mostrar_carrito((int)gestorVenta.getCarrito().size(), 5, &terminacion, gestorVenta.getTotalCarrito());

        int y = 10;
        for(const auto& item : gestorVenta.getCarrito())
        {
            rlutil::setColor(rlutil::MAGENTA);
            rlutil::locate(13, y);
            cout << (char)ASCII_BARRA_VERTICAL << " ";
            rlutil::setColor(rlutil::GREY);
            cout << item.getIdProducto();

            rlutil::setColor(rlutil::MAGENTA);
            rlutil::locate(27, y);
            cout << (char)ASCII_BARRA_VERTICAL << " ";
            rlutil::setColor(rlutil::GREY);
            cout << producto.getNombreProductoPorID(item.getIdProducto());

            rlutil::setColor(rlutil::MAGENTA);
            rlutil::locate(59, y);
            cout << (char)ASCII_BARRA_VERTICAL << " ";
            rlutil::setColor(rlutil::GREY);
            cout << item.getCantidad();

            rlutil::setColor(rlutil::MAGENTA);
            rlutil::locate(71, y);
            cout << (char)ASCII_BARRA_VERTICAL << " ";
            rlutil::setColor(rlutil::GREY);
            cout << item.getPrecioVenta();

            rlutil::setColor(rlutil::MAGENTA);
            rlutil::locate(89, y);
            cout << (char)ASCII_BARRA_VERTICAL << " ";

            rlutil::setColor(rlutil::GREY);
            cout << item.getSubtotal();
            y++;
        }

        terminacion+=5 + 5 + 6;
        int posY_hint = terminacion + 4;
        rlutil::setColor(rlutil::GREY);
        rlutil::locate(39, posY_hint);
        cout << "(Ingrese ID Producto = 0, o Cantidad = 0 para cerrar el carrito)";
        rlutil::setColor(rlutil::MAGENTA);

        int cantidadActual = gestorVenta.cantidadPedida();
        caja_producto_cantidad(&idProducto, &cantidadActual, &terminacion);

        if(idProducto == 0 || cantidadActual == 0){
           limpiar_linea(39, posY_hint);
           cout << "                                   ";
           if (gestorVenta.cantidadPedida() == 0)
                {
                    rlutil::setColor(rlutil::RED);
                    rlutil::locate(39, posY_hint);
                    cout << "ERROR: No hay productos. Agregue al menos uno para finalizar.";
                    rlutil::hidecursor();
                    cin.ignore();

                    idProducto = -1; // Resetea para que el while(true) no termine
                    continue; // Vuelve al inicio del bucle de agregar productos
                }
            break;
        }

        else if(idProducto == 0 && cantidadActual == 0)
        {
            rlutil::setColor(rlutil::RED);
            rlutil::locate(39, terminacion + 4);
            cout << "ERROR: NO SE HA INGRESADO NINGUN PRODUCTO";
            rlutil::hidecursor();
            cin.ignore();
            idProducto = -1;
            continue;
        }

        Producto prod;
        bool encontrado = false;
        int stockDisponible = 0;

        for(const auto& p : productos)
        {
            if(p.getID() == idProducto && p.getEstado())
            {
                prod = p;
                encontrado = true;
                stockDisponible = gestorVenta.stockDisponible(idProducto);
                break;
            }
        }

        if(!encontrado)
        {
            rlutil::setColor(rlutil::RED);
            rlutil::locate(39, terminacion + 4);
            cout << "ERROR: PRODUCTO NO EXISTE O ESTA INACTIVO";
            rlutil::hidecursor();
            cin.ignore();
            continue;
        }

        if(gestorVenta.cantidadPedida() > stockDisponible)
        {
            rlutil::setColor(rlutil::RED);
            rlutil::locate(39, terminacion + 4);
            cout << "ERROR: STOCK INSUFICIENTE. DISPONIBLE: " << stockDisponible;
            rlutil::hidecursor();
            cin.ignore();
            continue;
        }

        if (gestorVenta.agregarProducto(idProducto, cantidadActual))
        {
            rlutil::locate(45, terminacion + 4);
            cout << "ARTICULO AGREGADO EXITOSAMENTE";
        }
        else
        {
            rlutil::setColor(rlutil::RED);
            rlutil::locate(39, terminacion + 4);
            cout << "ERROR: NO SE PUDO AGREGAR EL ARTICULO";
        }
        rlutil::hidecursor();
        cin.ignore();
    }

    int posY_decision = terminacion + 4;

    rlutil::setColor(rlutil::WHITE);
    rlutil::locate(39, posY_decision);
    cout << "CARRITO CERRADO.";
    rlutil::locate(39, posY_decision + 1);
    cout << "1. FINALIZAR VENTA";
    rlutil::locate(39, posY_decision + 2);
    cout << "2. CANCELAR VENTA (cualquier otra tecla)";
    rlutil::locate(39, posY_decision + 3);
    cout << "Opcion: ";

    rlutil::showcursor();
    int opcionFinal = cargarInt(1);
    rlutil::hidecursor();

    if (opcionFinal == 1)
    {
        this->total = gestorVenta.getTotalCarrito();
        gestorVenta.finalizarVenta();
        rlutil::setColor(rlutil::WHITE);
        rlutil::locate(45, posY_decision + 5);
        cout << "VENTA REGISTRADA EXITOSAMENTE";
    }
    else
    {
        gestorVenta.cancelarVenta();
        rlutil::setColor(rlutil::RED);
        rlutil::locate(45, posY_decision + 5);
        cout << "VENTA CANCELADA. No se guardo ningun registro.";
        this->estado = false;
    }

    rlutil::hidecursor();
    rlutil::locate(45, posY_decision + 7);
    cin.ignore();
}


void Venta::mostrar() const
{
    string datos_titulo[VENTA_OPCIONES] =
    {
        "   ID VENTA    ",
        "   ID CLIENTE    ",
        "   LEGAJO VENDEDOR    ",
        "       TOTAL        ",
        "   FECHA    ",
        "  ESTADO  "
    };

    size_t datos_espacios[VENTA_OPCIONES] = {15, 17, 22, 20, 12, 10};

    rlutil::locate(50, 1);
    rlutil::setColor(rlutil::MAGENTA);
    std::cout << "CANTIDAD DE VENTAS: " << archivo.cantidadRegistros();

    mostrarRegistros(archivo, datos_titulo, datos_espacios, VENTA_CURSOR_START_X, VENTA_CURSOR_START_Y, VENTA_PAGINADO, VENTA_OPCIONES, 1);
}


void Venta::mostrarFila(int posX, int posY) const
{
    rlutil::locate(posX, posY);
    cout << char(186) << "               " /// ID VENTA
         << char(186) << "                 " /// ID CLIENTE
         << char(186) << "                      " /// LEGAJO VENDEDOR
         << char(186) << "                    " /// TOTAL
         << char(186) << "            " /// FECHA
         << char(186) << "          " /// ESTADO
         << char(186);

    rlutil::locate(posX, posY);
    cout << char(186);
    rlutil::setColor(rlutil::WHITE);
    rlutil::locate(11, posY);
    cout << idVenta;
    rlutil::locate(27, posY);
    cout << idCliente;
    rlutil::locate(45, posY);
    cout << legajoVendedor;
    rlutil::locate(68, posY);
    cout << fixed << setprecision(2) << total;
    rlutil::locate(89, posY);
    getFecha().MostrarF(); // << "/" << fechaVenta.getMes() << "/" << fechaVenta.getAnio();
    rlutil::locate(102, posY);
    cout << (getEstado() ? "PAGADO" : "ADEUDADO");

    rlutil::setColor(rlutil::MAGENTA);
}


// --- Setters ---

void Venta::setIdVenta(int _idVenta)
{
    idVenta = _idVenta;
}
void Venta::setIdCliente(int _idCliente)
{
    idCliente = _idCliente;
}
void Venta::setLegajoVendedor(int _legajoVendedor)
{
    legajoVendedor = _legajoVendedor;
}
void Venta::setTotal(double _total)
{
    total = _total;
}
void Venta::setFechaVenta(Fecha _fechaVenta)
{
    fechaVenta = _fechaVenta;
    // Sincroniza también la fecha de la Entidad base
    setFecha(_fechaVenta.getDia(), _fechaVenta.getMes(), _fechaVenta.getAnio());
}

// --- Getters ---

int Venta::getIdVenta() const
{
    return idVenta;
}
int Venta::getIdCliente() const
{
    return idCliente;
}
int Venta::getLegajoVendedor() const
{
    return legajoVendedor;
}
double Venta::getTotal() const
{
    return total;
}
