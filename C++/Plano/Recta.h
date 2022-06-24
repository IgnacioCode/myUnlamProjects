#ifndef RECTA_H
#define RECTA_H

#include <iostream>

using namespace std;

#include "Punto.h"

class Recta
{
    public:

        Recta();
        Recta(const Punto& p1,const Punto& p2);
        
        double distanciaPuntoARecta(const Punto& p2);
        Punto interseccionConRecta(const Recta& r2);

        Punto getP1()const;
        Punto getP2()const;

        double operator -(const Punto& p2);
        Punto operator &&(const Recta& r2);
    protected:

    private:
        Punto p1;
        Punto p2;

};
ostream& operator <<(ostream& os,const Recta& r);

#endif // RECTA_H
