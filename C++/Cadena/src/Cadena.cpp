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

    char* nuevoPuntero;

    nuevoPuntero = new char[strlen(this->cadena)+strlen(cad2.cadena)+1];

    strcpy(nuevoPuntero,this->cadena);
    strcat(nuevoPuntero,cad2.cadena);

    return Cadena(nuevoPuntero);

}

ostream& operator <<(ostream& os,Cadena& cad1){

    os << cad1.cadena;

    return os;

}
