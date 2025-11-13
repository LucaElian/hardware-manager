#include "constantes.h" // Incluye las declaraciones 'extern'
#include <cstddef>     // Para size_t

/* ===================================================================
 * DEFINICIONES DE CONSTANTES GLOBALES
 * ===================================================================*/
// Aquí les damos el valor real.
// Como esto es un .cpp, solo se compilará UNA SOLA VEZ.

// CONSTANTES DE UI PARA PRODUCTO
const size_t PRODUCTO_OPCIONES_MENU = 5;
const size_t PRODUCTO_OPCIONES_CARGA = 7;
const int PRODUCTO_INICIO_TITULO = 3;
const int PRODUCTO_INICIO_TABLA = PRODUCTO_INICIO_TITULO + 5;
const int PRODUCTO_CURSOR_START_X = 3;
const int PRODUCTO_CURSOR_START_Y = 4;
const int PRODUCTO_PAGINADO = 15;

// CONSTANTES DE UI PARA CLIENTE
const size_t CLIENTE_OPCIONES_MENU = 4;
const size_t CLIENTE_OPCIONES_CARGA = 3;
const int CLIENTE_INICIO_TITULO = 3;
// ... (agrega aquí el resto de las constantes de Cliente)

// CONSTANTES DE UI PARA VENDEDOR
const size_t VENDEDOR_OPCIONES_MENU = 5;
const size_t VENDEDOR_OPCIONES_CARGA = 6;
// ... (agrega aquí el resto de las constantes de Vendedor)
