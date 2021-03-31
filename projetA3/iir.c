#include "iir.h"       // --> Directives du pré processeur
#include "fichiers.h"  //




//  -------------------------------------------- //
//  | Projet: Oxymetre de pouls                | //
//  | Auteurs: PRALAIN Léopold - GURVAN ROUET  | //
//  | Date de creation: 29/03/2021             | // 
//  | Fonction : iirTest                       | //
//  | Role: fonction test du filtre iir        | //
//  -------------------------------------------- //

absorp iirTest(char* filename){
    FILE* data = initFichier(filename); // initialisation du fichier
	int etat = 0; // intialisation de la var etat
	absorp valeurSignal, myAbsorp = {0}; // initalisation des var valeurSignal et myabsorp de type absorp
	param_iir myIIR = {0}; // initialisation de my iIR de type param_iir


	while( etat != EOF){ // tant que etat n'est pas EOF (End of File), on continue le programme 

		valeurSignal = lireFichier(data, &etat); //on lis le fichier et on stock les valeur dans valeurSignal
		if (etat != EOF){ // permet de ne pas lire la dernière ligne
			myAbsorp = iir(valeurSignal, &myIIR); // on test la fonction iir qui nous permet d'appliquer le filtre iir
			printf("%.0f,%.0f,%.0f,%.0f \n", myAbsorp.acr, myAbsorp.dcr, myAbsorp.acir, myAbsorp.dcir); // on affiche les valeur ( commenter si vous ne voulez plus afficher)
		}
	}
	finFichier(data);// on ferme le fichier une fois le EOF atteinds

	return myAbsorp; //on retourne myAbsorp
}






//  -------------------------------------------- //
//  | Projet: Oxymetre de pouls                | //
//  | Auteurs: PRALAIN Léopold - GURVAN ROUET  | //
//  | Date de creation: 29/03/2021             | // 
//  | Fonction : iir                           | //
//  | Role: fonction permettant d'apliquer     | //
//  | un filtre iir à un jeu de données        | //
//  -------------------------------------------- //

absorp iir(absorp valeurSignal, param_iir* myIIR){

	absorp myAbsorp = valeurSignal;// on initialise les valeurs de Valeurs signal à uyne var myAbsorp


	//on applique les fonctions mathématiques suivante:
	// y(n) = x[n] - x[n-1] + alpha * y[n-1]

	myAbsorp.acir = (float)(valeurSignal.acir - (myIIR->precedenteValeurSignale.acir) + ALPHA * (myIIR->precedenteValeurFiltree.acir));
	myAbsorp.acr = (float)(valeurSignal.acr - (myIIR->precedenteValeurSignale.acr) + ALPHA * (myIIR->precedenteValeurFiltree.acr));


	myIIR->precedenteValeurSignale = valeurSignal; // voir define.h
	myIIR->precedenteValeurFiltree = myAbsorp;

	return myAbsorp;
}
