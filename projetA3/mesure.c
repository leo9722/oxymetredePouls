#include "mesure.h"
#include "fichiers.h"

oxy mesure(absorp* myAbsorp, oxy myOxy, float* memoire, float *minMax, int* passage_zero, float* compteur_periode){


	float rsir = 0, spo2 = 0, pouls = 0,vppACR = 0, vppACIR = 0;

	float acr = myAbsorp->acr, acir = myAbsorp->acir;
	
	
	int i;
	


	// recherche du min et du max

	if( acir < minMax[0]){
		minMax[0] =  acir;
	}else if (acir > minMax[1]){
		minMax[1]= acir;
	}

	if(acr < minMax[2]){
		minMax[2]=  acr;
	}else if (acr> minMax[3]){
		minMax[3] = acr;
	}

	
	
	// calcul des vpp

	if (*passage_zero < 2){

		(*compteur_periode) += 0.002;
		//printf("%0.3f\n", *compteur_periode );
		if ((acr * (*memoire)) <0 ){
		//if ((myAbsorp->acr > 0 && memoire[0] > 0) || (myAbsorp->acr > 0 && memoire[0] < 0)){
			//printf("TEST\n");
			(*passage_zero)++;
		}
		
		//printf ("%d\n", *passage_zero);
	}else{

		//printf("POULLLLOOOUUUUUUUUUUUU\n");
		//calcul du pouls
		
		//printf("PERIode %0.4f\n", *compteur_periode);
		pouls = 60 * (1/(*compteur_periode));
		//printf("Pouls%0.4f\n", pouls);
		//calcul vpp
		vppACIR = minMax[1] - minMax[0];
		vppACR = minMax[3] - minMax[2];

		//calcul de rsir et spo2
		rsir = (vppACR/myAbsorp->dcr)/(vppACIR/myAbsorp->dcir);

		//printf("RSIR : %0.3f\n", rsir);
		if (rsir > 1){
			spo2 = -35.41 * rsir + 120.394;

		}else if(rsir <= 1){
			spo2 = -25 * rsir + 110;
		}

		//printf("SPO2 : %0.3f\n", spo2);
		//affectation des valeurs obtenues

		myOxy.spo2 = (int)spo2;
		myOxy.pouls = (int)pouls;

		printf("RSPO2 ::%d\n", myOxy.spo2);
		printf("RPOULS ::%d\n", myOxy.pouls);
		


		for ( i = 0; i < 4; i++){
			minMax[i] = 0;
		}

		*passage_zero = 0;

		*compteur_periode = 0;	
	}
		//printf("%0.3f | ", *memoire);
		//printf("ACR : %f :", acr);

	*memoire = acr;
	//memoire[0] = acr;


	//printf("%0.3f \n", *memoire);
	

	return myOxy;
}






oxy mesureTest(char* filename){
  FILE* data = initFichier(filename);
	int etat = 0, passage_zero = 0;
	float compteur_periode = 0, memoire = 0;
	absorp myAbsorp;
	oxy myOxy = {0};
	float *minMax = malloc(4*sizeof(float));
	//loat *memoire = malloc(1*sizeof(float));
	
	
	int i =0;
	do{

		
		minMax[i] = 1;
		i ++;

	}while (i < 4);

	while( etat != EOF){

		myAbsorp = lireFichier(data, &etat);
		
		if (etat != EOF){
			myOxy = mesure(&myAbsorp, myOxy, &memoire, minMax, &passage_zero, &compteur_periode);
			//printf("SP02 : %d, POULS : %d\n", myOxy.spo2, myOxy.pouls);
			


		}

	}

	finFichier(data);
	free(minMax);

	return myOxy;

	
	//free(memoire);
}


