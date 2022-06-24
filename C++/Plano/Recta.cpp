#include "Recta.h"
#include <cmath>

#define ABS(X) (X<0?(-X):(X))
#define x_1 (this->p1.getX())
#define x_2 (this->p2.getX())
#define x_3 (r2.p1.getX())
#define x_4 (r2.p2.getX())

#define y_1 (this->p1.getY())
#define y_2 (this->p2.getY())
#define y_3 (r2.p1.getY())
#define y_4 (r2.p2.getY())

using namespace std;

Recta::Recta(const Punto& p1,const Punto& p2){
    this->p1=p1;
    this->p2=p2;
}

double Recta::distanciaPuntoARecta(const Punto& p2){

    double numerador;
    double denominador;

    numerador = ABS( (this->p2.getY() - this->p1.getY() )*p2.getX() - (this->p2.getX() - this->p1.getX() ) * p2.getY() + this->p2.getX() * this->p1.getY() - this->p2.getY() * this->p1.getX());
    denominador = sqrt( pow(this->p2.getY() - this->p1.getY(),2) + pow(this->p2.getX() - this->p1.getX(),2) );
    return numerador/denominador;
}
Punto Recta::interseccionConRecta(const Recta& r2){
    double xPunto = ( (x_1*y_2 - y_1*x_2)*(x_3 - x_4) - (x_1 - x_2)*(x_3*y_4 - y_3*x_4) )/( (x_1 - x_2)*(y_3 - y_4) - (y_1 - y_2)*(x_3 - x_4) );
    double yPunto = ( (x_1*y_2 - y_1*x_2)*(y_3 - y_4) - (y_1 - y_2)*(x_3*y_4 - y_3*x_4) )/( (x_1 - x_2)*(y_3 - y_4) - (y_1 - y_2)*(x_3 - x_4) );

    return Punto(xPunto,yPunto);
}

Punto Recta::getP1()const{
    return this->p1;
}

Punto Recta::getP2()const{
    return this->p2;
}

ostream& operator <<(ostream& os,const Recta& r){

    double m,b;
    if(r.getP1().getX() == r.getP2().getX()){
        os<< "x=" << r.getP2().getX();
        return os;
    }
    m = ( r.getP2().getY() - r.getP1().getY() ) / ( r.getP2().getX() - r.getP1().getX() );
    b = r.getP2().getY() - m * r.getP2().getX();

    os << "y=" << m << "x+" << b;
    return os;

}

double Recta::operator -(const Punto& p2){
    return this->distanciaPuntoARecta(p2);
}
Punto Recta::operator &&(const Recta& r2){
    return this->interseccionConRecta(r2);
}
