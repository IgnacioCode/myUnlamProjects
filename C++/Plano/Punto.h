#ifndef PUNTO_H
#define PUNTO_H

#include <iostream>

using namespace std;

class Punto
{
    public:
        Punto();
        Punto(const double& x,const double& y);
        double getX()const;
        double getY()const;
    protected:

    private:
        double x;
        double y;
};
ostream& operator <<(ostream& os,const Punto& p);

#endif // PUNTO_H
