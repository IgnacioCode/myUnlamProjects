#ifndef COMUN_H_INCLUDED
#define COMUN_H_INCLUDED

typedef enum{

    FALSO, VERDADERO

}booleano;

#define MIN(X,Y) ((X)>(Y)? (Y):(X))
#define MAX(X,Y) ((X)>(Y)? (X):(Y))
#define ABS(X) ((X>0)? (X):(-X))

#define TODO_OK 0
#define NO_MEMORY 1
#define DUPLICADO 2
#define VACIA 3

typedef int (*Cmp)(const void*,const void*);
typedef int (*Accion)(const void*,const void*);
typedef int (*Actualizar)(void*,const void*);

#endif // VECTORES_H_INCLUDED
