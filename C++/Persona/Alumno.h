#ifndef ALUMNO_H
#define ALUMNO_H

#include "Persona.h"


class Alumno : public Persona
{
    public:
        Alumno(const Cadena& dni,const Cadena& nombre, const Cadena& apellido, const Fecha& fechaNacimiento, char sexo,const Cadena& curso,const int cantMatAprob,const float promedio);

    private:
        Cadena curso;
        int cantMatAprob;
        float promedio;

};

#endif // ALUMNO_H
