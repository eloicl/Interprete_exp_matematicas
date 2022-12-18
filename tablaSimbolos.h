#ifndef TS_H
#define TS_H
#include "abb1.h"

//Redefinimos el tipo con un nombre adecuado al contexto
typedef abb tablaSimbolos; 
//Función para eliminar una variable tras un error sintáctico en su declaración
void eliminar_variable_ErrorSintactico(char* l);
//Función para reservar memoria e inicializar la tabla
void inicializarTabla();
//Función para destruir la tabla, liberando su memoria
void destruirTabla();
//Función a exportar que permitirá al analizador preguntar acerca de un lexema
tipoelem* estaEnTabla (char * lex);
//Función para imprimir la tabla de símbolos
void ImprimirTabla();
void ImprimirVar();
#endif	
