#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "abb1.h"
#include "tablaSimbolos.h"
#include "definiciones.h"
#include <math.h>
#include "funcs.h"

#define NUMCTES 2

tablaSimbolos tabla;
/*
struct init
{
char *fname;
double (*fnct)();
};

struct init arith_fncts[]
= {
{"sin", sin},
{"cos", cos},
{"atan", atan},
{"ln", log},
{"exp", exp},
{"sqrt", sqrt},
{0, 0}
};*/

//Función a exportar que permitirá al analizador preguntar acerca de un lexema
tipoelem* estaEnTabla (char * lex){
    //declaramos variable donde se guardará el resultado de la búsqueda
    tipoelem* elemento=NULL;
    //buscamos el nodo
    elemento=buscar_nodo(tabla,lex);
    //Comprobamos si ha cambiado o si sigue a su valor de inicialización
    if(elemento!=NULL){
        //existe el elemento, liberamos la memoria del lexema recién leído, ya que ya existe una copia en la tabla
        free(lex);
        return elemento;

    }
    else{
        //no existía el elemento, por lo que será una variable
        tipoelem e;
        e.lexema=lex;
        e.tipo=VARTEMP;
        e.data.val=0;
        //insertamos el tipoelem en la tabla
        elemento=insertar(&tabla,e);
        return elemento;
    }
}
//Función para reservar memoria e inicializar la tabla
void inicializarTabla(){
    int i=0,tam=0;
    //Inicializamos la estructura de la tabla, reservando memoria para esta
    crear(&tabla); 

    //Inserto constantes
    char nombresconstantes[NUMCTES][20]={"PI","E"};
    float valores[NUMCTES]={PI,E};
    tipoelem e;
    e.tipo=CONST;//Tipo
    for (i=0;i<NUMCTES;i++){
        //LEXEMA
        //Reservamos memoria dinámicamente
        tam=strlen(nombresconstantes[i]);
        e.lexema=malloc((tam+1)*sizeof(char));
        //Copiamos la cadena
        strcpy(e.lexema,nombresconstantes[i]);
        //Añadiendo el fin de cadena
        e.lexema[tam]='\0';

        //Valor
        e.data.val=valores[i];
        insertar(&tabla,e);
    }

    tam=0;
    //Inserto funciones matemáticas
    e.lexema=NULL;
    e.tipo=FUNC;
    e.data.val=0;
    for(i = 0; arith_fncts[i].fname != 0; i++){
        //LEXEMA
        //Reservamos memoria dinámicamente
        tam=strlen(arith_fncts[i].fname);
        e.lexema=malloc((tam+1)*sizeof(char));
        //Copiamos la cadena
        strcpy(e.lexema,arith_fncts[i].fname);
        //Añadiendo el fin de cadena
        e.lexema[tam]='\0';
        e.data.fnc=arith_fncts[i].fnc;
		insertar(&tabla,e);;
	}
    //Inserto funciones calculadora
    e.lexema=NULL;
    e.tipo=FUNC2;
    e.data.val=0;
    for(i = 0; arith_fncts2[i].fname != 0; i++){
        //LEXEMA
        //Reservamos memoria dinámicamente
        tam=strlen(arith_fncts2[i].fname);
        e.lexema=malloc((tam+1)*sizeof(char));
        //Copiamos la cadena
        strcpy(e.lexema,arith_fncts2[i].fname);
        //Añadiendo el fin de cadena
        e.lexema[tam]='\0';
        e.data.fnc2=arith_fncts2[i].fnc;
		insertar(&tabla,e);;
	}
}


//Eliminar variable si el comando de su declaración no fue válido
void eliminar_variable_ErrorSintactico(char* l){
    tipoelem e;
    e.lexema=l;
    suprimir(&tabla,e);
}




void ImprimirTablaRecursivo(tablaSimbolos t){
    tipoelem elem;
    //Mientras no sea vacío exploramos el árbol imprimiendo la información de cada nodo
    if(!es_vacio(t)){
        ImprimirTablaRecursivo(izq(t));//lamada recursiva
        leer(t,&elem);//lectura información nodo
        printf("%s:%d\n",elem.lexema,elem.tipo);
        ImprimirTablaRecursivo(der(t));//lamada recursiva
    }
}
//Función para imprimir la tabla de símbolos
void ImprimirTabla(){
    printf("--Entorno--\n");
    ImprimirTablaRecursivo(tabla);
}
//Función recursiva que imprime variables
void ImprimirVarRecursivo(tablaSimbolos t){
    tipoelem elem;
    //Mientras no sea vacío exploramos el árbol imprimiendo la información de cada nodo
    if(!es_vacio(t)){
        ImprimirVarRecursivo(izq(t));//lamada recursiva
        leer(t,&elem);//lectura información nodo
        if(elem.tipo==VAR) printf("%s:%lf\n",elem.lexema,elem.data.val);
        ImprimirVarRecursivo(der(t));//lamada recursiva
    }
}
//Función para imprimir variables
void ImprimirVar(){
    ImprimirVarRecursivo(tabla);
}
//Función para destruir la tabla, liberando su memoria
void destruirTabla(){
    destruir(&tabla);
}
