#include "Fecha.h"

Fecha::Fecha(){

    this->diaRel=0;

}


Fecha::Fecha(int dia,int mes,int anio){



}

int Fecha::cantDiaMesAcum(int mes){
    static int diasAcum[12] = {0,31,59,90,120,151,181,212,243,273,304,334};

    return diasAcum[mes];
}