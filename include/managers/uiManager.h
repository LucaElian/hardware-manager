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

#endif // UIMANAGER_H