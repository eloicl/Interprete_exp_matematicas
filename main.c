#include <stdlib.h>
#include <stdio.h>
#include "lex.yy.h"
#include "abb1.h"
#include "tablaSimbolos.h"
#include "definiciones.h"
#include "Sintac.tab.h"
#include <string.h>



int main(int argc, char *argv[]){
    /*printf("                                                                                                                                                                           \n
                                                                                                                          dddddddd                                                     \n
        CCCCCCCCCCCCC                  lllllll                                       lllllll                              d::::::d                                                     \n
     CCC::::::::::::C                  l:::::l                                       l:::::l                              d::::::d                                                     \n
   CC:::::::::::::::C                  l:::::l                                       l:::::l                              d::::::d                                                     \n
  C:::::CCCCCCCC::::C                  l:::::l                                       l:::::l                              d:::::d                                                      \n
 C:::::C       CCCCCC  aaaaaaaaaaaaa    l::::l     ccccccccccccccccuuuuuu    uuuuuu   l::::l   aaaaaaaaaaaaa      ddddddddd:::::d    ooooooooooo   rrrrr   rrrrrrrrr   aaaaaaaaaaaaa   \n
C:::::C                a::::::::::::a   l::::l   cc:::::::::::::::cu::::u    u::::u   l::::l   a::::::::::::a   dd::::::::::::::d  oo:::::::::::oo r::::rrr:::::::::r  a::::::::::::a  \n
C:::::C                aaaaaaaaa:::::a  l::::l  c:::::::::::::::::cu::::u    u::::u   l::::l   aaaaaaaaa:::::a d::::::::::::::::d o:::::::::::::::or:::::::::::::::::r aaaaaaaaa:::::a \n
C:::::C                         a::::a  l::::l c:::::::cccccc:::::cu::::u    u::::u   l::::l            a::::ad:::::::ddddd:::::d o:::::ooooo:::::orr::::::rrrrr::::::r         a::::a \n
C:::::C                  aaaaaaa:::::a  l::::l c::::::c     cccccccu::::u    u::::u   l::::l     aaaaaaa:::::ad::::::d    d:::::d o::::o     o::::o r:::::r     r:::::r  aaaaaaa:::::a \n
C:::::C                aa::::::::::::a  l::::l c:::::c             u::::u    u::::u   l::::l   aa::::::::::::ad:::::d     d:::::d o::::o     o::::o r:::::r     rrrrrrraa::::::::::::a \n
C:::::C               a::::aaaa::::::a  l::::l c:::::c             u::::u    u::::u   l::::l  a::::aaaa::::::ad:::::d     d:::::d o::::o     o::::o r:::::r           a::::aaaa::::::a \n
 C:::::C       CCCCCCa::::a    a:::::a  l::::l c::::::c     cccccccu:::::uuuu:::::u   l::::l a::::a    a:::::ad:::::d     d:::::d o::::o     o::::o r:::::r          a::::a    a:::::a \n
  C:::::CCCCCCCC::::Ca::::a    a:::::a l::::::lc:::::::cccccc:::::cu:::::::::::::::uul::::::la::::a    a:::::ad::::::ddddd::::::ddo:::::ooooo:::::o r:::::r          a::::a    a:::::a \n
   CC:::::::::::::::Ca:::::aaaa::::::a l::::::l c:::::::::::::::::c u:::::::::::::::ul::::::la:::::aaaa::::::a d:::::::::::::::::do:::::::::::::::o r:::::r          a:::::aaaa::::::a \n
     CCC::::::::::::C a::::::::::aa:::al::::::l  cc:::::::::::::::c  uu::::::::uu:::ul::::::l a::::::::::aa:::a d:::::::::ddd::::d oo:::::::::::oo  r:::::r           a::::::::::aa:::a\n
        CCCCCCCCCCCCC  aaaaaaaaaa  aaaallllllll    cccccccccccccccc    uuuuuuuu  uuuullllllll  aaaaaaaaaa  aaaa  ddddddddd   ddddd   ooooooooooo    rrrrrrr            aaaaaaaaaa  aaaa\n
                                                                                                                                                                                       \n
                                                                                                                                                                                       \n
                                                                                                                                                                                       \n
                                                                                                                                                                                       \n
");*/
    //Comprobamos si se pasan parámetros de entrada
    if(argc==2){
        FILE * h;
        if(strcmp("-h",argv[1])==0){ //AYUDA
            h=fopen("HELP.txt","r");
            if(h==NULL) printf("Error abriendo el archivo de ayuda.\n>>");
            else{
                fclose(h);
                system("cat HELP.txt");
            }
        }
        
        else{//Invocamos función para abrir fichero y establecer entrada al fichero
            abrirFichero(argv[1]);
        }
    }
    
    //Inicializamos tabla
    inicializarTabla();

    printf("\n\n>>");


    //Invocamos analizador sintáctico de bison
    yyparse();


    //Liberamos a memoria da tabla
    destruirTabla();
    
}