import os
import platform
def echo(message):
    os.system(f'echo {message}')

def borrar_archivos_dat():
    """
    Borra archivos .dat del proyecto de forma segura y multiplataforma
    """
    archivos = [
        "clientes.dat",
        "detalles_venta.dat",
        "productos.dat",
        "ventas.dat",
        "vendedores.dat"
    ]
    
    archivos_borrados = 0
    archivos_no_encontrados = 0
    errores = 0
    
    for archivo in archivos:
        try:
            if os.path.exists(archivo):
                os.remove(archivo)  # Mas pythonico que os.system
                echo(f"{archivo} eliminado exitosamente")
                archivos_borrados += 1
            else:
                echo(f"{archivo} no encontrado (ya estaba eliminado)")
                archivos_no_encontrados += 1
                
        except PermissionError:
            echo(f"Error: {archivo} está en uso o sin permisos")
            errores += 1
            
        except Exception as e:
            echo(f"Error al borrar {archivo}: {str(e)}")
            errores += 1
    
    return archivos_borrados, errores

if __name__ == "__main__":
    borrar_archivos_dat()