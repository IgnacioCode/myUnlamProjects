#include "VectorEnteros.h"

#define TAM_INT (sizeof(int))

VectorEnteros::VectorEnteros(){
    cantElem=0;
    vec=NULL;
}
VectorEnteros::~VectorEnteros(){
    delete [] vec;
    this->vec = NULL;
    cout << "destrui un objeto" << endl;
}
/*VectorEnteros::VectorEnteros(const VectorEnteros& vec2){
    this->vec = new int[vec2.cantElem];
    memcpy(this->vec,vec2.vec,vec2.cantElem*TAM_INT);
    this->cantElem = vec2.cantElem;
}*/
VectorEnteros::VectorEnteros(const int* vec,const unsigned cantElem){

    this->vec = new int[cantElem];
    memcpy(this->vec,vec,cantElem*TAM_INT);
    this->cantElem=cantElem;
}
/*
VectorEnteros::VectorEnteros(const VectorEnteros& vec1,const VectorEnteros vec2){
    this->vec = new int[vec1.cantElem + vec2.cantElem];
    memcpy(this->vec,vec1.vec,vec1.cantElem*TAM_INT);
    memcpy(this->vec+vec1.cantElem*TAM_INT,vec2.vec,vec2.cantElem*TAM_INT);
    this->cantElem = vec1.cantElem+vec2.cantElem;
}*/

VectorEnteros& VectorEnteros::agregar(const int* vec, const unsigned cantElem){

    this->vec = (int*)realloc(this->vec,cantElem*TAM_INT + this->cantElem*TAM_INT);
    memcpy(this->vec+this->cantElem/**TAM_INT*/,vec,cantElem*TAM_INT);
    this->cantElem +=cantElem;

    return *this;
}

VectorEnteros VectorEnteros::operator +(const VectorEnteros& vec2){

    int* vecAux = new int[this->cantElem + vec2.cantElem];
    memcpy(vecAux,this->vec,this->cantElem*TAM_INT);
    memcpy(vecAux+this->cantElem,vec2.vec,vec2.cantElem*TAM_INT);
    VectorEnteros objAux;
    objAux.vec = vecAux;
    objAux.cantElem=this->cantElem+vec2.cantElem;
    return objAux;
}

VectorEnteros VectorEnteros::operator +(const int num){
    int vectorAux[this->cantElem + 1];
    memcpy(&vectorAux[0], this->vec, this->cantElem*TAM_INT);
    memcpy(&vectorAux[this->cantElem], &num, 1);
    return VectorEnteros(vectorAux,this->cantElem+1);
}

VectorEnteros& VectorEnteros::operator =(const VectorEnteros& vec2){

    int* vecAux = new int[vec2.cantElem];
    memcpy(vecAux,vec2.vec,vec2.cantElem*TAM_INT);
    delete [] this->vec;
    this->vec = vecAux;
    this->cantElem = vec2.cantElem;
    return *this;
    
}

ostream& operator <<(ostream& os,const VectorEnteros& vec){
    unsigned i;
    os << '[';
    for(i=0;i<vec.cantElem-1;i++){
        os << (*(vec.vec+i))<<", ";
    }
    os << (*(vec.vec+i))<<"]";
    return os;
}
