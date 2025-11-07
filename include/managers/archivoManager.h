#ifndef ARCHIVOMANAGER_H
#define ARCHIVOMANAGER_H

#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>

template <typename T>
class ArchivoManager{
private:
    char nombreArchivo[100];

    /** @brief Abre un archivo con el modo especificado y maneja errores 
     * @param modo Modo de apertura del archivo (por ejemplo, "rb", "wb", "ab", etc.)
     * @return Puntero al archivo abierto, o nullptr si hubo un error
    */
    FILE *abrirArchivo(const char* modo) {
        FILE* archivo = fopen(nombreArchivo, modo);
        if (!archivo) {
            std::cerr << "Error al abrir '" << nombreArchivo 
                      << "': " << strerror(errno) << std::endl;
        }
        return archivo;
    }
    /** @brief Cierra un archivo y maneja errores
     * @param archivo Puntero al archivo a cerrar
    */
    void cerrarArchivo(FILE* archivo) {
        if (fclose(archivo) != 0) {
            std::cerr << "Advertencia: error al cerrar archivo" << std::endl;
        }
    }

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
        if (!objeto) {
            std::cerr << "Error: puntero nulo recibido en escribir()" << std::endl;
            return false;
        }
        FILE* archivo = abrirArchivo("ab");

        size_t element = fwrite(objeto, sizeof(T), 1, archivo);
        
        //vean este link para mas info sobre ferror
        //https://www.geeksforgeeks.org/c/ferror-in-c/

        if (ferror(archivo)) {
            std::cerr << "Error de I/O al escribir en '" << nombreArchivo << "'" << std::endl;
            cerrarArchivo(archivo);
            return false;
        }
        
        cerrarArchivo(archivo);
        return element == 1;
    }

    /**
     * @brief Obtiene todos los registros activos del archivo
     * 
     * @param objetos Vector donde se almacenarán los objetos activos leídos
     * @return true Si la lectura fue exitosa
     * @return false Si hubo un error al abrir el archivo
     */
    bool leer(std::vector<T>& objetos) {
        FILE* archivo = abrirArchivo("rb");
        if(cantidadRegistros() > 0) {
            objetos.reserve(static_cast<typename std::vector<T>::size_type>(std::max(0, cantidadRegistros())));
        }
        T objeto;
        while (fread(&objeto, sizeof(T), 1, archivo) == 1) {
            objetos.push_back(objeto);
        }

        cerrarArchivo(archivo);
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
        if (id < 0){
            std::cerr << "Error: ID inválido proporcionado para eliminarPorID()" << std::endl;
            return false;
        }
        FILE* archivo = abrirArchivo("rb+");

        T objeto;
        bool encontrado = false;

        while (fread(&objeto, sizeof(T), 1, archivo) == 1){
            if (objeto.getID() == id){
                objeto.setEstado(false);
                fseek(archivo, -static_cast<long>(sizeof(T)), SEEK_CUR);
                fwrite(&objeto, sizeof(T), 1, archivo);
                encontrado = true;
                break;
            }
        }

        cerrarArchivo(archivo);

        if (!encontrado) return false;

        return true;
    }

    /// ----------------------------METODO CANTIDAD DE REGISTROS---------------------------------
    /**
     * @brief Obtiene la cantidad total de registros en el archivo
     *
     * @return int Número total de registros en el archivo
     */
    int cantidadRegistros(){
        FILE* archivo = abrirArchivo("rb");

        fseek(archivo, 0, SEEK_END);
        long bytes = ftell(archivo);
        if (bytes == -1) {
            std::cerr << "Error: no se pudo obtener la posición del archivo " << nombreArchivo << std::endl;
            return 0;
        }
        cerrarArchivo(archivo);

        if (sizeof(T) == 0) {
            std::cerr << "Error: tamaño de T es 0" << std::endl;
            return 0;
        }
        return static_cast<int>(bytes / static_cast<long>(sizeof(T)));
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
        FILE* archivo = abrirArchivo("rb");

        int contadorActivos = 0;
        if (sizeof(T) == 0){
            cerrarArchivo(archivo);
            return 0;
        }

        T objeto;

        //Recibo el estado del objeto, y segun eso muestro la cantidad de registros activos, porq me mostraba que tenia 3 cuando solo habia 2 visibles
        while (fread(&objeto, sizeof(T), 1, archivo) == 1){
            if (objeto.getEstado()){contadorActivos++;}
        }

        cerrarArchivo(archivo);

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
        FILE* archivo = abrirArchivo("rb");

        while (fread(&objeto, sizeof(T), 1, archivo) == 1){
            if (objeto.getID() == id)
            {
                cerrarArchivo(archivo);
                return true;
            }
        }

        std::cerr << "Error: registro con ID " << id << " no encontrado." << std::endl;
        cerrarArchivo(archivo);
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
        FILE* archivo = abrirArchivo("rb+");

        T temp;
        bool encontrado = false;
        while (fread(&temp, sizeof(T), 1, archivo) == 1){
            if (temp.getID() == id){
                //SEEK_CUR: Desplazamiento desde la posición actual del puntero.
                fseek(archivo, -static_cast<long>(sizeof(T)), SEEK_CUR);  // mueve el puntero al inicio del registro encontrado
                fwrite(&objeto, sizeof(T), 1, archivo); // escribe el nuevo objeto
                encontrado = true;
                break;
            }
        }
        cerrarArchivo(archivo);
        if (!encontrado){
            std::cerr << "Error: registro con ID " << id << " no encontrado." << std::endl;
            return false;
        }return true;
    }

    /**
     * @brief Lee todos los registros del archivo y los almacena en un vector
     *
     * @param objetos Referencia al vector donde se almacenarán los registros activos
     * @return true Si la lectura fue exitosa
     * @return false Si hubo un error al abrir el archivo
     *
     * Este método lee todos los registros del archivo y almacena aquellos que están activos
     * (getEstado() retorna verdadero) en el vector proporcionado.
     */
    bool leerTodos(std::vector<T>& objetos){
        FILE* archivo = abrirArchivo("rb");
        if (cantidadRegistrosActivos() > 0) {
            objetos.reserve(static_cast<size_t>(cantidadRegistrosActivos()));
        }

        T objeto;
        while (fread(&objeto, sizeof(T), 1, archivo) == 1){
            objetos.push_back(objeto);
        }

        cerrarArchivo(archivo);
        return true;
    }

    /**
     * @brief Lee todos los registros activos del archivo y los almacena en un vector
     * 
     * @param objetos Referencia al vector donde se almacenarán los registros activos
     * @return true Si la lectura fue exitosa
     * @return false Si hubo un error al abrir el archivo
     * 
     * Este método lee todos los registros del archivo y almacena únicamente aquellos que están activos
     * (getEstado() retorna verdadero) en el vector proporcionado.
     */
    bool leerTodosActivos(std::vector<T>& objetos){
    FILE* archivo = abrirArchivo("rb");

    if (cantidadRegistrosActivos() > 0) {
        objetos.reserve(static_cast<size_t>(cantidadRegistrosActivos()));
    }

    T objeto;
    while (fread(&objeto, sizeof(T), 1, archivo) == 1){
        if(objeto.getEstado()) {
            objetos.push_back(objeto);
        }
    }

    cerrarArchivo(archivo);
    return true;
    }
};

#endif // ARCHIVOMANAGER_H
