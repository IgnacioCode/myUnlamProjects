#include "Alumno.h"

Alumno::Alumno(const Cadena& dni,const Cadena& nombre, const Cadena& apellido, const Fecha& fechaNacimiento, char sexo,const Cadena& curso,const int cantMatAprob,const float promedio)
: Persona(dni,nombre,apellido,fechaNacimiento,sexo),cantMatAprob(cantMatAprob),promedio(promedio),curso(curso){
    
}
