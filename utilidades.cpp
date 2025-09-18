#include <iostream>
using namespace std;

void toUpperCase(char *texto){
    for(int x = 0; texto[x] != '\0'; ++x){
        if(texto[x] >= 'a' && texto[x] <= 'z'){
            texto[x] = texto[x] - 32;
        }
    }
}
