#ifndef GESTORVENTA_H
#define GESTORVENTA_H

#include <ctime>
#include <iostream>
#include <vector>

#include "archivoManager.h"
#include "clsVenta.h"
#include "clsDetalleVenta.h"
#include "clsProducto.h"
#include "clsCliente.h"
#include "clsVendedor.h"
#include "utilidades.h"
#include "uiManager.h"
#include "artworks.h"
#include "constantes.h"

// Despues lo documento como archivoManager
// Lean esto para entender vector: https://cplusplus.com/reference/vector/vector/

class GestorVenta {
private:
    ArchivoManager<Venta> _gestorVenta;
    ArchivoManager<DetalleVenta> _gestorDetalle;
    ArchivoManager<Producto> _gestorProducto;
    ArchivoManager<Cliente> _gestorCliente;
    ArchivoManager<Vendedor> _gestorVendedor;

    // el carrito temporal robado de un carrefour
    std::vector<DetalleVenta> _carrito;
    int _idCliente;
    int _legajoVendedor;

public:
    GestorVenta() :
        _gestorVenta(ARCHIVO_VENTAS),
        _gestorDetalle(ARCHIVO_DETALLE_VENTAS),
        _gestorProducto(ARCHIVO_PRODUCTOS),
        _gestorCliente(ARCHIVO_CLIENTES),
        _gestorVendedor(ARCHIVO_VENDEDORES),
        _idCliente(0),
        _legajoVendedor(0) {}

    /**
     * @brief Constructor que inicializa los gestores de archivos
     *
     * Inicializa los manejadores de archivos para ventas, detalles,
     * productos, clientes y vendedores.
     */
    bool iniciarNuevaVenta(int idCliente, int legajoVendedor) {

        //si no se encuentran el cliente o vendedor retornaria false
        if (!validarCliente(idCliente) || !validarVendedor(legajoVendedor)) {
            std::cout << "Error: Vendedor/Cliente no valido" << std::endl;
            return false;
        }
        _carrito.clear();
        _idCliente = idCliente;
        _legajoVendedor = legajoVendedor;
        return true;
    }

    /**
     * @brief Agrega un producto al carrito de compras
     *
     * @param idProducto ID del producto a agregar
     * @param cantidad Cantidad del producto
     * @return true Si el producto se agregó correctamente
     * @return false Si no hay stock suficiente o el producto no existe
     */
    bool agregarProducto(int idProducto, int cantidad) {
        if (cantidad <= 0) return false; // validacion simple

        if (!validarStock(idProducto, cantidad)) {
            return false;
        }
        double precio = obtenerPrecioProducto(idProducto);
        if (precio <= 0) return false;

        DetalleVenta detalle;
        detalle.setIdProducto(idProducto);
        detalle.setCantidad(cantidad);
        detalle.setPrecioVenta(precio);
        detalle.setSubtotal(precio * cantidad);

        _carrito.push_back(detalle);
        return true;
    }

    /**
     * @brief Muestra el contenido actual del carrito
     *
     * Imprime una lista de los productos en el carrito con sus
     * cantidades, precios y el total de la compra.
     */
    void mostrarCarrito() {
        double total = 0;
        std::cout << "\n=== Carrito Actual ===\n";
        for (const auto& detalle : _carrito) {
            std::cout << "Producto ID: " << detalle.getIdProducto()
                      << " - Cantidad: " << detalle.getCantidad()
                      << " - Subtotal: $" << detalle.getSubtotal() << std::endl;
            total += detalle.getSubtotal();
        }
        std::cout << "Total: $" << total << "\n";
    }

    void mostrarProductosDisponibles() {
        std::vector<Producto> productos;
        _gestorProducto.leerTodosActivos(productos);
        
        rlutil::locate(5, 5);
        rlutil::setColor(rlutil::CYAN);
        std::cout << "=== PRODUCTOS DISPONIBLES (Stock Actualizado) ===";
        
        int linea = 5;
        for (const auto& producto : productos) {
            int stockDisponible = this->stockDisponible(producto.getID());
            
            rlutil::locate(5, linea);
            rlutil::setColor(rlutil::WHITE);
            std::cout << "ID: " << producto.getID() 
                      << " | NOMBRE: " << producto.getNombre()
                      << " | STOCK DISPONIBLE: " << stockDisponible 
                      << " | PRECIO: $" << std::fixed << std::setprecision(2) << producto.getPrecio();
            linea++;
            
            if(linea > 35) break;
        }
    }

    /**
     * @brief Finaliza la venta actual
     *
     * Registra la venta en el archivo, actualiza el stock de productos
     * y limpia el carrito.
     *
     * @return true Si la venta se completó exitosamente
     * @return false Si hubo error o el carrito está vacío
     */
    bool finalizarVenta() {
        if (_carrito.empty()) return false;

        //crea la venta
        Venta* nuevaVenta = new Venta();
        int idVenta = generarIdVenta();
        nuevaVenta->setID(idVenta);
        nuevaVenta->setIdVenta(idVenta);
        nuevaVenta->setIdCliente(_idCliente);
        nuevaVenta->setLegajoVendedor(_legajoVendedor);

        /*
        tm_mday contiene el día del mes (1-31)
        tm_mon contiene el mes (0-11, por eso se suma 1)
        tm_year contiene los años desde 1900, por eso se suma 1900
        */

        time_t now = time(0);
        tm* ltm = localtime(&now);

        nuevaVenta->setFechaVenta(Fecha(ltm->tm_mday, ltm->tm_mon + 1, 1900 + ltm->tm_year));

        //calcula el total
        double total = 0;
        int detalleID_counter = _gestorDetalle.cantidadRegistros();
        for (auto& detalle : _carrito) {
            detalle.setIdVenta(idVenta);
            total += detalle.getSubtotal();

            actualizarStock(detalle.getIdProducto(), detalle.getCantidad());

            detalle.setID(++detalleID_counter);

            DetalleVenta* pDetalle = new DetalleVenta(detalle);
            //pDetalle.setID(_gestorDetalle.cantidadRegistros());
            //registra detalle

            if (!_gestorDetalle.escribir(pDetalle)) {
                delete nuevaVenta;
                delete pDetalle;
                return false;
            }
            delete pDetalle;
        }

        nuevaVenta->setTotal(total);

        // Registrar venta
        bool exito = _gestorVenta.escribir(nuevaVenta);
        delete nuevaVenta;

        if (exito) {
            _carrito.clear();
            _idCliente = 0;
            _legajoVendedor = 0;
        }

        return exito;
    }

    /**
     * @brief Cancela la venta actual
     *
     * Limpia el carrito y reinicia los datos del cliente y vendedor
     */
    void cancelarVenta() {
        _carrito.clear();
        _idCliente = 0;
        _legajoVendedor = 0;
    }

    /**
     * @brief Lista las ventas del archivo
     *
     * Lee y muestra las ventas registradas en el archivo.
    */
   void listarVentas() {
    const size_t OPCIONES = 6; // <-- 1. Cambiado de 7 a 6
    std::string titulos[OPCIONES] = {
        // "    ID    ", // <-- 2. Columna ID eliminada
        " ID VENTA ", " ID CLIENTE ", "L.VENDEDOR", "     TOTAL     ", "    FECHA   ", "  ESTADO  "
    };

    size_t espacios[OPCIONES] = {
        // 10, // <-- 3. Ancho de ID eliminado
        10, 12, 10, 15, 12, 10
    };

    // 4. Centramos la tabla (igual que el reporte)
    mostrarRegistros(_gestorVenta, titulos, espacios, 15, 4, 15, OPCIONES, 1);
    }

    /**
     * @brief Lista el detalle de las ventas
     *
     * @return Lee y muestra los detalles de las ventas registradas en el archivo.
     */

    void listarDetallesVentas() {
       const size_t OPCIONES = 7;
    std::string titulos[OPCIONES] = {
        "    ID    ", " ID VENTA ", " ID PROD  ", "  CANT  ", "     PRECIO    ", "    SUBTOTAL   ", "  ESTADO  "
    };

    size_t espacios[OPCIONES] = {
        10, 10, 10, 8, 15, 15, 10
    };
    mostrarRegistros(_gestorDetalle, titulos, espacios, 10, 4, 15, OPCIONES, 1);
    }

    bool leerTodos(std::vector<Venta>& ventas) {
        return _gestorVenta.leerTodos(ventas);
    }

    bool leerTodosDetalles(std::vector<DetalleVenta>& detalles) {
        return _gestorDetalle.leerTodos(detalles);
    }

    int cantidadRegistros() {
        return _gestorVenta.cantidadRegistros();
    }

    int cantidadRegistrosActivos() {
        return _gestorVenta.cantidadRegistrosActivos();
    }
    int cantidadPedida() {
        return static_cast<int>(_carrito.size());
    }
    int stockDisponible(int idProducto) {
        int stockTotal = 0;
        Producto producto;
        if (_gestorProducto.leerPorID(idProducto, producto)) {
            stockTotal = producto.getStock();
        }

        int reservado = 0;
        for (const auto& d : _carrito) {
            if (d.getIdProducto() == idProducto) reservado += d.getCantidad();
        }
        return stockTotal - reservado;
    }
    int getTotalCarrito() const {
        int total = 0;
        for (const auto& detalle : _carrito) {
            total += detalle.getSubtotal();
        }
        return total;
    }
    std::vector<DetalleVenta> getCarrito() const {
        return _carrito;
    }

private:
    /**
     * @brief Genera un nuevo ID para la venta
     * @return int Nuevo ID generado
     */
    int generarIdVenta() {
        return _gestorVenta.cantidadRegistros() + 1;
    }

    /**
     * @brief Valida si hay stock suficiente de un producto
     *
     * @param idProducto ID del producto a validar
     * @param cantidad Cantidad requerida
     * @return true Si hay stock suficiente
     * @return false Si no hay stock suficiente o el producto no existe
     */
    bool validarStock(int idProducto, int cantidad) {
        Producto producto;
        if (_gestorProducto.leerPorID(idProducto, producto)) {
            int reservado = 0;
            for (const auto& d : _carrito) {
                if (d.getIdProducto() == idProducto) reservado += d.getCantidad();
            }
            return (producto.getStock() - reservado) >= cantidad;
        }
        return false;
    }

    /**
     * @brief Valida si existe un cliente
     *
     * @param idCliente ID del cliente a validar
     * @return true Si el cliente existe
     * @return false Si el cliente no existe
     */
    bool validarCliente(int idCliente) {
        Cliente cliente;
        return _gestorCliente.leerPorID(idCliente, cliente);
    }

    /**
     * @brief Valida si existe un vendedor
     *
     * @param legajoVendedor Legajo del vendedor a validar
     * @return true Si el vendedor existe
     * @return false Si el vendedor no existe
     */
    bool validarVendedor(int legajoVendedor) {
        Vendedor vendedor;
        return _gestorVendedor.leerPorID(legajoVendedor, vendedor);
    }

    /**
     * @brief Obtiene el precio de un producto
     *
     * @param idProducto ID del producto
     * @return double Precio del producto, 0 si no existe
     */
    double obtenerPrecioProducto(int idProducto) {
        Producto producto;
        if (_gestorProducto.leerPorID(idProducto, producto)) {
            return producto.getPrecio();
        }
        return 0;
    }

    /**
     * @brief Actualiza el stock de un producto
     *
     * @param idProducto ID del producto
     * @param cantidad Cantidad a restar del stock
     * @return true Si el stock se actualizó correctamente
     * @return false Si hubo error o el producto no existe
     */
    bool actualizarStock(int idProducto, int cantidad) {
        Producto producto;
        if (_gestorProducto.leerPorID(idProducto, producto)) {
            producto.setStock(producto.getStock() - cantidad);
            return _gestorProducto.modificarPorId(idProducto, producto);
        }
        return false;
    }

    int clienteMaxVentas() {
        std::vector<Venta> ventas;
        if (!_gestorVenta.leerTodos(ventas) || ventas.empty()) {
            return 0;
        }

        std::vector<Cliente> clientes;
        _gestorCliente.leerTodos(clientes);

        std::vector<int> contadorVentas(clientes.size() + 1, 0);

        for (const auto& venta : ventas) {
            contadorVentas[static_cast<size_t>(venta.getIdCliente())]++;
        }

        int clienteMax = 0;
        int maxVentas = 0;

        for (size_t i = 0; i < contadorVentas.size(); i++) {
            if (contadorVentas[i] > maxVentas) {
                maxVentas = contadorVentas[i];
                clienteMax = static_cast<int>(i);
            }
        }

        return clienteMax;
    }
};

#endif // GESTORVENTA_H
