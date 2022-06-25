#ifndef MEDICION_H
#define MEDICION_H

#include <iostream>

using namespace std;

class Medicion
{
    public:
        Medicion();
        Medicion(const float medicion,const char* unidad);
        ~Medicion();

        float getMedicion()const;
        char* getUnidad()const;

        Medicion operator -(Medicion& med2);
        friend Medicion operator +(float num,Medicion& med2);
        friend ostream& operator <<(ostream& os,const Medicion& med);
    protected:

    private:
        float medicion;
        char* unidad;
};

#endif // MEDICION_H
