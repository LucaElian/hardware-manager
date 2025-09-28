#include <iostream>
#include <cstring>  // For strlen or similar, if needed
void cargarCadena(char* palabra, int maxLen) {
    int i = 0;
    int ch;  // Use int to store cin.get() result
    while (i < maxLen - 1) {  // Leave space for null terminator
        ch = std::cin.get();
        if (ch == EOF || ch == '\n') {  // Stop on EOF or newline
            break;
        }
        palabra[i] = static_cast<char>(ch);  // Safe explicit cast
        ++i;
    }
    palabra[i] = '\0';  // Null-terminate the string
}

/// FIJATE SI TE SIRVE, ESTA HECHO CON GPT PERO ES PA SACAR EL WARNING.
/// Y PONELO EN UTILIDADES.CPP Y UTILIDADES.H PANCHO, NO CREAS UN ARC
/// SOLO POR UNA FUNCION.

// #include <iostream>
// using namespace std;

// void cargarCadena(char *palabra, int tam){
//     int i=0;
//     fflush(stdin);
//     for (i=0; i<tam; i++){
//         palabra[i]=cin.get();
//         if (palabra[i]=='\n'){
//             break;
//         }
//     }
//     palabra[i]='\0';
//     fflush(stdin);
// }