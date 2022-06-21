#ifndef COMUN_H_INCLUDED
#define COMUN_H_INCLUDED

typedef enum{
    FALSO,VERDADERO
}booleano;

#define MIN(X,Y) ((X)>(Y)? (Y):(X))
#define MAX(X,Y) ((X)>(Y)? (X):(Y))
#define ABS(X) ((X>0)? (X):(-X))

typedef int (*Cmp)(const void*,const void*);
typedef void (*ImpFunc)(const void*,const void*,const int);

#endif // COMUN_H_INCLUDED
