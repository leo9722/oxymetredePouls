#include "mesure.h"
#include "fichiers.h"
#include <unistd.h>

oxy mesure(absorp* myAbsorp, oxy myOxy, float* memoire, float *minMax, int* passage_zero, float* compteur_periodeCon){

	float acr = myAbsorp->acr, acir = myAbsorp->acir, dcr = myAbsorp->dcr, dcir = myAbsorp->dcir, rsir = 0, spo2 = 0, pouls = 0,vppACR = 0, vppACIR = 0;
	int i;
	
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

		(compteur_periodeCon[0]) += 0.002;

		if ((acr * (*memoire)) <0 ){
			(*passage_zero)++;
		}

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

		(compteur_periodeCon[1]) += 0.002;
		
		if ((acr * (*memoire)) <0 ){
			(*passage_zero)++;
		}

		if(*passage_zero == 4){
			compteur_periodeCon[2] = 0;
		}

	}else if (((*passage_zero == 2) || (*passage_zero == 4)) && compteur_periodeCon[2] == 0){
		
		float periode = compteur_periodeCon[0] + compteur_periodeCon[1];
		pouls = 60 * (1/(periode/2));

		vppACIR = minMax[3] - minMax[2];
		vppACR = minMax[1] - minMax[0];

		//calcul de rsir et spo2
		rsir = (vppACR/dcr)/(vppACIR/dcir);

		//printf("RSIR : %0.3f\n", rsir);
		if (rsir > 1){
			spo2 = -35.41 * rsir + 120.394;

		}else if(rsir <= 1){
			spo2 = -25 * rsir + 110;
		}

		myOxy.spo2 = (int)spo2;
		myOxy.pouls = (int)pouls;

		printf("SPO2 ::%d\n", myOxy.spo2);
		printf("POULS ::%d\n", myOxy.pouls);
		
		for ( i = 0; i < 4; i++){
			minMax[i] = minMax[i+4];
			minMax[i+4] = 0;
		}

		*passage_zero = 0;

		if (compteur_periodeCon[3] == 0){
		
		compteur_periodeCon[0] = 0;
		compteur_periodeCon[3] = 1;

		}else if (compteur_periodeCon[3] == 1){
			compteur_periodeCon[1] = compteur_periodeCon[0];
			compteur_periodeCon[0] = 0;

		}
	}

	*memoire = acr;
	return myOxy;
}

oxy mesureTest(char* filename){

  	FILE* data = initFichier(filename);
	int etat = 0, passage_zero = 0;
	float memoire = 0;
	absorp myAbsorp;
	oxy myOxy = {0};
	float *minMax = malloc(8*sizeof(float));
	float *compteur_periodeCon = malloc(4*sizeof(float));
	
	int i =0;
	do{
		minMax[i] = 1;
		i ++;
	}while (i < 8);

	compteur_periodeCon[0] = 0, compteur_periodeCon[1] = 0, compteur_periodeCon[2] = 1, compteur_periodeCon[3] = 0;
	

	while( etat != EOF){

		myAbsorp = lireFichier(data, &etat);
		
		if (etat != EOF){
			myOxy = mesure(&myAbsorp, myOxy, &memoire, minMax, &passage_zero, compteur_periodeCon);
		}
	}

	finFichier(data);
	free(minMax);
	free(compteur_periodeCon);

	return myOxy;
}
 