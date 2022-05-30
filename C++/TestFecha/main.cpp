#include <iostream>
#include "..\Fecha\include\Fecha.h"

using namespace std;

int main(){

    cout << "Hello world!" << endl;

    Fecha miFecha(1,1,2000);
    Fecha miFecha2(13,5,2002);

    int dif=fecha1.difEnDias(miFecha2);

    Fecha fSuma=miFecha.sumarDias(35);

    return 0;
}
