#include "iir.h"
#include "fichiers.h"

void init_iir(param_iir* myIRR){
	myIIR->alpha
}
absorp iir(absorp valeurSignal, param_iir* myIRR){

	absorp myAbsorp = valeurSignal;

	myAbsorp.acir = valeurSignal.acir - (myIIR->precedenteValeurSignale.acir) + (myIIR->alpha) * (myIIR->precedenteValeurFiltree.acir);
	myAbsorp.acr = valeurSignal.acr - (myIIR->precedenteValeurSignale.acr) + (myIIR->alpha) * (myIIR->precedenteValeurFiltree.acr);




	myIIR->precedenteValeurSignale = valeurSignal;
	myIIR->precedenteValeurFiltrees = myAbsorp;

	return myAbsorp;
}
