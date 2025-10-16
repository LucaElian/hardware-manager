#ifndef ARCHIVOMANAGER_H
#define ARCHIVOMANAGER_H

#include <cstdio>
#include <cstring>
#include <iostream>


template <typename T>
class ArchivoManager
{
private:
    char nombreArchivo[100];

public:
    ArchivoManager(const char* archivo){
        strncpy(nombreArchivo, archivo, sizeof(nombreArchivo)-1);
        nombreArchivo[sizeof(nombreArchivo)-1] = '\0';
    }

    /// ----------------------------METODO ESCRIBIR---------------------------------
    /**
     * @brief Escribe un objeto en un archivo binario
     * 
     * @tparam T El tipo de objeto a escribir
     * @param objeto Puntero al objeto que se escribirá en el archivo
     * @return true Si el objeto se escribió exitosamente
     * @return false Si hubo un error al abrir el archivo o escribir el objeto
     * 
     * Este método abre el archivo en modo binario de anexado y escribe el objeto.
     * El archivo se cierra automáticamente después de escribir, ya sea exitoso o no.
     */

    bool escribir(T* objeto){
        FILE* archivo = fopen(nombreArchivo, "ab");
        if (!archivo){
            std::cerr << "Error: fallo al abrir el archivo" << std::endl;
            return false;
        }

        size_t element = fwrite(objeto, sizeof(T), 1, archivo);
        fclose(archivo);

        if (element != 1){
            std::cerr << "Error: fallo al escribir el objeto" << std::endl;
            return false;
        }
        return true;
    }

    /// ----------------------------METODO LEER---------------------------------
    /**
     * @brief Lee y muestra los registros activos de un archivo binario
     * 
     * Este método abre un archivo binario especificado por nombreArchivo y lee objetos de tipo T.
     * Muestra solo los registros que tienen su estado configurado como verdadero.
     * Cada registro activo se muestra seguido de una línea separadora.
     * 
     * @return bool True si la lectura fue exitosa, False si hubo error al abrir el archivo
     */
    bool leer(){
        FILE* archivo = fopen(nombreArchivo, "rb");

        if (!archivo){
            std::cerr << "Error: no se pudo abrir el archivo " << nombreArchivo << std::endl;
            return false;
        }

        std::cout << "Contenido del archivo " << nombreArchivo << std::endl;

        T objeto;
        bool activos = false;

        while (fread(&objeto, sizeof(T), 1, archivo) == 1){
            if (objeto.getEstado() == true){
                objeto.mostrar();
                std::cout << "---------------------\n";
                activos = true;
            }
        }

        if (!activos){
            std::cout << "No se encontraron registros activos." << std::endl;
        }

        fclose(archivo);
        return true;
    }

    /// ----------------------------METODO ELIMINAR POR ID---------------------------------
    /**
     * @brief Elimina lógicamente un registro por su ID
     * 
     * @param id El ID del registro a eliminar
     * @return true Si el registro fue encontrado y marcado como eliminado
     * @return false Si hubo error o no se encontró el registro
     * 
     * Este método realiza un borrado lógico, marcando el estado del registro como falso.
     * El registro permanece en el archivo pero no será mostrado en las lecturas normales.
     */
    bool eliminarPorID(int id){
        FILE* archivo = fopen(nombreArchivo, "rb+");
        if (!archivo){
            std::cerr << "Error: no se pudo abrir el archivo " << nombreArchivo << std::endl;
            return false;
        }

        T objeto;
        bool encontrado = false;

        while (fread(&objeto, sizeof(T), 1, archivo) == 1){
            if (objeto.getID() == id){
                objeto.setEstado(false);
                fseek(archivo, -sizeof(T), SEEK_CUR);
                fwrite(&objeto, sizeof(T), 1, archivo);
                encontrado = true;
                break;
            }
        }

        fclose(archivo);
        
        if (!encontrado){
            std::cerr << "Error: no se encontró el registro con ID " << id << std::endl;
            return false;
        }
        
        return true;
    }

    /// ----------------------------METODO CANTIDAD DE REGISTROS---------------------------------
    /**
     * @brief Obtiene la cantidad total de registros en el archivo
     * 
     * @return int Número total de registros en el archivo
     */
    int cantidadRegistros(){
        FILE* archivo = fopen(nombreArchivo, "rb");

        if (!archivo) return 0;

        fseek(archivo, 0, SEEK_END);
        long bytes = ftell(archivo);
        fclose(archivo);

        if (sizeof(T) == 0) return 0;
        return bytes / sizeof(T);
    }

    /// ----------------------------METODO CANTIDAD DE REGISTROS ACTIVOS----------------------------
    /**
     * @brief Cuenta el número de registros activos en el archivo
     * 
     * Este método lee a través del archivo binario y cuenta los registros donde el
     * estado del objeto está activo/verdadero. Solo considera registros que tienen
     * getEstado() retornando verdadero.
     * 
     * @return int Número de registros activos encontrados en el archivo
     * @return 0 Si el archivo no puede abrirse o si sizeof(T) es 0
     * 
     * @throws Ninguno pero muestra mensaje de error en cerr si el archivo no puede abrirse
     */

    int cantidadRegistrosActivos(){
        FILE* archivo = fopen(nombreArchivo, "rb");
        if (!archivo){
            std::cerr << "Error: no se pudo abrir el archivo " << nombreArchivo << std::endl;
            return 0;
        }

        int contadorActivos = 0;
        if (sizeof(T) == 0){
            fclose(archivo);
            return 0;
        }

        T objeto;

        //Recibo el estado del objeto, y segun eso muestro la cantidad de registros activos, porq me mostraba que tenia 3 cuando solo habia 2 visibles
        while (fread(&objeto, sizeof(T), 1, archivo) == 1){
            if (objeto.getEstado()){contadorActivos++;}
        }

        fclose(archivo);

        return contadorActivos;
    }

    // Doc rapida: pasas la direccion de memoria de el objeto 't' y
    // si lo encuentra lo carga en 't' y devuelve true, sino false
    /// ----------------------------METODO LEER POR ID---------------------------------
    /**
     * @brief Lee un registro por su ID y lo carga en el objeto proporcionado
     * 
     * @param id El ID del registro a buscar
     * @param objeto Referencia al objeto donde se cargará el registro encontrado
     * @return true Si se encontró y cargó el registro exitosamente
     * @return false Si hubo error o no se encontró el registro
     * 
     * Este método busca un registro específico por su ID en el archivo.
     * Si lo encuentra, carga los datos en el objeto proporcionado por referencia.
     */
    bool leerPorID(int id, T& objeto){
        FILE* archivo = fopen(nombreArchivo, "rb");
        if (!archivo){
            std::cerr << "Error: no se pudo abrir el archivo " << nombreArchivo << std::endl;
            return false;
        }

        while (fread(&objeto, sizeof(T), 1, archivo) == 1){
            if (objeto.getID() == id)
            {
                fclose(archivo);
                return true;
            }
        }

        std::cerr << "Error: registro con ID " << id << " no encontrado." << std::endl;
        fclose(archivo);
        return false;
    }

    /**
     * @brief Modifica un objeto en el archivo por su ID
     * 
     * @param id El ID del objeto a modificar
     * @param objeto Referencia al objeto que contiene los nuevos datos
     * @return bool True si la modificación fue exitosa, false en caso contrario
     * 
     * @details Abre el archivo en modo binario de actualización (rb+) y busca un objeto
     * con el ID especificado. Si lo encuentra, actualiza los datos del objeto en el archivo
     * con los nuevos datos proporcionados. El archivo se cierra automáticamente después de la operación.
     * 
     * @throws Muestra mensaje de error en cerr si:
     *         - No se puede abrir el archivo
     *         - No se encuentra el objeto con el ID especificado
     */

    bool modificarPorId(int id, T& objeto){
        FILE* archivo = fopen(nombreArchivo, "rb+"); // abre en modo update
        if (!archivo){
            std::cerr << "Error: no se pudo abrir el archivo " << nombreArchivo << std::endl;
            return false;
        }
        T temp;
        bool encontrado = false;
        while (fread(&temp, sizeof(T), 1, archivo) == 1){
            if (temp.getID() == id){
                //SEEK_CUR: Desplazamiento desde la posición actual del puntero.
                fseek(archivo, -sizeof(T), SEEK_CUR); // mueve el puntero al inicio del registro encontrado
                fwrite(&objeto, sizeof(T), 1, archivo); // escribe el nuevo objeto
                encontrado = true;
                break;
            }
        }
        fclose(archivo);
        if (!encontrado){
            std::cerr << "Error: registro con ID " << id << " no encontrado." << std::endl;
            return false;
        }return true;
    }
};

#endif // ARCHIVOMANAGER_H
