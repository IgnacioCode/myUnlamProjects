#ifndef COMPLEJOS_H
#define COMPLEJOS_H

#include <iostream>
#include <cmath>

using namespace std;

class Complejos{
    public:

        Complejos();
        Complejos(float a,float b);

        void setParteReal(float a);
        float getParteReal()const;
        void setParteImaginaria(float b);
        float getParteImaginaria()const;

        Complejos operator +(const Complejos& z2)const;
        Complejos operator -(const Complejos& z2)const;
        Complejos operator *(const Complejos& z2)const;
        Complejos operator /(float& a);


        double modulo()const;

    protected:

    private:
        float parteReal;
        float parteImaginaria;
};

ostream& operator <<(ostream& os,const Complejos& z1);
istream& operator >>(istream& is,Complejos& z2);


#endif // COMPLEJOS_H
