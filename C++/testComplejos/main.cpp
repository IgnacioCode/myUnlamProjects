#include <iostream>

#include "..\Complejos\include\Complejos.h"

using namespace std;

int main(){

    Complejos z1(2,1);
    Complejos z2(-1,3);
    Complejos z3;


    cout << (z1+z2) <<endl;
    cin >> z3;
    cout << z3.modulo();

}
