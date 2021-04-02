#include <stdio.h>      //      
#include "fichiers.h"   //
#include "lecture.h"    //
#include "fir.h"        //
#include "iir.h"        // ----> Directives du pré-processeur
#include "mesure.h"     //
#include "affichage.h"  //
#include "define.h"     //
#include <unistd.h>     //


//  -------------------------------------------- //
//  | Projet: Oxymetre de pouls                | //
//  | Auteurs: PRALAIN Léopold - GURVAN ROUET  | //
//  | Date de creation: 29/03/2021             | // 
//  | Fonction : integrationTest               | //
//  | Role: fonction réalisant l’intégration   | //
//  | de toutes les fonctions précédentes.     | //
//  -------------------------------------------- //

void integrationTest(char* filename)
{

  int etat = 0, passage_zero = 0 ,i =0;   //
  float  memoire = 0;// --> déclaration et initialisation de toutes les vars demandé dans nos fonctions
  float *minMax = malloc(8*sizeof(float));//
  float *compteur_periodeCon = malloc(4*sizeof(float));//
  
  absorp myAbsorp ={0};
  absorp vartemp = {0};
  absorp tab[51] = {0};
  oxy myOxy = {0};
  param_iir myIIR = {0};

  FILE* myFile = initFichier(filename); // initialisation du fichier 


  do{// on initialise le min et le max à 1 pour éviter les erreurs

    
    minMax[i] = 1;
    i ++;

  }while (i < 8);
  compteur_periodeCon[0] = 0, compteur_periodeCon[1] = 0, compteur_periodeCon[2] = 1, compteur_periodeCon[3] = 0;

  do{
       vartemp = lireFichier(myFile, &etat);// vartemp lis en get les valeurs de fichier 
      //vartemp = lecture(myFile, &etat);
    if ( etat != EOF) // si l'etat est différent de End Of file le programme continue 
    {
   
      myAbsorp = fir(vartemp, tab); // on passe nos valeurs dans le filtre fir 
      myAbsorp = iir(myAbsorp, &myIIR); // une fois filtré on les passe dans le filtre iir
      myOxy = mesure(&myAbsorp, myOxy, &memoire, minMax, &passage_zero, compteur_periodeCon); // enfin on aplique mesure pour relever le spo2 et le pouls
      affichage(myOxy);// et on affiche enfin dans data.txt 

    }    
  }
  while ( etat != EOF);
  free(minMax);
  free(compteur_periodeCon); // en fin de programme on libère l'espace alloué par le malloc
  finFichier(myFile);// on ferme le fichier
}
