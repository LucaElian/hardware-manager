#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <iostream>
#include <vector>

#include "archivoManager.h"
#include "artworks.h"

#define byte windows_byte
#include "rlutil.h"
#undef byte

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
                    int espacios[] = nullptr,
                    int xInicio = 3,
                    int yInicio = 4,
                    int paginado = 15,
                    int opciones = 0,
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

    mostrar_encabezado((std::string*)titulos, xInicio, yInicio, opciones, (int*)espacios);

    int cont_lineas = 0;

    for (const auto& registro : registros) {
        registro.mostrarFila(xInicio, yInicio + 3 + cont_lineas);
        cont_lineas++;

        if(cont_lineas % paginado == 0 && cont_lineas < registros.size()) {
            barra_final(opciones, yInicio + 3 + cont_lineas, espacios);
            rlutil::locate(102, yInicio + 3 + cont_lineas + 1);
            cout << "SIGUIENTE PAGINA";

            cin.ignore();
            system("cls");

            mostrar_encabezado((std::string*)titulos, xInicio, yInicio, opciones, (int*)espacios);
            cont_lineas = 0;
        }
    }

    barra_final(opciones, yInicio + 3 + cont_lineas, espacios);

    rlutil::locate(101, yInicio + 3 + cont_lineas + 1);
    cout << "FIN DE PAGINACION";
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
    } else {
        std::cout << "Registro con ID " << id << " no encontrado." << std::endl;
    }

}

#endif // UIMANAGER_H