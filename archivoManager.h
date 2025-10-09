#ifndef ARCHIVOMANAGER_H
#define ARCHIVOMANAGER_H

class ArchivoManager {
private:
    char nombreArchivo[256];
    char tipoObj; // 'P' para Producto, 'C' para Cliente
    size_t size;

public:
    ArchivoManager(const char* archivo, char tipoObj, size_t size);
    bool escribir(void* objeto);
    bool leer();
    bool eliminarPorID(int id);
    int cantidadRegistros();
};

#endif