#ifndef MENU_REPORTS_H
#define MENU_REPORTS_H

#include "iostream"
#include "archivoManager.h"
#include "rlutil.h"
#include "artworks.h"
#include <utility> // <-- Necesario para std::pair

#include "ContextoGestores.h"
#include "Contexto.h"

void menuReports(Contexto objetos, ContextoGestores& gestores);

void opcion1(Contexto objetos, ContextoGestores& gestores);

void opcion2(Contexto objetos, ContextoGestores& gestores);

void opcion3(Contexto objetos, ContextoGestores& gestores);

void opcion4(Contexto objetos, ContextoGestores& gestores);

void opcion5(Contexto objetos, ContextoGestores& gestores);

#endif // MENU_REPORTS_H
