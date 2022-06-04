#include "..\include\Cadena.h"

Cadena::Cadena(){

    this->cadena=NULL;
}

Cadena::~Cadena(){
    delete [] this->cadena;
}


Cadena::Cadena(char* str){

    char* nuevaCad = new char[strlen(str)+1];

    strcpy(nuevaCad,str);

    this->cadena = nuevaCad;

}

Cadena Cadena::operator +(Cadena& cad2){

    Cadena nuevaCadena;

    nuevaCadena.cadena = new char[strlen(this->cadena)+strlen(cad2.cadena)+1];

    strcpy(nuevaCadena.cadena,this->cadena);
    strcat(nuevaCadena.cadena,cad2.cadena);

    return nuevaCadena;

}

ostream& operator <<(ostream& os,Cadena cad){

    os << cad.cadena;

    return os;

}
