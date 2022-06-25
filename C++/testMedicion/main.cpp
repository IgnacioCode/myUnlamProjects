#include <iostream>
#include "..\Mediciones\Medicion.h"
#include "..\Mediciones\unidadExc.h"

using namespace std;

int main(){

    Medicion m1mv(100.0,"Mv");
    Medicion m2mv(20.0,"Mv");
    Medicion m4amp(3.0,"Amp");
    Medicion m3mv = m1mv-m2mv;

    cout << "Resultado 1: "<< 180+m3mv <<endl;

    try{
        cout << m3mv-m2mv  << endl;
    }catch(unidadExc& e){
        cout << "El programa termino con el error: " << e.getValorError() << endl;
        return 2;
    }

    return 0;
}
