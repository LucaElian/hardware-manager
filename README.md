# Sistema de Gestión de Hardware Gaming
> Sistema de gestión empresarial desarrollado en C++ para la administración integral de inventario y clientes en tiendas de hardware gaming.

## Descripción General
Sistema diseñado para optimizar la gestión de inventario y clientes en comercios especializados en hardware gaming, implementando una arquitectura modular y robusta con persistencia de datos.

## Características Técnicas

### Gestión de Datos
- Implementación de CRUD completo para productos y clientes
- Sistema de persistencia mediante archivos binarios
- Manejo eficiente de memoria
- Validación de datos en tiempo real
- Control de concurrencia básico

### Arquitectura
- Diseño orientado a objetos
- Implementación de patrones de diseño
- Sistema de templates para gestión de datos
- Separación clara de responsabilidades (MVC)

### Seguridad
- Sistema de roles y permisos
- Validación de entrada de datos
- Gestión de errores y excepciones
- Registro de operaciones críticas

## Estructura del Proyecto

```
project/
├── include/
│   ├── models/           # Definiciones de clases base
│   ├── managers/         # Gestores de datos
│   └── ui/              # Interfaces de usuario
├── src/
│   ├── models/          # Implementaciones de modelos
│   ├── managers/        # Lógica de negocio
│   └── ui/             # Implementación de interfaces
├── data/               # Archivos de datos
```

### Dependencias
- Biblioteca estándar de C++
- RLUtil para interfaces de terminal
- Filesystem (C++17)

## Instalación y Configuración

1. Clonar el repositorio:
```bash
git clone https://github.com/usuario/GestorHardware.git
```

2. Compilar el proyecto:
```bash
cd GestorHardware
make all
```

3. Ejecutar la aplicación:
```bash
./bin/GestorHardware
```

## Documentación Técnica

### Clases Principales

#### ArchivoManager<T>
Template para gestión de persistencia de datos.
```cpp
ArchivoManager<T>(const char* archivo);
bool escribir(T* objeto);
bool leer();
bool eliminarPorID(int id);
```

#### Entidad
Clase base abstracta para objetos persistentes.
```cpp
virtual int getID() const = 0;
virtual void setEstado(bool estado) = 0;
virtual bool getEstado() const = 0;
```

## Mantenimiento y Soporte

### Control de Versiones
- Sistema de versionado: Git
- Repositorio principal: GitHub
- Política de branches: GitFlow

### Testing
- Framework: Google Test
- Cobertura mínima: 80%
- Tests unitarios y de integración

## Equipo de Desarrollo
- **Arquitecto de Software:** Thiago Núñez
- **Desarrollador Senior:** Zadquiel Juan Bautista Gallardo
- **Desarrollador:** Luca Elian Abulafia

## Licencia
Este proyecto está bajo la Licencia MIT. Consulte el archivo `LICENSE` para más detalles.

## Contacto
Para reportar bugs o sugerir mejoras, por favor crear un issue en el repositorio de GitHub o contactar al equipo de desarrollo.

---
*Versión de la documentación: 1.0.0*
*Última actualización: Octubre 2023*