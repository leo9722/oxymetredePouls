#include "iir.h"
#include "fichiers.h"

//void init_iir(param_iir* myIIR){

	//myIIR->precedenteValeurSignale.acir = 0;
	//myIIR->precedenteValeurFiltree.acr =0;
//}

absorp iirTest(char* filename){
    FILE* data = initFichier(filename);
	int etat = 0;
	absorp valeurSignal, myAbsorp = {0};
	param_iir myIIR = {0};


	while( etat != EOF){

		valeurSignal = lireFichier(data, &etat);
		if (etat != EOF){
			myAbsorp = iir(valeurSignal, &myIIR);
			printf("%.0f,%.0f,%.0f,%.0f \n", myAbsorp.acr, myAbsorp.dcr, myAbsorp.acir, myAbsorp.dcir);
		}
	}
	finFichier(data);

	return myAbsorp;
}




absorp iir(absorp valeurSignal, param_iir* myIIR){

	absorp myAbsorp = valeurSignal;

	myAbsorp.acir = (float)(valeurSignal.acir - (myIIR->precedenteValeurSignale.acir) + ALPHA * (myIIR->precedenteValeurFiltree.acir));
	myAbsorp.acr = (float)(valeurSignal.acr - (myIIR->precedenteValeurSignale.acr) + ALPHA * (myIIR->precedenteValeurFiltree.acr));


	myIIR->precedenteValeurSignale = valeurSignal;
	myIIR->precedenteValeurFiltree = myAbsorp;

	return myAbsorp;
}
