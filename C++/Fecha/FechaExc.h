#ifndef FECHAEXC_H
#define FECHAEXC_H

#include "..\Cadena\include\Cadena.h"

class FechaExc
{
    public:
        FechaExc(const Cadena& mensaje);
        const Cadena& getMensaje()const; 
    protected:

    private:
        Cadena mensaje;

};

#endif // FECHAEXC_H
