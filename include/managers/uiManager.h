#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <iostream>
#include <vector>

#include "archivoManager.h"
#include "artworks.h"

#include <string>
#include <limits>

#define byte windows_byte
#include "rlutil.h"
#undef byte
#include "utilidades.h"

/**
 * @brief Muestra todos los registros de una entidad
 *
 * @tparam T Tipo de entidad a mostrar (Producto, Cliente, Vendedor, etc)
 * @param gestor Referencia al gestor de archivos de la entidad
 *
 * Esta función template obtiene todos los registros activos y los muestra
 * usando el método mostrar() de cada entidad
 */


template<typename T>
void mostrarRegistros(ArchivoManager<T>& gestor,
                    std::string titulos[] = nullptr,
                    size_t espacios[] = nullptr,
                    int xInicio = 3,
                    int yInicio = 4,
                    int paginado = 15,
                    size_t opciones = 0,
                    bool modo = 1) { /// 1 - agregar (todos)  2 - eliminar (estado activo)
    std::vector<T> registros;
    if(modo == 1) {
        if (!gestor.leerTodos(registros)) {
            std::cout << "ERROR AL LEER EL ARCHIVO";
            return;
        }
    }

    else {
        if (!gestor.leerTodosActivos(registros)) {
            std::cout << "ERROR AL LEER EL ARCHIVO";
            return;
        }
    }

    mostrar_encabezado(titulos, xInicio, yInicio, opciones, espacios);

    int cont_lineas = 0;

    for (const auto& registro : registros) {
        registro.mostrarFila(xInicio, yInicio + 3 + cont_lineas);
        cont_lineas++;

        if(cont_lineas % paginado == 0 && static_cast<size_t>(cont_lineas) < registros.size()) {
            barra_final(opciones, xInicio, yInicio + 3 + cont_lineas, espacios);
            rlutil::locate(102, yInicio + 3 + cont_lineas + 1);
            std::cout << "SIGUIENTE PAGINA";

            std::cin.ignore();
            system("cls");

            mostrar_encabezado(titulos, xInicio, yInicio, opciones, espacios);
            cont_lineas = 0;
        }
    }

    barra_final(opciones, xInicio, yInicio + 3 + cont_lineas, espacios);

    rlutil::locate(101, yInicio + 3 + cont_lineas + 1);
    std::cout << "FIN DE PAGINACION";
}

/** @brief Muestra un registro específico de una entidad
 *
 * @tparam T Tipo de entidad (Producto, Cliente, Vendedor, etc)
 * @param gestor Referencia al gestor de archivos de la entidad
 * @param id ID del registro a mostrar
 *
 * Esta función template busca un registro por su ID y lo muestra
 * usando el método mostrar() de la entidad. Si no se encuentra,
 * muestra un mensaje indicando que no fue encontrado.
 */

template<typename T>
void mostrarRegistro(ArchivoManager<T>& gestor, int id) {
    T registro;
    if (gestor.leerPorID(id, registro)) {
        registro.mostrar();
    }

}
/** @brief Modifica un registro existente de una entidad
 * @tparam T Tipo de entidad (Producto, Cliente, Vendedor, etc)
 * @param gestor Referencia al gestor de archivos de la entidad
 * Esta función template busca un registro por su ID, permite modificar sus datos
 * usando el método cargar() de la entidad, y guarda los cambios en el archivo.
 * Si no se encuentra el registro, muestra un mensaje indicando que no fue encontrado.
 *
 * (INFO DESACTUALIZADA PQ SE VA A MODIFICAR CON EL TIEMPO)
 */
template <typename T>
void modificarRegistro(ArchivoManager<T>& gestor){
    std::string titulos[] = {"ID", "DATOS"};
    size_t espacios[] = {10, 30};
    T registro;

    int idModificar;
    caja_eliminar(&idModificar, 52, 24);

    if (gestor.leerPorID(idModificar, registro)) {
        system("cls");
        registro.modificar();
        gestor.modificarPorId(idModificar, registro);
        rlutil::setColor(rlutil::WHITE);
    }

    else {
        rlutil::setColor(rlutil::RED);
        rlutil::locate(43, 24+3);
        cerr << "NO SE ENCONTRARON REGISTROS CON ID " << idModificar;
    }
}

/** @brief Muestra los placeholders actuales en la interfaz
 *  @param valores Array de strings con los valores actuales
 * @param cantidadValores Cantidad de valores en el array
 * @param xInicio Posición X inicial para mostrar los valores
 * @param yInicio Posición Y inicial para mostrar los valores
 * @param paso Espacio vertical entre cada valor (default 2)
 * Esta función muestra los valores actuales de los campos en gris
 * en las posiciones correspondientes de la interfaz.
 */
inline void mostrarPlaceholdersActuales(std::string valores[], int cantidadValores, int xInicio, int yInicio, int paso = 2) {
    // Offsets segun el orden: NOMBRE, TELEFONO, DNI, FECHA, TIPO, STOCK, PRECIO, ID
    // Para Producto: NOMBRE(9), TIPO(7), STOCK(8), PRECIO(9), FECHA(8), ID(5)
    int offsets[] = {9, 7, 8, 9, 8, 5}; // Orden de Producto

    // Si es Cliente/Vendedor (2-4 campos), se usa este orden:
    // NOMBRE(9), TELEFONO(11), DNI(6), FECHA(8)
    if (cantidadValores <= 4) {
        int offsetsClienteVendedor[] = {9, 11, 6, 8};
        rlutil::setColor(rlutil::GREY);
        for(int i = 0; i < cantidadValores; i++) {
            int offset = offsetsClienteVendedor[i];
            int cursorX = xInicio + offset + 1;
            int cursorY = yInicio + (i * paso);

            rlutil::locate(cursorX, cursorY);
            std::cout << valores[i];
        }
    } else {
        // Para Producto (6 campos)
        rlutil::setColor(rlutil::GREY);
        for(int i = 0; i < cantidadValores; i++) {
            int offset = offsets[i];
            int cursorX = xInicio + offset + 1;
            int cursorY = yInicio + (i * paso);

            rlutil::locate(cursorX, cursorY);
            std::cout << valores[i];
        }
    }
    rlutil::setColor(rlutil::MAGENTA);
}

#endif // UIMANAGER_H
