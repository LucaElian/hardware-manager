# 💻 Sistema de gestion de una tienda de hardware
## Miembros del proyecto:
- Thiago Núñez  
- Zadquiel Juan Bautista Gallardo
- Luca Elian Abulafia
 
Este proyecto es un sistema gestor desarollado completamente en C++, desarollado principalmente en codeblocks utilizando la manipulacion de archivos para guardar los datos.
---
## 🔄 Navegación del programa
Al iniciar veras un menu y elegiras con un numero la opcion.
----------Bienvenido a compra gaymer-----------
ingresen un numero para elegir su opcion:
0. Salir del prograna
1. Registrarse
2. Iniciar sesion
3. Administrar productos
Opcion:

**Si elige la opcion 3**: Sera enviado al menu para los productos

---
## 📦 Funcionalidades actuales

- 📄 Carga y escritura de productos en archivo binario.
- 📋 Listado de productos existentes.
- ❌ Prevención de duplicados por ID.
- 🗓️ Manejo de fechas con clase `Fecha` tanto para ingreso de productos como para registro de usuarios.
- 📁 Abstracción del manejo de archivos mediante `GestorArchivos`.

---

## 🧱 Estructura del proyecto
**Clases:**
- **Producto**: Clase que representa un producto de hardware (ID, nombre, tipo, precio, stock).
- **Usuario**: Clase que representará usuarios comunes o administradores (en desarrollo).
- **Fecha**: Manejo básico de fechas (creación de productos, registro, etc).
- **GestorArchivos**: Maneja la lectura y escritura de productos en un archivo binario.
**Utilidades:**
- **CargarCadena**: Archivo que recibe caracteres y lo convierte en cadena**
- **Utilidades**: Asi se llama el archivo que tiene metodos utiles como "toUpperCase".
- **Menu producto**: Archivo que contiene el menu para manipular los productos
---

## 🚧 Funcionalidades futuras

- 🔐 Sistema de login con roles (usuario y administrador).
- 🛒 Gestión de compras y ventas (en produccion). 
- 📈 Reportes por fecha o tipo de producto.
- 🧑‍💼 Administración de usuarios.

---

## 💾 Compilación

//thiago fijate vos que sabes que podrias poner aca
Este proyecto está escrito en C++ (C++11 o superior recomendado). Para compilarlo:

```bash
g++ main.cpp -o tienda_hardware
Asegúrate de incluir todos los archivos .cpp y .h necesarios.

🗂️ Estructura de carpetas esperada
bash
Copiar código
/tu-proyecto/
├── src/
│   ├── cargarCadena.cpp
|   ├── clsFecha
│   ├── clsProducto.cpp
│   ├── clsUsuario.cpp
│   ├── GestorArchivos.cpp
|   ├── main.cpp
|   ├── menuProducto.cpp
|   ├── utilidades.cpp
├── headers/
│   ├── cargarCadena.h
│   ├── Usuario.h
│   ├── Fecha.h
│   ├── GestorArchivos.h
├── productos.dat  # Archivo binario generado
├── README.md
