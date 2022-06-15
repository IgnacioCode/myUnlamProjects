#include "Persona.h"
#include "PersonaExc.h"

Persona::Persona(){

}

Persona::Persona(const Cadena& dni,const Cadena& nombre, const Cadena& apellido, const Fecha& fechaNacimiento, char sexo){

    setDNI(dni);
    setNombre(nombre);
    setApellido(apellido);
    setFechaNacimiento(fechaNacimiento);
    setSexo(sexo);

}


const Cadena& Persona::getDNI()const{
    validarDNI(dni);
    return dni;
}
const Cadena& Persona::getNombre()const{
    return nombre;
}
const Cadena& Persona::getApellido()const{
    return apellido;
}
const Fecha& Persona::getFechaNacimiento()const{
    return fechaNacimiento;
}
const char Persona::getSexo()const{
    return sexo;
}

void Persona::setDNI(const Cadena& dni){
    this->dni = dni;
}

void Persona::setNombre(const Cadena& nombre){
    this->nombre = nombre;
}
void Persona::setApellido(const Cadena& apellido){
    this->apellido = apellido;
}
void Persona::setFechaNacimiento(const Fecha& fechaNacimiento){
    this->fechaNacimiento = fechaNacimiento;
}
void Persona::setSexo(char sexo){
    this->sexo = sexo;
}

bool Persona::validarDNI(Cadena dni){
    int longMax= 8;

    if(dni[0]=='M' || dni[0]=='F'){
        longMax++;
        //Validar que el resto de la cadena sea numerica
    }
    else{
        if(!dni.esEnteroPositivo()){
            throw PersonaExc("DNI Invalido: " + dni + "no es un numero");
        }
    }

    if(dni.longitud()>9){
        throw PersonaExc("DNI Invalido");
    }

    return true;
}
