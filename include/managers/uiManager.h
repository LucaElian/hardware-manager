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
    } else {
        std::cout << "Registro con ID " << id << " no encontrado." << std::endl;
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
    int idModificar;
    //aca deberia mostrar los registros disponibles a modificar
    //mostrarRegistros(gestor);
    std::cout << "Ingrese el ID del registro a modificar: ";
    std::cin >> idModificar;

    T registro;
    if (gestor.leerPorID(idModificar, registro)) {
        std::cout << "Registro encontrado:" << std::endl;
        registro.modificar();

        gestor.modificarPorId(idModificar, registro);

        std::cout << "Registro modificado exitosamente." << std::endl;
    } else {
        std::cout << "Registro con ID " << idModificar << " no encontrado." << std::endl;
    }
}

#endif // UIMANAGER_H
