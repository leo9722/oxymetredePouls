// Includes 
#include "mesure.h"
#include "fichiers.h"
#include <unistd.h>


//  -------------------------------------------- //
//  | Projet: Oxymetre de pouls                | //
//  | Auteurs: PRALAIN Léopold - GURVAN ROUET  | //
//  | Date de creation: 29/03/2021             | // 
//  | Fonction : mesure                        | //
//  | Role: mesurer le spo2 et le pouls à      | //
//  | partir des données filtrées par iir      | //
//  -------------------------------------------- //

oxy mesure(absorp* myAbsorp, oxy myOxy, float* memoire, float *minMax, int* passage_zero, float* compteur_periodeCon){
	// Déclarations des variables
	float acr = myAbsorp->acr, acir = myAbsorp->acir, dcr = myAbsorp->dcr, dcir = myAbsorp->dcir, rsir = 0, spo2 = 0, pouls = 0,vppACR = 0, vppACIR = 0;
	int i;
	// Recherche du min et du max pour la première période
	if (*passage_zero < 2){

		if(acr < minMax[0]){
			minMax[0]=  acr;
		}else if (acr> minMax[1]){
			minMax[1] = acr;
		}

		if( acir < minMax[2]){
			minMax[2] =  acir;
		}else if (acir > minMax[3]){
			minMax[3]= acir;
		}
		// on incrémente le compteur de période de 0.002 seconde
		(compteur_periodeCon[0]) += 0.002; 
		// on regarde si on a un passage à zéro, et on incrémente le compteur si c'est le cas
		if ((acr * (*memoire)) <0 ){
			(*passage_zero)++;
		}
	// Recherche du min et du max pour la seconde période	
	}else if(*passage_zero >= 2 && *passage_zero < 4 && compteur_periodeCon[2] == 1){

		if(acr < minMax[4]){
			minMax[4]=  acr;
		}else if (acr> minMax[5]){
			minMax[5] = acr;
		}
		if( acir < minMax[6]){
			minMax[6] =  acir;
		}else if (acir > minMax[7]){
			minMax[7]= acir;
		}
		// on incrémente le compteur de période de 0.002 seconde
		(compteur_periodeCon[1]) += 0.002; 
		// on regarde si on a un passage à zéro, et on incrémente le compteur si c'est le cas
		if ((acr * (*memoire)) <0 ){
			(*passage_zero)++;
		}
		//au bout de 4 passage à zéro on passe la condition à 0, pour ne plus rentrer dans la condition 
		if(*passage_zero == 4){
			compteur_periodeCon[2] = 0;
		}
	//Calcul de SpO2 et du pouls une fois que la période est fini
	}else if (((*passage_zero == 2) || (*passage_zero == 4)) && compteur_periodeCon[2] == 0){
		//calcul du pouls
		float periode = compteur_periodeCon[0] + compteur_periodeCon[1];
		pouls = 60 * (1/(periode/2));
		myOxy.pouls = (int)pouls;
		//calcul des vpp et initialisation des min et des max
		if(compteur_periodeCon[3] == 0){
			compteur_periodeCon[3] = 1;
			vppACIR = minMax[3] - minMax[2];
			vppACR = minMax[1] - minMax[0];
			for ( i = 0; i < 4; i++){
				minMax[i] = 0; 
			}
		}else if(compteur_periodeCon[3] == 1){
			compteur_periodeCon[1] = compteur_periodeCon[0];				
			vppACIR = minMax[7] - minMax[6];
			vppACR = minMax[5] - minMax[4];
			for ( i = 0; i < 4; i++){
				minMax[i + 4] = minMax[i]; 
				minMax[i] = 0; 
			}
		}
		//calcul du rsir et du spo2
		rsir = (vppACR/dcr)/(vppACIR/dcir);

		if (rsir > 1){
			spo2 = -35.41 * rsir + 120.394;
		}else if(rsir <= 1){
			spo2 = -25 * rsir + 110;
		}

		myOxy.spo2 = (int)spo2;
		// printf("SPO2 ::%d\n", myOxy.spo2);
		// printf("POULS ::%d\n", myOxy.pouls);

		//on initialise les variables.
		*passage_zero = 0;
		compteur_periodeCon[0] = 0;
	}

	*memoire = acr; // on stocke le acr pour pouvoir déterminer le assage à zéro
	return myOxy;
}

//  -------------------------------------------- //
//  | Projet: Oxymetre de pouls                | //
//  | Auteurs: PRALAIN Léopold - GURVAN ROUET  | //
//  | Date de creation: 29/03/2021             | // 
//  | Fonction : mesureTest                    | //
//  | Role:  tester la fonction mesure afin    | //
//  | d'obtenir le spo2 et le pouls            | //
//  -------------------------------------------- //

oxy mesureTest(char* filename){

  	FILE* data = initFichier(filename);//initialisation du fichier
  	//déclaration des variables et des struct
	int etat = 0, passage_zero = 0;
	float memoire = 0;
	absorp myAbsorp;
	oxy myOxy = {0};
	//on aloue de la mémoire
	float *minMax = malloc(8*sizeof(float));
	float *compteur_periodeCon = malloc(4*sizeof(float));
	
	int i =0;
	// Initialisation des min et max pour éviter les erreurs
	do{
		minMax[i] = 1;
		i ++;
	}while (i < 8);

	compteur_periodeCon[0] = 0, compteur_periodeCon[1] = 0, compteur_periodeCon[2] = 1, compteur_periodeCon[3] = 0;
	

	while( etat != EOF){ // Tant que le fichier n'est pas à la fin

		myAbsorp = lireFichier(data, &etat);
		
		if (etat != EOF){
			myOxy = mesure(&myAbsorp, myOxy, &memoire, minMax, &passage_zero, compteur_periodeCon);
		}
	}

	finFichier(data);
	//On libère la mémoire allouée
	free(minMax);
	free(compteur_periodeCon);

	return myOxy;
}
 