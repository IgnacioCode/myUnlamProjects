#include "Archivos.h"


int MostrarMenu()
{
    int opcion;

    system("cls");

    printf("(1) Minimo elemento\n");
    printf("(2) Promedio de posiciones pares\n");
    printf("(3) Mostrar inverso\n");
    printf("(4) Salir\n");

    printf("\nIngrese una opcion: ");

    scanf("%d", &opcion);

    while(opcion<1 || opcion>4)
    {
        system("cls");

        printf("Opcion Invalida\n\n");

        printf("(1) Minimo elemento\n");
        printf("(2) Promedio de posiciones pares\n");
        printf("(3) Mostrar inverso\n");
        printf("(4) Salir\n");

        printf("\nIngrese una opcion: ");

        scanf("%d", &opcion);
    }

    return opcion;

}

int LlenarVector(float* vec, int cantElem)
{
    float* i;
    float leido;

    for(i=vec; i-vec<cantElem; i++)
    {
        printf("Elemento %d: ", 1+i-vec);
        scanf("%f", &leido);
        if(!leido)
        {
            return i-vec;
        }
        *i = leido;
    }
    return cantElem;
}

int Minimo(float* vec, int cantElem)
{
    float menor = *vec;
    int posicionMenor = 0;
    float* i;

    for(i=vec; i-vec<cantElem; i++)
    {
        if(*i<menor)
        {
            menor=*i;
            posicionMenor = i-vec;
        }
    }
    return posicionMenor;
}

float promedioPosPares(float* vec, int cantElem)
{
    float* i;
    float suma;

    for(i=vec; i-vec<cantElem; i++)
    {
        if((i-vec)%2==0)
        {
            suma+=*i;
        }
    }
    return suma/(cantElem/2);
}

void mostrarInverso(float* vec, int cantElem)
{
    float* i =vec;
    i+=cantElem-1;
    printf("{ ");
    for(i; i-vec>=0; i--)
    {
        printf("%.2f, ", *i);
    }
    printf("}");
}

void GuardarEnArchivo(FILE* archivo, float* vec, int cantElem)
{
    float* i=vec;

    for(i; i-vec<cantElem; i++)
    {
        fprintf(archivo, "%.2f\n", *i);
    }

}

void mergeArchivoProductos(char* archivoBase,const char* archivoCambios){

    //Asumimos que ambos archivos estan ordenados por codigo
    char nombreTemp[101];
    FILE* archBase = fopen(archivoBase,"rb");
    FILE* archCambios = fopen(archivoCambios,"rb");

    if(archBase==NULL || archCambios==NULL){
        printf("No se pudo abrir un archivo");
        return;
    }

    cambiaExtension(archivoBase,nombreTemp,"tmp");
    FILE* archBaseTemp = fopen(nombreTemp,"wb");

    if(archBaseTemp==NULL){
        printf("No se pudo abrir el archivo temporal");
        return;
    }

    Producto producto,nuevoProducto,movimiento;
    int comparacion;

    fread(&producto,sizeof(Producto),1,archBase);
    fread(&movimiento,sizeof(Producto),1,archCambios);

    while(!feof(archBase) && !feof(archCambios)){

        comparacion=producto.codigo-movimiento.codigo;

        if(comparacion==0){ //Actualiza Producto

            producto.cantidad+=movimiento.cantidad;
            fread(&movimiento,sizeof(Producto),1,archCambios);
        }
        else if(comparacion<0){ //Producto sin movimientos restantes

            fwrite(&producto,sizeof(Producto),1,archBaseTemp);
            fread(&producto,sizeof(Producto),1,archBase);
        }
        else{   //Producto Nuevo

            nuevoProducto=movimiento;
            fread(&movimiento,sizeof(Producto),1,archCambios);

            while(nuevoProducto.codigo==movimiento.codigo && feof(archCambios)){
                nuevoProducto.cantidad+=movimiento.cantidad;
            }

            fwrite(&nuevoProducto,sizeof(Producto),1,archBaseTemp);

        }

    }

    while(!feof(archBase)){
        fwrite(&producto,sizeof(Producto),1,archBaseTemp);
        fread(&producto,sizeof(Producto),1,archBase);
    }

    while(!feof(archCambios)){
        nuevoProducto=movimiento;
        fread(&movimiento,sizeof(Producto),1,archCambios);

        while(nuevoProducto.codigo==movimiento.codigo && !feof(archCambios)){
            nuevoProducto.cantidad+=movimiento.cantidad;
        }

        fwrite(&nuevoProducto,sizeof(Producto),1,archBaseTemp);
    }

    fclose(archBase);
    fclose(archCambios);
    fclose(archBaseTemp);

    remove(archivoBase);
    rename(nombreTemp,archivoBase);

}

void creaProductos(const char* nombreArchivo){

    Producto productos[8]={
        {1,"Leche",5,2.3},
        {2,"Arroz",15,6},
        {3,"Lentejas",23,1.1},
        {4,"Coca Cola",7,4.3},
        {5,"Carne",9,3.145},
        {6,"Cebolla",1,1.5},
        {7,"Oreos",26,3},
        {8,"Galletitas de Agua",50,0.95}

    };

    FILE* archivo = fopen(nombreArchivo,"wb");

    fwrite(productos,sizeof(Producto),8,archivo);

    fclose(archivo);
}

void creaMovimientos(const char* nombreArchivo){

    Producto movimientos[10]={
        {1,"Leche",3,2.3},
        {2,"Arroz",-10,6},
        //{2,"Arroz",-6,1.1},
        {4,"Coca Cola",7,4.3},
        {5,"Carne",31,3.145},
        {6,"Cebolla",-5,1.5},
        {7,"Oreos",10,3},
        //{7,"Oreos",-9,3},
        {8,"Galletitas de Agua",-26,0.95},
        {9,"Manaos Cola",13,2.4}

    };

    FILE* archivo = fopen(nombreArchivo,"wb");

    fwrite(movimientos,sizeof(Producto),10,archivo);

    fclose(archivo);
}

void cambiaExtension(char* nombreOriginal,char* nombreCambiado, const char* nuevaExtension){

    strcpy(nombreCambiado,nombreOriginal);
    char* punto = strrchr(nombreCambiado,'.');

    if(!punto)
        return;

    strcpy(punto+1,nuevaExtension);

}

void muestraProductos(const char* nombreArchivo){

    Producto miProducto;
    FILE* pf=fopen(nombreArchivo,"rb");
    fread(&miProducto,sizeof(Producto),1,pf);

    while(!feof(pf)){
        printf("%3d %-20s %3d\n",miProducto.codigo,miProducto.descripcion,miProducto.cantidad);
        fread(&miProducto,sizeof(Producto),1,pf);
    }

    fclose(pf);
}

void interseccionArchivosProductos(char* archivo1,char* archivo2,char* archivoResultante){

    FILE* arch1 = fopen(archivo1,"rb");
    FILE* arch2 = fopen(archivo2,"rb");
    FILE* archRes = fopen(archivoResultante,"wb");

    if(arch1==NULL || arch2==NULL || archRes==NULL){
        printf("No se pudo abrir un archivo");
        return;
    }

    Producto producto1,producto2;

    while(!feof(arch1) && !feof(arch2)){

        fread(&producto1,sizeof(Producto),1,arch1);
        fread(&producto2,sizeof(Producto),1,arch2);

        if(producto1.codigo==producto2.codigo){ //Codigos iguales, escribo en archivo
            producto1.cantidad+=producto2.cantidad;
            fwrite(&producto1,sizeof(Producto),1,archRes);
        }
        else if(producto1.codigo<producto2.codigo){ //Avanzo el archivo 1

            fread(&producto1,sizeof(Producto),1,arch1);

        }
        else if(producto1.codigo>producto2.codigo){ //Avanzo el archivo 2

            fread(&producto2,sizeof(Producto),1,arch2);
        }

    }

    fclose(arch1);
    fclose(arch2);
    fclose(archRes);

}

///Funciones Ejercicio 12

int ingresoAlumnos(char nombresApellidos[][101][31],float notas[][101]){

    int i=0,j;
    char deseo='Y';

    while(deseo!= 'N' && i<100){
        printf("Ingrese el Apellido del alumno: ");
        scanf("%s",&nombresApellidos[0][i][0]);

        printf("Ingrese el Nombre del alumno: ");
        scanf("%s",&nombresApellidos[1][i][0]);

        for(j=0;j<6;j++){
            printf("Ingrese la nota del parcial %d: ",j+1);
            fflush(stdin);
            scanf("%f",&notas[j][i]);
        }

       calculaPromedio(notas,i);

        fflush(stdin);
        printf("¿Desea ingresar otro alumno? [Y/N] ");
        scanf("%c",&deseo);
        deseo=toupper(deseo);
        printf("---------------------------------------\n");
        i++;

    }

    calculaPromedioGenerales(notas,i);

    return i;
}

void calculaPromedio(float notas[][101],int alumno){        ///Revisar calculo de promedios

    int i;

    notas[6][alumno]=0;

    for(i=0;i<6;i++){
        notas[6][alumno]+=notas[i][alumno];
    }
    notas[6][alumno]/=(float)i;

}

void imprimeResultados(FILE* archivo,char nombresApellidos[][101][31],float notas[][101],int cantAlumnos){

    int i;

    fprintf(archivo,"   Apellidos,Nombres                    P. 1  P. 2  P. 3  P. 4  P. 5  P. 6 - Promedio\n");
    fprintf(archivo,"   =================================== ===== ===== ===== ===== ===== ===== - ========\n");

    for(i=0;i<cantAlumnos;i++){
        fprintf(archivo,"%2d %-11s, %-22s %-5.2f %-5.2f %-5.2f %-5.2f %-5.2f %-5.2f - %-5.2f\n",i+1,nombresApellidos[0][i],nombresApellidos[1][i],notas[0][i],notas[1][i],notas[2][i],notas[3][i],notas[4][i],notas[5][i],notas[6][i]);
    }

    fprintf(archivo,"%2d Promedios generales                 %-5.2f %-5.2f %-5.2f %-5.2f %-5.2f %-5.2f - %-5.2f\n",i+1,notas[0][100],notas[1][100],notas[2][100],notas[3][100],notas[4][100],notas[5][100],notas[6][100]);


}

void calculaPromedioGenerales(float notas[][101],int cantAlumnos){  ///Tengo que verificar cual es la ultima fila segun cantALum

    int i,j;

    for(i=0;i<7;i++){
        notas[i][100]=0;
    }

    for(j=0;j<7;j++){
        for(i=0;i<cantAlumnos;i++){
             notas[j][100]+=notas[j][i];
        }
        notas[j][100]/=(float)cantAlumnos;
    }

}

void actualizaSueldos(FILE* archivoEstudiantes,FILE* archivoEmpleados,float porAumento){

    Empleado empleadoLeido;
    Estudiante estudianteLeido;

    fread(&empleadoLeido,sizeof(Empleado),1,archivoEmpleados);
    fread(&estudianteLeido,sizeof(Estudiante),1,archivoEstudiantes);
    
    while(!feof(archivoEmpleados) && !feof(archivoEstudiantes)){
        if(datosIguales(empleadoLeido,estudianteLeido)){
            if(estudianteLeido.promedio>7){
                empleadoLeido.sueldo*=(1+(porAumento/100));
                fseek(archivoEmpleados,-1*(sizeof(Empleado)),SEEK_CUR);
                fwrite(&empleadoLeido,sizeof(Empleado),1,archivoEmpleados);
            }

        }
        fread(&estudianteLeido,sizeof(Estudiante),1,archivoEstudiantes);
        fread(&empleadoLeido,sizeof(Empleado),1,archivoEmpleados);
    }

}

int datosIguales(Empleado emp,Estudiante est){

    return (emp.apellido==est.nombre && emp.dni==est.dni && emp.nombre==est.nombre);

}

int mostrarMenuPila(){

    short entrada;

    do{
        
        printf("1) Cargar otro dato en la Pila\n");
        printf("2) Ver el tope de la pila\n");
        printf("3) Sacar el tope de la pila\n");
        printf("4) Salir del menu\n");

         printf("Ingrese una opcion: ");

        scanf("%d",&entrada);

         
    }while(entrada>=1 && entrada<=4);

    return entrada;

}