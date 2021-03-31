#include <stdio.h>
#include "fichiers.h"
#include "lecture.h"
#include "fir.h"
#include "iir.h"
#include "mesure.h"
#include "affichage.h"
#include "define.h"
#include <unistd.h>



void integrationTest(char* filename)
{
  int etat = 0, passage_zero = 0 ,i =0;
  float compteur_periode = 0, memoire = 0;
  float *minMax = malloc(4*sizeof(float));
  
  absorp myAbsorp ={0};
  absorp vartemp = {0};
  absorp tab[51] = {0};
  oxy myOxy = {0};
  param_iir myIIR = {0};

  FILE* myFile = initFichier(filename);


  do{

    
    minMax[i] = 1;
    i ++;

  }while (i < 4);


  do{
       vartemp = lireFichier(myFile, &etat);
      //vartemp = lecture(myFile, &etat);
    if ( etat != EOF)
    {
   
      myAbsorp = fir(vartemp, tab);
      myAbsorp = iir(myAbsorp, &myIIR);
      myOxy = mesure(&myAbsorp, myOxy, &memoire, minMax, &passage_zero, &compteur_periode);
      affichage(myOxy);

    }    
  }
  while ( etat != EOF);
  free(minMax);
  finFichier(myFile);
}
