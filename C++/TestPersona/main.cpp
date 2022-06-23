#include <iostream>
#include "..\Persona\Persona.h"
#include "..\Cadena\include\Cadena.h"
#include "..\Persona\PersonaExc.h"
#include "..\Persona\PersonaBuilder.h"

using namespace std;

int main(){

    
    PersonaBuilder builder;

    try{
        builder
            .setDNI("X12345678")
            .setNombre("Juan")
            .setApellido("Perez")
            .setFechaNacimiento(Fecha(1,1,2020))
            .setSexo('M');
    }
    catch(PersonaExc& e){
        cout << e.getMensaje() << endl;
        return 1;
    }

    Persona persona = builder.build();

    cout << "DNI: " << persona.getDNI() << endl;

    return 0;
}
