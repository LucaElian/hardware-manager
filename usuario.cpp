#include <iostream>

#include "usuario.h"

using namespace std;

Usuario::Usuario(char _user[20], char _pass[20], char _rol[20], Fecha _fecha){
    strcpy(user, _user);
    strcpy(pass, _pass);
    strcpy(rol, _rol);
    ingresa = _fecha;
}
