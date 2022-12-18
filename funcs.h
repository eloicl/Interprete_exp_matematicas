#include <math.h>
#include "tablaSimbolos.h"
#include "Sintac.tab.h"
#include "lex.yy.h"
//FUNCIONES MATH.H
struct init
	{
		char *fname;
		double (*fnc)();
	};
struct init arith_fncts[]
	= { 
		{"sin", sin},
		{"cos", cos},
		{"tan", tan},
		{"asin", asin},
		{"acos", acos},
		{"atan", atan},
		{"sinh", sinh},
		{"cosh", cosh},
		{"tanh", tanh},
		{"log10", log10},
		{"ln", log},
		{"exp", exp},
		{"sqrt", sqrt},
		{"ceil", ceil},
		{"floor", floor},
		{"fabs", fabs},
		{"pow", pow},
		{0, 0}
	};
//FUNCIONES VOID CALCULADORA
struct init2
{
	char *fname;
	void (*fnc)();
};
struct init2 arith_fncts2[]
	= { 
		{"clear", limpiartabla},
		{"tabla", ImprimirTabla},
		{"entorno", ImprimirVar},
		{"ayuda", help},
		{0, 0}
	};