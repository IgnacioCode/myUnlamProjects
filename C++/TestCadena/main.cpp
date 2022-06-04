#include <iostream>
#include "..\Cadena\include\Cadena.h"

using namespace std;

int main(){

    char linea[]="Hola como va";
    char linea2[]=", todo bien?";

    Cadena cad1(linea);
    Cadena cad2(linea2);
    Cadena cad3;

    cout << cad1+cad2;

    return 0;
}
