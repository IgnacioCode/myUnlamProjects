#include "libros.h"


booleano verificaISBN(char* codigo){

    int i,leyoImpar=0;
    int sumaImpares=0;
    int sumaPares=0;

    char* charAct = codigo;

    for(i=0;i<17;i++){
        if(!leyoImpar && esLetra(*charAct)){
            sumaImpares+=charToInt(*charAct);
            leyoImpar=1;
        }
        if(leyoImpar && esLetra(*charAct)){
            sumaPares+=charToInt(*charAct);
            leyoImpar=0;
        }
        charAct++;
    }

    sumaPares*=3;

    return ((sumaImpares+sumaPares)%10) == 0;
}

booleano esLetra(char c){
    return ((c>=65 && c<=90) || (c>=97 && c<=122) )? (VERDADERO):(FALSO);
}

void creaArchivoStock(){

    Libro misLibros[3]={
        {"978-11-748-5698-3",7},
        {"978-38-600-5281-5",12},
        {"978-96-684-4030-4",5}
    };

    FILE* pf = fopen("archivoStockLibros.dat","wb");

    fwrite(misLibros,sizeof(Libro),3,pf);

    fclose(pf);

}

int comparaISBN(const char* c1,const char* c2){

    int i,comp;
    for(i=0;i<17;i++){
        comp = charToInt(*(c1+i)) - charToInt(*(c2+i));
        if(comp>0){
            return 1;
        }
        else if(comp < 0){
            return -1;
        }

    }

    return 0;
}
