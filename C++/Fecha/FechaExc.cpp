#include "FechaExc.h"

FechaExc::FechaExc(const Cadena& mensaje){
    this->mensaje = mensaje;
}

const Cadena& FechaExc::getMensaje()const{
    return this->mensaje;
}
