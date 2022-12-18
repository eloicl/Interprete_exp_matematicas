
Desarrollo de un intérprete de expresiones matemáticas con entrada desde comandos o ficheros. Se utiliza para ello Bison y Flex.



Desde la carpeta con los archivos del código fuente


Generación del analizador mediante flex:
	
	flex codflex.l

Generación del analizador sitáctico mediante bison:

	 bison -d Sintac.y

Compilar:
		
	gcc abb1.c tablaSimbolos.c lex.yy.c Sintac.tab.c main.c -Wall -lm -o ejec

Ejecutar:
	En esa misma carpeta llamar al ejecutable generado (sin opciones, -h para ayuda o ruta de fichero con comandos a ejecutar)
	
	./ejec
	./ejec -h
	./ejec prueba.txt
