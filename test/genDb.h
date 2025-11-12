#include <iostream>
#include "archivoManager.h"
#include "clsProducto.h"
#include "clsCliente.h"
#include "clsVendedor.h"
#include "clsVenta.h"
#include "clsDetalleVenta.h"
#include "clsFecha.h"

void generarProductos() {
    ArchivoManager<Producto> gestor("productos.dat");

    const char* nombres[] = {
        "MOUSE LOGITECH G502", "TECLADO MECANICO RGB", "MONITOR 27 PULGADAS",
        "AURICULARES GAMING", "WEBCAM FULL HD", "MICROFONO USB",
        "SSD 1TB NVME", "RAM DDR4 16GB", "GABINETE ATX",
        "PLACA DE VIDEO RTX", "PROCESADOR RYZEN 5", "MOTHERBOARD B550",
        "FUENTE 750W", "COOLER CPU RGB", "MOUSEPAD XXL"
    };

    char tipos[] = {'A', 'A', 'A', 'A', 'A', 'A', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'A'};
    int stocks[] = {15, 8, 12, 20, 10, 7, 25, 18, 9, 5, 14, 11, 16, 22, 30};
    double precios[] = {12500.50, 18900.00, 95000.00, 8500.00, 15000.00, 22000.00,
                        45000.00, 28000.00, 35000.00, 280000.00, 95000.00, 65000.00,
                        42000.00, 12000.00, 3500.00};

    for(int i = 0; i < 15; i++) {
        Producto p;
        p.setID(i + 1);
        p.setNombre(nombres[i]);
        p.setTipo(tipos[i]);
        p.setStock(stocks[i]);
        p.setPrecio(precios[i]);
        p.setEstado(true);
        p.setFecha(1, 1, 2023);
        gestor.escribir(&p);
    }

    std::cout << "15 productos generados" << std::endl;
}

void generarClientes() {
    ArchivoManager<Cliente> gestor("clientes.dat");

    const char* nombres[] = {
        "JUAN PEREZ", "MARIA GONZALEZ", "CARLOS RODRIGUEZ",
        "ANA MARTINEZ", "LUIS FERNANDEZ", "SOFIA LOPEZ",
        "DIEGO SANCHEZ", "LAURA RAMIREZ", "PABLO TORRES",
        "VALENTINA DIAZ", "MATEO ROMERO", "CAMILA SILVA"
    };

    const char* telefonos[] = {
        "1145678901", "1156789012", "1167890123",
        "1178901234", "1189012345", "1190123456",
        "1101234567", "1112345678", "1123456789",
        "1134567890", "1145678902", "1156789013"
    };

    for(int i = 0; i < 12; i++) {
        Cliente c(i + 1, nombres[i], telefonos[i]);
        gestor.escribir(&c);
    }

    std::cout << "12 clientes generados" << std::endl;
}

void generarVendedores() {
    ArchivoManager<Vendedor> gestor("vendedores.dat");

    const char* nombres[] = {
        "ROBERTO DIAZ", "FLORENCIA CASTRO", "MARTIN SILVA",
        "CAROLINA MORENO", "ALEJANDRO RUIZ", "VERONICA SOTO"
    };

    const char* telefonos[] = {
        "1198765432", "1187654321", "1176543210",
        "1165432109", "1154321098", "1143210987"
    };

    const char* dnis[] = {
        "35123456", "38234567", "40345678",
        "42456789", "39567890", "37678901"
    };

    for(int i = 0; i < 6; i++) {
        Vendedor v(
            i + 1,
            nombres[i],
            telefonos[i],
            dnis[i],
            true,
            Fecha(1, 1, 2023)
        );
        gestor.escribir(&v);
    }

    std::cout << "6 vendedores generados" << std::endl;
}

void generarVentas() {
    ArchivoManager<Venta> gestorVenta("ventas.dat");
    ArchivoManager<DetalleVenta> gestorDetalle("detalles_venta.dat");

    int detalleID = 1;

    // Generar 20 ventas aleatorias
    for(int i = 1; i <= 20; i++) {
        int idCliente = rand() % 12 + 1;
        int legajoVendedor = rand() % 6 + 1;
        int cantProductos = rand() % 4 + 1; // 1 a 4 productos por venta

        Venta venta(
            i,
            i,
            idCliente,
            legajoVendedor,
            0.0, // Se calculará después
            true,
            Fecha(rand() % 28 + 1, rand() % 4 + 9, 2024) // Sep-Dic 2024
        );

        double totalVenta = 0;

        // Generar detalles para esta venta
        for(int j = 0; j < cantProductos; j++) {
            int idProducto = rand() % 15 + 1;
            int cantidad = rand() % 3 + 1;
            double precio = 10000 + (rand() % 20000); // Precio random simplificado
            double subtotal = precio * cantidad;

            DetalleVenta detalle(
                detalleID++,
                i, // idVenta
                idProducto,
                cantidad,
                precio,
                subtotal,
                true
            );

            gestorDetalle.escribir(&detalle);
            totalVenta += subtotal;
        }

        venta.setTotal(totalVenta);
        gestorVenta.escribir(&venta);
    }

    std::cout << "20 ventas con sus detalles generados" << std::endl;
}
