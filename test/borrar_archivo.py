import os
archivos = ["clientes.dat","detalles_venta.dat"
            ,"productos.dat","ventas.dat", "vendedores.dat"]
for a in archivos:
    try:
        os.system(f"del {a}")
        os.system(f"echo {a} removed")
    except:
        os.system("echo Hubo un error al borrar")
