#ifndef ENTIDAD_H_INCLUDED
#define ENTIDAD_H_INCLUDED

#include "clsFecha.h"

class Entidad {
protected:
    int id;
    bool estado;
    Fecha fechaIngreso;

public:
    // Constructor
    Entidad(int _id = 0, bool _estado = true, Fecha _fecha = Fecha(1,1,1))
        : id(_id), estado(_estado), fechaIngreso(_fecha) {}

    // Destructor virtual para herencia correcta, sino falla
    virtual ~Entidad() {}

    // Setters comunes
    void setID(int _id) { id = _id; }
    void setEstado(bool _estado) { estado = _estado; }
    void setFecha(int dia, int mes, int anio) { 
        fechaIngreso = Fecha(dia, mes, anio); 
    }

    // Getters comunes
    int getID() const { return id; }
    bool getEstado() const { return estado; }
    Fecha getFecha() const { return fechaIngreso; }

    // Metodos virtuales puros - cada clase debe implementarlos
    virtual void cargar() = 0;
    virtual void mostrar() = 0;
};

#endif // ENTIDAD_H_INCLUDED