#include <stdio.h>
#include "define.h"
#include "iir.h"
#include "fir.h"

int main (){

  // int etat =0;
  absorp myAbsorp;
  // oxy myOxy;
  // param_fir myFIR = {0};
  // param_iir myIIR = {0};
  // param_mesure myMes = {0};
  // FILE* myFile = initFichier("record1.dat");
  // do{
  //   myAbsorp = lireFichier(myFile, &etat);
  //   //myAbsorp = fir(myAbsorp, &myFIR);
  //   myAbsorp = iir(myAbsorp, &myIIR);
  //   //myOxy = mesure(myAbsorp, &myMes);
  //   affichage(myOxy);
  // }while ( etat != EOF);
  // finFichier(myFile);
  // return EXIT_SUCCESS;
  myAbsorp = firTest("record1.dat");

 return 0;

}
