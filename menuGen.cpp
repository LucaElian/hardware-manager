

#include <iostream>
#include "menuGen.h"
#include "menuProducto.h"
#include "menuCliente.h"
#include "Contexto.h"
#include "utilidades.h"
#include "artworks.h"
using namespace std;

#define byte windows_byte
#include "rlutil.h"
#undef byte

///ESTA FUNCION MUESTRA EL MENU Y CONTROLA CON RLUTIL EL MOVIMIENTO DE LAS FLECHAS ---------------------------
//recibe el archivo del gestor para pasarselo a todos los menues, y el struct contexto con todos los objetos, tambien para pasarle a los menues
<<<<<<< HEAD
void MenuGen::mostrarMenuPrincipal(ContextoGestores gestores, Contexto objetos) {
    string opciones[4] = {"GESTIONAR PRODUCTOS", "GESTIONAR CLIENTE", "VENTAS", "SALIR"};

    while(true) {
=======
void MenuGen::mostrarMenuPrincipal(ContextoGestores gestores, Contexto objetos)
{
    string opciones[3] = {"GESTIONAR PRODUCTOS", "GESTIONAR CLIENTE", "SALIR"};

    while(true)
    {
>>>>>>> f33bb5de07063265a7f9d952ac53fcc7951314da
        rlutil::hidecursor();
        int opcion = 0;
        bool curs = true;
        system("cls");

        titulo();
        menu("M E N U   G E S T O R", opciones, 10, 4);

<<<<<<< HEAD
        while(curs == true) {
=======
        while(curs == true)
        {
>>>>>>> f33bb5de07063265a7f9d952ac53fcc7951314da
            rlutil::locate(45, 16 + opcion);
            cout << (char)175;

            int pos = rlutil::getkey(); // Captura de teclas

<<<<<<< HEAD
            switch(pos) {
                case 14:
                    rlutil::locate(45, 16 + opcion);
                    cout << " ";
                    opcion -= 2;
                    if(opcion < 0) opcion = 4;
                    break;
=======
            switch(pos)
            {
            case 14:
                rlutil::locate(45, 16 + opcion);
                cout << " ";
                opcion -= 2;
                if(opcion < 0) opcion = 4;
                break;
>>>>>>> f33bb5de07063265a7f9d952ac53fcc7951314da

            case 15:
                rlutil::locate(45, 16 + opcion);
                cout << " ";
                opcion += 2;
                if(opcion > 4) opcion = 0;
                break;

<<<<<<< HEAD
                case 1:
                    system("cls");
                    curs = false;
                    switch(opcion) {
                        case 0: menuProducto(objetos.producto, gestores.gestorP); break;
                        case 2: menuCliente(objetos.cliente, gestores.gestorC); break;
                        case 4: return;
                    }
=======
            case 1:
                system("cls");
                curs = false;
                switch(opcion)
                {
                case 0:
                    menuProducto(objetos.producto, gestores.gestorP);
                    break;
                case 2:
                    menuCliente(objetos.cliente, gestores.gestorC);
                    break;
                case 4:
                    return;
                }
>>>>>>> f33bb5de07063265a7f9d952ac53fcc7951314da
            }
        }
    }
}




