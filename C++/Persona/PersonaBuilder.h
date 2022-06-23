#ifndef PERSONABUILDER_H
#define PERSONABUILDER_H

#include "..\Cadena\include\Cadena.h"
#include "..\Fecha\include\Fecha.h"
#include "Persona.h"

class PersonaBuilder
{
    public:
        PersonaBuilder();

        PersonaBuilder& setDNI(const Cadena& dni);
        PersonaBuilder& setNombre(const Cadena& nombre);
        PersonaBuilder& setApellido(const Cadena& apellido);
        PersonaBuilder& setFechaNacimiento(const Fecha& fechaNacimiento);
        PersonaBuilder& setSexo(char sexo);

        Persona build();

    private:
        Cadena dni;
        Cadena nombre;
        Cadena apellido;
        Fecha fechaNacimiento;
        char sexo;

        //static bool validarDNI(Cadena dni);
};

#endif // PERSONABUILDER_H
