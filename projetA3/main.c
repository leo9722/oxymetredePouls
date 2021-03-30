#include <stdio.h>
#include "define.h"
#include "iir.h"
#include "fir.h"
#include "lecture.h"
#include "fichiers.h"
int main (){

  int etat =0;
   absorp myAbsorp;
  FILE* test = initFichier("record1_bin.dat");
  myAbsorp = lireFichier(test, &etat);
  while( etat != EOF){

   myAbsorp = lecture(test, &etat);
   printf("%.0f,%.0f,%.0f,%.0f \n", myAbsorp.acr, myAbsorp.acir, myAbsorp.dcr, myAbsorp.dcir);
  

  }
return 0;
}
