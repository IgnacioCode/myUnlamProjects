#include "Medicion.h"
#include <string.h>
#include "unidadExc.h"

#define ERROR_UNIDAD 2

Medicion::Medicion(){
    medicion = 0;
    unidad = new char[1];
    unidad[0] = '\0';
}
Medicion::Medicion(const float medicion,const char* unidad){
    this->medicion = medicion;
    this->unidad = new char[strlen(unidad)];
    strcpy(this->unidad,unidad);
    //this->unidad = (char*)unidad;
}
Medicion::~Medicion(){
    delete [] unidad;
}

Medicion Medicion::operator -(Medicion& med2){
    if(strcmp(this->unidad,med2.unidad)==0){
        return Medicion(this->medicion-med2.medicion,this->unidad);
    }
    else{
        throw unidadExc(ERROR_UNIDAD);
    }

}

Medicion operator +(float num,Medicion& med2){
    Medicion retorno = Medicion(num+med2.getMedicion(),med2.getUnidad());
    return retorno;
}

ostream& operator <<(ostream& os,const Medicion& med){
    os << med.getMedicion() << med.getUnidad();
    return os;
}

float Medicion::getMedicion()const{
    return this->medicion;
}
char* Medicion::getUnidad()const{
    return this->unidad;
}
