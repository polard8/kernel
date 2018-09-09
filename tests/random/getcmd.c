#include <stdio.h>
#include <stdlib.h>


enum {BP,BR,CE,FI,FO,HE,IND,LS,NF,PL,RM,SP,TI,UL,UNKNOWN};

int getcmd (buf)
char *buf;

/* Decodifica o tipo de comando */

{
  char cmd[3];
  cmd[0] = buf[0];
  cmd[1] = buf[1];
  cmd[2] = '\0';
 
  if (!strcmp(cmd,"fi"))
    return(FI);
  else if (!strcmp(cmd,"nf"))
    return(NF);
  else if (!strcmp(cmd,"br"))
    return(BR);
  else if (!strcmp(cmd,"ls"))
    return(LS);
  else if (!strcmp(cmd,"bp"))
    return(BP);
  else if (!strcmp(cmd,"sp"))
    return(SP);
  else if (!strcmp(cmd,"in"))
    return(IND);
  else if (!strcmp(cmd,"rm"))
    return(RM);
  else if (!strcmp(cmd,"ti"))
    return(TI);
  else if (!strcmp(cmd,"ce"))
    return(CE);
  else if (!strcmp(cmd,"ul"))
    return(UL);
  else if (!strcmp(cmd,"he"))
    return(HE);
  else if (!strcmp(cmd,"fo"))
    return(FO);
  else if (!strcmp(cmd,"pl"))
    return(PL);
  else
    return(UNKNOWN);
}


 main(argc, argv)
int argc;
char *argv[];

{
   if(argc <= 1)
    {
     printf("Erro numero de argumentos\n");
     exit(1);
    } 
  printf("%d", getcmd(argv[1]));

}
