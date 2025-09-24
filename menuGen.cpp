#include "rlutil.h"
#include <iostream>

class menuGen{
    public:
        /*Porque static?
        Porque no necesitamos instanciar un objeto de la clase menuGen para usar sus metodos.
        */
        static void mostrarMenuPrincipal(){
            rlutil::cls();
            rlutil::setColor(rlutil::YELLOW);
            rlutil::locate(35,1);
            std::cout << "===================" << std::endl;
            rlutil::locate(35,2);
            std::cout << "GESTION DE HARDWARE" << std::endl;
            rlutil::locate(35,3);
            std::cout << "===================" << std::endl;
            rlutil::setColor(rlutil::WHITE);
            std::cout << "1. Gestionar Productos" << std::endl;
            std::cout << "2. Gestionar Usuarios" << std::endl;
            std::cout << "3. Salir" << std::endl;
            std::cout << "Seleccione una opcion: ";
        }

        static void seleccionarOpcion(int opcion){
            switch(opcion){
                case 1:
                    // Llamar a la funcion para gestionar productos
                    break;
                case 2:
                    // Llamar a la funcion para gestionar usuarios
                    break;
                case 3:
                    std::cout << "Saliendo del programa..." << std::endl;
                    break;
                default:
                    std::cout << "Opcion invalida. Intente de nuevo." << std::endl;
                    break;
            }
        }
};