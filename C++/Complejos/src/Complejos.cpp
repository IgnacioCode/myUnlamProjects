#include "Complejos.h"

Complejos::Complejos(){

}

Complejos::Complejos(float a,float b){
    this->parteReal=a;
    this->parteImaginaria=b;
}

void Complejos::setParteReal(float a){
    this->parteReal=a;
}
float Complejos::getParteReal()const{
    return this->parteReal;
}
void Complejos::setParteImaginaria(float b){
    this->parteImaginaria=b;
}
float Complejos::getParteImaginaria()const{
    return this->parteImaginaria;
}

Complejos Complejos::operator +(const Complejos& z2)const{
    return Complejos(this->parteReal+z2.parteReal,this->parteImaginaria+z2.parteImaginaria);
}

Complejos Complejos::operator -(const Complejos& z2)const{
    return Complejos(this->parteReal-z2.parteReal,this->parteImaginaria-z2.parteImaginaria);
}

double Complejos::modulo()const{

    double sumaCuadrados = pow(this->parteReal,2)+pow(this->parteImaginaria,2);

    return sqrt(sumaCuadrados);

}

ostream& operator <<(ostream& os,const Complejos& z1){

    os << z1.getParteReal() << '+'<< z1.getParteImaginaria() << 'i';
    return os;

}

istream& operator >>(istream& is,Complejos& z2){

    char aux;
    float pR,pI;

    cin >> pR >> aux >> pI >> aux;

    z2.setParteImaginaria(pI);
    z2.setParteReal(pR);

    return is;

}

