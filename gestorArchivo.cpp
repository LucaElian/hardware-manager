// DEJEN DE COMENTARLO, SOLO COMENTEN LA LINEA 6 EN EL MAIN LA PUTA QUE LO PARIO
#include <iostream>
#include <cstdio>
#include <cstring> // strcpychaval
#include "clsProducto.h"

class SQCopy {
private:
    char nombreArchivo[256];

public:
    SQCopy(const char* archivo) {
        strncpy(nombreArchivo, archivo, sizeof(nombreArchivo)-1);
        nombreArchivo[sizeof(nombreArchivo)-1] = '\0';
    }

    bool escribirProductoTexto(const Producto& producto) {
        //abre en modo append+ (lectura y escritura al final)
        FILE* archivo = fopen(nombreArchivo, "a+");
        if (!archivo) {
            printf("Error: no se pudo abrir/crear el archivo %s\n", nombreArchivo);
            return false;
        }

        // Velve al inicio para verificar si existe el ID
        rewind(archivo);
        
        char linea[256];
        int id;
        // Revisa si ya existe el producto
        while (fgets(linea, sizeof(linea), archivo) != NULL) {
            if (sscanf(linea, "%d", &id) == 1) {
                if (id == producto.getID()) {
                    printf("Erroreishon: producto con ID %d ya existe\n", id);
                    fclose(archivo);
                    return false;
                }
            }
        }

        //escribe al final del archivo
        fprintf(archivo, "%d,%d,%.2f\n", 
                producto.getID(),
                producto.getStock(),
                producto.getPrecio());

        fclose(archivo);
        return true;
    }

    bool escribirProducto(const Producto& producto) {
        // Abre en lectura/escritura binaria
        FILE* archivo = fopen(nombreArchivo, "r+b");
        if (!archivo) {
            // Si no existe crea el archivp
            archivo = fopen(nombreArchivo, "wb");
            if (!archivo) return false;
        }

        int id, stock;
        float precio;
        // Revisa si ya existe el producto
        while (fread(&id, sizeof(int), 1, archivo) == 1) {
            fread(&stock, sizeof(int), 1, archivo);
            fread(&precio, sizeof(float), 1, archivo);

            if (id == producto.getID()) {
                printf("Error: producto con ID %d ya existe\n", id);
                fclose(archivo);
                return false;
            }
        }

        // Mueve the cursor al final para escribir
        fseek(archivo, 0, SEEK_END);

        int newId = producto.getID();
        int newStock = producto.getStock();
        float newPrecio = producto.getPrecio();

        fwrite(&newId, sizeof(int), 1, archivo);
        fwrite(&newStock, sizeof(int), 1, archivo);
        fwrite(&newPrecio, sizeof(float), 1, archivo);

        fclose(archivo);
        return true;
    }

    bool leerProductos() {
        FILE* archivo = fopen(nombreArchivo, "rb");
        if (!archivo) {
            printf("Error: no se pudo leer el archivo ostias%s\n", nombreArchivo);
            return false;
        }

        printf("contenido de %s\n", nombreArchivo);

        int numeroProducto = 1;
        int id, stock;
        float precio;

        // Lee los 3 campos por producto. fread devuelve 1 si leyo 1 elemento.
        while (fread(&id, sizeof(int), 1, archivo) == 1) {
            // ahora si leem el stock y precio (si falla tira archivo corrupto/parcial)
            if (fread(&stock, sizeof(int), 1, archivo) != 1 ||
                fread(&precio, sizeof(float), 1, archivo) != 1) {
                printf("Error: archivo corrupto o fallido\n");
                break;
            }

            printf("Producto %d: ID=%d, Stock=%d, Precio=%.2f\n",
                numeroProducto, id, stock, precio);
                numeroProducto++;
        }

        fclose(archivo);
        return true;
    }

    bool actualizarStock(int idProducto, int nuevoStock) {
        FILE* archivo = fopen(nombreArchivo, "r+b");
        if (!archivo) {
            printf("Error: no se pudo abrir el archivo %s\n", nombreArchivo);
            return false;
        }

        int id, stock;
        float precio;
        bool encontrado = false;

        while (fread(&id, sizeof(int), 1, archivo) == 1) {
            long posicionStock = ftell(archivo); // apunta al inicio del campo stock

            // lee el stock y precio para avanzar el cursor
            if (fread(&stock, sizeof(int), 1, archivo) != 1 ||
                fread(&precio, sizeof(float), 1, archivo) != 1) {
                printf("Error: archivo corrupto o truncado\n");
                break;
            }

            if (id == idProducto) {
                // vuelce a la posición del stock y sobrescribe
                if (fseek(archivo, posicionStock, SEEK_SET) != 0) {
                    printf("Error: fseek falló\n");
                    break;
                }
                if (fwrite(&nuevoStock, sizeof(int), 1, archivo) != 1) {
                    printf("Error: no se pudo escribir el nuevo stock\n");
                    break;
                }
                encontrado = true;
                break;
            }
        }

        fclose(archivo);

        if (encontrado) {
            printf("Stock actualizado para ID %d: %d\n", idProducto, nuevoStock);
            return true;
        } else {
            printf("Producto con ID %d no encontrado\n", idProducto);
            return false;
        }
    }

    int obtenerStock(int idProducto) {
        FILE* archivo = fopen(nombreArchivo, "rb");
        if (!archivo) return -1;

        int id, stock;
        float precio;

        while (fread(&id, sizeof(int), 1, archivo) == 1) {
            if (fread(&stock, sizeof(int), 1, archivo) != 1 ||
                fread(&precio, sizeof(float), 1, archivo) != 1) {
                break;
            }

            if (id == idProducto) {
                fclose(archivo);
                return stock;
            }
        }

        fclose(archivo);
        return -1;
    }
};

// EJEMPLO

/*int main() {
    SQCopy gestor("productos.dat");
    
    Producto producto("Manzana", "Fruta", 101, 50, 0.5, Fecha(1, 1, 2023));

    gestor.escribirProducto(producto);
    gestor.leerProductos();
    
    gestor.actualizarStock(101, 75);
    gestor.leerProductos();
    
    int stock = gestor.obtenerStock(102);
    if (stock != -1) {
        printf("Stock del producto con ID 102: %d\n", stock);
    } else {
        printf("Producto con ID 102 no encontrado\n");
    }
    return 0;
}*/