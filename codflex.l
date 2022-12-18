%{
#include <stdlib.h>
#include <stdio.h>
#include "abb1.h"
#include "definiciones.h"
#include "tablaSimbolos.h"
#include "errores.h"
#include "Sintac.tab.h"
#include <string.h>

void cerrarFichero();

%}
%option nounput
%option noinput
%option noyywrap
%option yylineno

ESPACIO                       [ ]
SEPARADORES                     (\t|\r|{ESPACIO})+

NEWLINE                       \n
UNICODE_CHAR                  .
UNICODE_LETTER                [A-Za-z]
UNICODE_DIGIT                 [0-9]

LETTER                        {UNICODE_LETTER}|_
DECIMAL_DIGIT                 [0-9]

SEMICOLON                     ;

IDENTIFIER                    {LETTER}({LETTER}|{UNICODE_DIGIT})*

OPERADORES                    [+*/%^<>=!(),.-]|{SEMICOLON}
MAS_IGUAL                     \+=
MENOS_IGUAL                   \-=
MULT_IGUAL                    \*=
DIV_IGUAL                     \/=

DECIMALS                      {DECIMAL_DIGIT}+
INT                           {DECIMALS}
DECIMAL_EXPONENT              [eE][+-]?{DECIMALS}
FLOAT                         {DECIMALS}\.({DECIMALS})?({DECIMAL_EXPONENT})?|{DECIMALS}{DECIMAL_EXPONENT}|\.{DECIMALS}({DECIMAL_EXPONENT})?
NUM                           {INT}|{FLOAT}

FICHERO                       ({LETTER}|{UNICODE_DIGIT})+\.({LETTER}|{UNICODE_DIGIT})+

%x lect
%%

{SEPARADORES}


"salir"                         {yyterminate();}
"abrir"                         { return (LEER); }

{NEWLINE}                     return((int)*yytext);

{NUM}                         {yylval.num=atof(yytext);
                                return (NUM);}

{IDENTIFIER}                  {char* lexem;
                                lexem=malloc((strlen(yytext)+1)*sizeof(char));
                                strcpy(lexem,yytext);
                                lexem[strlen(yytext)]='\0';
                                yylval.elem=estaEnTabla(lexem);
                                if(yylval.elem->tipo==FUNC) return(FNCT);
                                else if(yylval.elem->tipo==FUNC2) return(FNCT2);
                                else return (VA);
                                }

{FICHERO}                 {char* lexem;

                                lexem=malloc((strlen(yytext)+1)*sizeof(char));
                                strcpy(lexem,yytext);
                                lexem[strlen(yytext)]='\0';
                                yylval.cad=lexem;
                                printf("%s\n",yylval.cad);
                                BEGIN(INITIAL);
                                return (FICHERO);
                                }




{MAS_IGUAL}                   return(MAS_IGUAL);
{MENOS_IGUAL}                 return(MENOS_IGUAL);
{MULT_IGUAL}                  return(MULT_IGUAL);
{DIV_IGUAL}                   return(DIV_IGUAL);
{OPERADORES}                  return((int)*yytext);

.                             printf("ERROR LEXICO\n");
<<EOF>>                       {cerrarFichero(); yyrestart(stdin);}
%%


void abrirFichero(char * nombreFichero){printf("%s\n",nombreFichero);
    yyin=fopen(nombreFichero,"r");
    if(yyin==NULL){
        printf("Error al abrir el fichero\n");
        yyin=stdin;
        yyrestart(stdin);
        BEGIN(INITIAL);
    }
}
void help(){
  FILE * h;
  h=fopen("HELP.txt","r");
  if(h==NULL) printf("Error abriendo el archivo de ayuda.\n");
  else{
    fclose(h);
    system("cat HELP.txt");
  }
}
void cerrarFichero(){
    fclose(yyin);
    yyin=stdin;
}
void limpiartabla(){
    destruirTabla();inicializarTabla();printf("..Entorno restablecido..\n\n");
}