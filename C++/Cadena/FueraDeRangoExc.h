#ifndef FUERADERANGOEXC_H
#define FUERADERANGOEXC_H

#include "include\Cadena.h"

class FueraDeRangoExc{
    public:
        FueraDeRangoExc(const Cadena& mensaje);
        const Cadena& getMensaje()const;
    protected:

    private:
        Cadena mensaje;
};

#endif // FUERADERANGOEXC_H
