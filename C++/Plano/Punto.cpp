#include "Punto.h"

Punto::Punto(){
    x=0;
    y=0;
}

Punto::Punto(const double& x,const double& y){
    this->x=x;
    this->y=y;
}

double Punto::getX()const{
    return this->x;
}
double Punto::getY()const{
    return this->y;
}

ostream& operator <<(ostream& os,const Punto& p){
    os << '(' << p.getX() << ',' << p.getY() << ')';
    return os;
}
