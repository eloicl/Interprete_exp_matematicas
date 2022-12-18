%{
#include <stdio.h>
#include <stdlib.h>
#include "abb1.h"
#include "lex.yy.h"
#include "definiciones.h"
#include <math.h>
#include "tablaSimbolos.h"

void help();
extern int yylex();
void yyerror(char* s);
%}

%union{
    double num;
    char* cad;
    tipoelem* elem;
}


%token <num> NUM
%token <elem> VA FNCT FNCT2
%token <cad> FICHERO

%type <num> exp
%type <num> asign
%type <num> fnct

%token MAS_IGUAL
%token MENOS_IGUAL
%token MULT_IGUAL
%token DIV_IGUAL

%token VARIABLES
%token TABLA
%token HELP
%token LEER
%token CLEAR

%right '='
%left '-' '+' MAS_IGUAL MENOS_IGUAL
%left '*' '/' '%' DIV_IGUAL MULT_IGUAL
%left '>' '<'
%left NEG
%right '^'

%%
input: /* vacio */
| input line
;
line:
'\n'
| asign '\n' { printf("\n>>"); }
| asign ';''\n' { printf ("\t%.10g\n>>", $1); }



| exp '\n' { printf("\n>>"); }
| exp ';''\n' { printf ("\t%.10g\n>>", $1); }

| FNCT2 '\n'{ $1->data.fnc2();printf("\n>>");}
| LEER FICHERO {printf("EJECUCIÓN FICHERO:\n");abrirFichero($2);}
| error '\n' { printf("\n>>"); }
;

asign:
VA '=' exp { 
          if($1->tipo!=CONST){ $$ = $3;$1->data.val = $3; $1->tipo=VAR;}
          else {printf("No se puede asignar valor a una constante.\n>>");$$=$1->data.val;}
}

|VA MAS_IGUAL exp { if ($1->tipo==VAR){
                      $$ = $1->data.val+$3; $1->data.val += $3; $1->tipo=VAR;}
                    else if($1->tipo==CONST){printf("No se puede asignar valor a una constante.\n>>");$$=$1->data.val;}
                    else{
                            eliminar_variable_ErrorSintactico($1->lexema);
                            printf("ERROR SINTACTICO: variable no definida.\n>>");
                          }
                    
                          }
|VA MENOS_IGUAL exp { if ($1->tipo==VAR){
                          $$ = $1->data.val-$3; $1->data.val -= $3; $1->tipo=VAR;}
                      else if($1->tipo==CONST){printf("No se puede asignar valor a una constante.\n>>");$$=$1->data.val;}
                      else{
                              eliminar_variable_ErrorSintactico($1->lexema);
                              printf("ERROR SINTACTICO: variable no definida.\n>>");
                            }}
|VA MULT_IGUAL exp { if ($1->tipo==VAR){
                          $$ = $1->data.val*$3; $1->data.val *= $3; $1->tipo=VAR;}
                    else if($1->tipo==CONST){printf("No se puede asignar valor a una constante.\n>>");$$=$1->data.val;}
                    else{
                            eliminar_variable_ErrorSintactico($1->lexema);
                            printf("ERROR SINTACTICO: variable no definida.\n>>");
                          }}
|VA DIV_IGUAL exp { if ($1->tipo==VAR){
                        $$ = $1->data.val/$3; $1->data.val /= $3; $1->tipo=VAR;}
                    else if($1->tipo==CONST){printf("No se puede asignar valor a una constante.\n>>");$$=$1->data.val;}
                    else{
                            eliminar_variable_ErrorSintactico($1->lexema);
                            printf("ERROR SINTACTICO: variable no definida.\n>>");
                          }}

fnct:
FNCT '(' exp ')' { $$ = $1->data.fnc($3); }
| FNCT '('')' { $$ = $1->data.fnc(); }
|FNCT '(' exp ',' exp ')' { $$ = $1->data.fnc($3,$5); }

exp: NUM { $$ = $1; }
|fnct
| VA { 
        if ($1->tipo==VAR || $1->tipo==CONST ){
            $$ = $1->data.val;
            }
        else{
          eliminar_variable_ErrorSintactico($1->lexema);
          printf("ERROR SINTACTICO: variable no definida.\n>>");
        }
}
| exp '+' exp { $$ = $1 + $3; }
| exp '-' exp { $$ = $1 - $3; }
| exp '*' exp { $$ = $1 * $3; }
| exp '/' exp { $$ = $1 / $3; }
| '-' exp %prec NEG { $$ = -$2; }
| exp '^' exp { $$ = pow ($1, $3); }
| '(' exp ')' { $$ = $2; }
;
%%
void yyerror(char* s){
  printf (">ERROR -> %s <\n", s);
}
