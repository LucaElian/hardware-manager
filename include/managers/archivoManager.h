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
    ArchivoManager(const char* archivo)
    {
        strncpy(nombreArchivo, archivo, sizeof(nombreArchivo)-1);
        nombreArchivo[sizeof(nombreArchivo)-1] = '\0';
    }

    /// ----------------------------METODO ESCRIBIR---------------------------------
    bool escribir(T* objeto)
    {
        FILE* archivo = fopen(nombreArchivo, "ab");
        if (!archivo)
        {
            std::cerr << "Error: fallo al abrir el archivo" << std::endl;
            return false;
        }

        size_t element = fwrite(objeto, sizeof(T), 1, archivo);
        fclose(archivo);

        if (element != 1)
        {
            std::cerr << "Error: fallo al escribir el objeto" << std::endl;
            return false;
        }
        return true;
    }

    /// ----------------------------METODO LEER---------------------------------
    bool leer()
    {
        FILE* archivo = fopen(nombreArchivo, "rb");

        if (!archivo)
        {
            std::cerr << "ERROR: NO SE PUDO LEER EL ARCHIVO " << nombreArchivo << std::endl;
            return false;
        }

        std::cout << "CONTENIDO DE " << nombreArchivo << std::endl;

        T objeto;
        bool activos = false;

        while (fread(&objeto, sizeof(T), 1, archivo) == 1)
        {
            if (objeto.getEstado() == true)
            {
                objeto.mostrar();
                std::cout << "---------------------\n";
                activos = true;
            }
        }

        if (!activos)
        {
            std::cout << "NO SE ENCONTRARON REGISTROS ACTIVOS." << std::endl;
        }

        fclose(archivo);
        return true;
    }

    /// ----------------------------METODO ELIMINAR POR ID---------------------------------
    bool eliminarPorID(int id)
    {
        FILE* archivo = fopen(nombreArchivo, "r+b");
        if (!archivo)
        {
            std::cerr << "Error: no se pudo abrir el archivo " << nombreArchivo << std::endl;
            return false;
        }

        T objeto;
        while (fread(&objeto, sizeof(T), 1, archivo) == 1)
        {
            if (objeto.getID() == id)
            {
                // Mueve el puntero al inicio del registro leído
                long posActual = ftell(archivo);
                long posRegistro = posActual - sizeof(T);
                fseek(archivo, posRegistro, SEEK_SET);

                // Marca como eliminado
                objeto.setEstado(false);
                fwrite(&objeto, sizeof(T), 1, archivo);

                fclose(archivo);
                return true;
            }
        }

        // di no se encontro
        std::cerr << "Error: registro con ID " << id << " no encontrado." << std::endl;
        fclose(archivo);
        return false;
    }


    /// ----------------------------METODO CANTIDAD DE REGISTROS---------------------------------
    int cantidadRegistros()
    {
        FILE* archivo = fopen(nombreArchivo, "rb");

        if (!archivo) return 0;

        fseek(archivo, 0, SEEK_END);
        long bytes = ftell(archivo);
        fclose(archivo);

        if (sizeof(T) == 0) return 0;
        return bytes / sizeof(T);
    }

    /// ----------------------------METODO CANTIDAD DE REGISTROS ACTIVOS----------------------------
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
    bool leerPorID(int id, T& objeto)
    {
        FILE* archivo = fopen(nombreArchivo, "rb");
        if (!archivo)
        {
            std::cerr << "Error: no se pudo abrir el archivo " << nombreArchivo << std::endl;
            return false;
        }

        while (fread(&objeto, sizeof(T), 1, archivo) == 1)
        {
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
};

#endif // ARCHIVOMANAGER_H
