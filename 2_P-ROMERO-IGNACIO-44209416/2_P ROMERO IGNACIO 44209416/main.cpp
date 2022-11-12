#include <iostream>
#include <cmath>

#define ABS(X) (X<0? (-X):(X) )

using namespace std;

class Punto
{
    public:
        Punto();
        Punto(const double x,const double y);
        double getX()const;
        double getY()const;

    protected:

    private:
        double x;
        double y;
};

class Recta
{
    public:
        Recta();
        Recta(const Punto& p1,const Punto& p2);

        Punto getP1()const;
        Punto getP2()const;
        Punto operator &&(const Recta& r2);
        double operator -(const Punto& p);
    protected:

    private:
        Punto p1;
        Punto p2;
};

ostream& operator <<(ostream& os,const Punto& p);
ostream& operator <<(ostream& os,const Recta& r);

int main(){
    Recta r1(Punto(2, 0), Punto(0, 2));
    Recta r2(Punto(1, 0), Punto(1, 2));

    Punto p(2, 2);

    cout << "Punto de Interseccion entre las rectas " << r1 << " y " << r2 << ": " << (r1 && r2) << endl;

    cout << "Distancia del punto " << p << " a la recta " << r1 << ": " << (r1 - p) << endl;

    cout << "Distancia del punto " << p << " a la recta " << r2 << ": " << (r2 - p) << endl;

    return 0;
}

Punto::Punto(){
    x=0;
    y=0;
}

Punto::Punto(const double x,const double y){
    this->x=x;
    this->y=y;
}

Recta::Recta(){
    Punto p1;
    Punto p2;
    this->p1 = p1;
    this->p2 = p2;
}

Recta::Recta(const Punto& p1,const Punto& p2){
    this->p1 = p1;
    this->p2 = p2;
}

Punto Recta::operator &&(const Recta& r2){

    double x_1 = this->p1.getX();
    double x_2 = this->p2.getX();
    double x_3 = r2.p1.getX();
    double x_4 = r2.p2.getX();

    double y_1 = this->p1.getY();
    double y_2 = this->p2.getY();
    double y_3 = r2.p1.getY();
    double y_4 = r2.p2.getY();

    double numerador, denominador;

    numerador = (x_1*y_2 - y_1*x_2)*(x_3-x_4) - (x_1-x_2)*(x_3*y_4 - y_3*x_4);
    denominador = (x_1-x_2)*(y_3-y_4) - (y_1-y_2)*(x_3-x_4);

    double xRes = numerador/denominador;

    numerador = (x_1*y_2 - y_1*x_2)*(y_3-y_4) - (y_1-y_2)*(x_3*y_4 - y_3*x_4);
    double yRes = numerador/denominador;
    return Punto(xRes,yRes);

}

double Recta::operator -(const Punto& p){
    double x_1 = this->p1.getX();
    double x_2 = this->p2.getX();
    double x_0 = p.getX();

    double y_1 = this->p1.getY();
    double y_2 = this->p2.getY();
    double y_0 = p.getY();

    double numerador, denominador;

    numerador = ABS((y_2-y_1)*x_0 - (x_2-x_1)*y_0 + x_2*y_1 - y_2*x_1);
    denominador = sqrt(pow(y_2-y_1,2) + pow(x_2-x_1,2));

    return numerador/denominador;
}

ostream& operator <<(ostream& os,const Punto& p){
    os << '(' << p.getX() << ',' << p.getY() << ')';
    return os;
}
ostream& operator <<(ostream& os,const Recta& r){

    double m,b;
    if(r.getP1().getX() == r.getP2().getX()){
        os << "x=" << r.getP1().getX();
        return os;
    }
    m = ( r.getP2().getY() - r.getP1().getY() )/ (r.getP2().getX() - r.getP1().getX());
    b = r.getP1().getY() - m*r.getP1().getX();

    os << "y=" << m <<"x+(" << b <<')';
    return os;

}

double Punto::getX()const{
    return this->x;
}

double Punto:: getY()const{
    return this->y;
}

Punto Recta::getP1()const{
    return this->p1;
}
Punto Recta::getP2()const{
    return this->p2;
}
