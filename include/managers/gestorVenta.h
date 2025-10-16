#ifndef GESTORVENTA_H
#define GESTORVENTA_H

#include <iostream>
#include <vector>
#include "archivoManager.h"
#include "clsVenta.h"
#include "clsDetalleVenta.h"
#include "clsProducto.h"
#include "clsCliente.h"
#include "clsVendedor.h"

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
        _gestorVenta("ventas.dat"),
        _gestorDetalle("detalles_venta.dat"),
        _gestorProducto("productos.dat"),
        _gestorCliente("clientes.dat"),
        _gestorVendedor("vendedores.dat"),
        _idCliente(0),
        _legajoVendedor(0) {}

    // Metodos para manejar el carrito
    bool iniciarNuevaVenta(int idCliente, int legajoVendedor) {
        if (!validarCliente(idCliente) || !validarVendedor(legajoVendedor)) {
            return false;
        }
        _carrito.clear();
        _idCliente = idCliente;
        _legajoVendedor = legajoVendedor;
        return true;
    }

    bool agregarProducto(int idProducto, int cantidad) {
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

    bool finalizarVenta() {
        if (_carrito.empty()) return false;

        //crea la venta
        Venta* nuevaVenta = new Venta();
        int idVenta = generarIdVenta();
        nuevaVenta->setIdVenta(idVenta);
        nuevaVenta->setIdCliente(_idCliente);
        nuevaVenta->setLegajoVendedor(_legajoVendedor);
        nuevaVenta->setFechaVenta(Fecha());

        //calcula el total
        double total = 0;
        for (auto& detalle : _carrito) {
            detalle.setIdVenta(idVenta);
            total += detalle.getSubtotal();
            
            actualizarStock(detalle.getIdProducto(), detalle.getCantidad());
            
            DetalleVenta* pDetalle = new DetalleVenta(detalle);
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

    void cancelarVenta() {
        _carrito.clear();
        _idCliente = 0;
        _legajoVendedor = 0;
    }

private:
    int generarIdVenta() {
        return _gestorVenta.cantidadRegistros() + 1;
    }

    bool validarStock(int idProducto, int cantidad) {
        Producto producto;
        if (_gestorProducto.leerPorID(idProducto, producto)) {
            return producto.getStock() >= cantidad;
        }
        return false;
    }

    bool validarCliente(int idCliente) {
        Cliente cliente;
        return _gestorCliente.leerPorID(idCliente, cliente);
    }

    bool validarVendedor(int legajoVendedor) {
        Vendedor vendedor; 
        return _gestorVendedor.leerPorID(legajoVendedor, vendedor);
    }

    double obtenerPrecioProducto(int idProducto) {
        Producto producto;
        if (_gestorProducto.leerPorID(idProducto, producto)) {
            return producto.getPrecio();
        }
        return 0;
    }

    bool actualizarStock(int idProducto, int cantidad) {
        Producto producto;
        if (_gestorProducto.leerPorID(idProducto, producto)) {
            producto.setStock(producto.getStock() - cantidad);
            return _gestorProducto.modificarPorId(idProducto, producto);
        }
        return false;
    }
};

#endif // GESTORVENTA_H