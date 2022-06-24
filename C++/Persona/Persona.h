#ifndef PERSONA_H
#define PERSONA_H

#include "..\Cadena\include\Cadena.h"
#include "..\Fecha\include\Fecha.h"

class Persona{

    public:
        Persona();
        

        const Cadena& getDNI()const;
        const Cadena& getNombre()const;
        const Cadena& getApellido()const;
        const Fecha& getFechaNacimiento()const;
        const char getSexo()const;

        void setDNI(const Cadena& dni);
        void setNombre(const Cadena& nombre);
        void setApellido(const Cadena& apellido);
        void setFechaNacimiento(const Fecha& fechaNacimiento);
        void setSexo(char sexo);

        friend class PersonaBuilder;
    protected:
        Persona(const Cadena& dni,const Cadena& nombre, const Cadena& apellido, const Fecha& fechaNacimiento, char sexo);
    private:
        Cadena dni;
        Cadena nombre;
        Cadena apellido;
        Fecha fechaNacimiento; 
        char sexo;

        
        static bool validarDNI(Cadena dni);
};

ostream& operator <<(ostream& os,const Persona& persona);
istream& operator >>(istream& is,const Persona& persona);

#endif // PERSONA_H
