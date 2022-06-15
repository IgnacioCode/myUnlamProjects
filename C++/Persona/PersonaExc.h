#ifndef PERSONAEXC_H
#define PERSONAEXC_H

#include "..\Cadena\include\Cadena.h"

class PersonaExc
{
    public:
        PersonaExc(const Cadena& mensaje);
        const Cadena& getMensaje()const;
    protected:

    private:
        Cadena mensaje;
};

#endif // PERSONAEXC_H
