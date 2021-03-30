#include "iir.h"
#include "fichiers.h"

void init_iir(param_iir* myIIR){
	myIIR->alpha = 0.992;
	myIIR->precedenteValeurSignale.acir = 0;
	myIIR->precedenteValeurFiltree.acr =0;
}

absorp iir(absorp valeurSignal, param_iir* myIIR){

	absorp myAbsorp = valeurSignal;

	myAbsorp.acir = valeurSignal.acir - (myIIR->precedenteValeurSignale.acir) + (myIIR->alpha) * (myIIR->precedenteValeurFiltree.acir);
	myAbsorp.acr = valeurSignal.acr - (myIIR->precedenteValeurSignale.acr) + (myIIR->alpha) * (myIIR->precedenteValeurFiltree.acr);


	myIIR->precedenteValeurSignale = valeurSignal;
	myIIR->precedenteValeurFiltree = myAbsorp;

	return myAbsorp;
}
