#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <iostream>
#include <vector>
#include "archivoManager.h"

/**
 * @brief Muestra todos los registros activos de una entidad
 * 
 * @tparam T Tipo de entidad a mostrar (Producto, Cliente, Vendedor, etc)
 * @param gestor Referencia al gestor de archivos de la entidad
 * 
 * Esta función template obtiene todos los registros activos y los muestra
 * usando el método mostrar() de cada entidad
 */
template<typename T>
void mostrarRegistros(ArchivoManager<T>& gestor) {
    std::vector<T> registros;
    if (gestor.leerTodos(registros)) {
        if (registros.empty()) {
            std::cout << "No hay registros activos." << std::endl;
            return;
        }
        // Itera en cada registro usando una referencia constante para evitar copias
        for (const auto& registro : registros) {
            registro.mostrar();
        }
    }
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