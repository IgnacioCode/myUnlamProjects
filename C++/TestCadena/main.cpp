#include <iostream>
#include <fstream>
#include "..\Cadena\include\Cadena.h"

using namespace std;

int main(){


    Cadena cad1="Hola";
    Cadena cad2="mundo";
    Cadena cad3=cad2 + "!!!!";

    cout << cad1 + ' ' + cad2 + "!!!!" + ' '+ 2022 << endl;

    cin >> cad3;

    cout << cad3;

    fstream archivo("archivo.txt",ios::out);    //Asi se crea un objeto archivo

    archivo << "!!!" + ' ' + cad2 + "!!!!" + ' '+ 2022 << endl;

    archivo.close();

    return 0;
}
