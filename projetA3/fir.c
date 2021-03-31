#include "fir.h"       // -->
#include "fichiers.h"  //-->    Directives du pré-processeur



//  -------------------------------------------- //
//  | Projet: Oxymetre de pouls                | //
//  | Auteurs: PRALAIN Léopold - GURVAN ROUET  | //
//  | Date de creation: 29/03/2021             | // 
//  | Fonction : firTest                       | //
//  | Role: fonction test du filtre fir        | //
//  -------------------------------------------- //

absorp firTest(char* filename){
	absorp	myAbsorp;//declaration d'une variable myabsorp de type absorp
    absorp vartemp;// var temp nous sers à parcourir notre fichier et permet de ne pas récupérer une ligne en trop 

	int etat = 0; // initialisation de l'état à 0
	FILE* fic = initFichier(filename); //on apèle la fonction init fichier pour initialiser notre fichier 
	
	absorp tab[51] = {0}; //on initialise un tableau de type absorp qui va nous permettre de stocker les futur valeur de acr et acir

	while (etat != EOF){// tant qu'on est pas arrivé à la fin de notre fichier ( caractérisé par EOF = End of File) on poursuit le programme
        vartemp = lireFichier(fic, &etat);// var temp parcour le fichier ligne à ligne et stoque les valeurs
            if ( etat != EOF){ // cette condition nous permet de ne pas avoir une valeur en plus à la fin du fichier 
		      //printf("%.0f,%.0f,%.0f,%.0f :", myAbsorp.acr, myAbsorp.acir, myAbsorp.dcr, myAbsorp.dcir);// Décommenter cette ligne pour pouvoir voir les résultat
		      myAbsorp = fir(vartemp,tab);//on appelle la fonction fir qui nous permet alors de stocker les resultat d'un filtrage de donné par le filtre fir et ainsi d'avoir de nouvelles valeurs		
		    }	
	}
	
	finFichier(fic); //à la fin de la lecture du fichier on ferme celui-ci

    //printf("%.0f,%.0f,%.0f,%.0f\n", myAbsorp.acr, myAbsorp.acir, myAbsorp.dcr, myAbsorp.dcir); //décommenter pour avoir les dernière valeurs
	return myAbsorp; // on retourne un tableau de type absorp ayant subis le filtre fir
}



//  -------------------------------------------- //
//  | Projet: Oxymetre de pouls                | //
//  | Auteurs: PRALAIN Léopold - GURVAN ROUET  | //
//  | Date de creation: 29/03/2021             | // 
//  | Fonction : fir                           | //
//  | Role: fonction permettant d'apliquer     | //
//  | un filtre fir à un jeu de données        | //
//  -------------------------------------------- //
absorp fir(absorp myAbsorp, absorp *tab){
	float FIR_TAPS[51]={ //déclaration d'un tableau de flottants de 51 echantillons de valeurs précédentes
    1.4774946e-019,
    1.6465231e-004,
    3.8503956e-004,
    7.0848037e-004,
    1.1840522e-003,
    1.8598621e-003,
    2.7802151e-003,
    3.9828263e-003,
    5.4962252e-003,
    7.3374938e-003,
    9.5104679e-003,
    1.2004510e-002,
    1.4793934e-002,
    1.7838135e-002,
    2.1082435e-002,
    2.4459630e-002,
    2.7892178e-002,
    3.1294938e-002,
    3.4578348e-002,
    3.7651889e-002,
    4.0427695e-002,
    4.2824111e-002,
    4.4769071e-002,
    4.6203098e-002,
    4.7081811e-002,
    4.7377805e-002,
    4.7081811e-002,
    4.6203098e-002,
    4.4769071e-002,
    4.2824111e-002,
    4.0427695e-002,
    3.7651889e-002,
    3.4578348e-002,
    3.1294938e-002,
    2.7892178e-002,
    2.4459630e-002,
    2.1082435e-002,
    1.7838135e-002,
    1.4793934e-002,
    1.2004510e-002,
    9.5104679e-003,
    7.3374938e-003,
    5.4962252e-003,
    3.9828263e-003,
    2.7802151e-003,
    1.8598621e-003,
    1.1840522e-003,
    7.0848037e-004,
    3.8503956e-004,
    1.6465231e-004,
    1.4774946e-019
};


   int i,j;     //initialisation des entiers i et j
   float fir_acr = 0; // intialisations des flottant fir_acr ert fir_acir
   float fir_acir = 0;
 

//Mise en place d'un buffer circulaire décallant à droite
//Un buffer circulaire est une structure de données utilisant un buffer de taille fixe et dont le début et la fin sont considérés comme connectés. 
//Les buffers circulaires sont souvent utilisés pour gérer des flux de données ou pour implémenter un comportement de type FIFO. 


   for (i = 0; i < 50; i ++){ //utilisation d'une boucle ppour faire décaller le tableau sur les 51 vals
			tab[50 -i] = tab[49-i]; // permet de faire le décallage à droite on supprime la plus ancienne  des vals
        

		}
		tab[0]= myAbsorp; //permet de mettre la nouvelle valeur


    for (j =0 ; j < 51 ; j ++){// on aplique le filtrre sur les 51 vals de acr et acir uniquement 
    	fir_acr += FIR_TAPS[j] * tab[j].acr;
    	fir_acir += FIR_TAPS[j] * tab[j].acir;
    	 
    	
    }
   	// printf("MABSORP : %f :",myAbsorp.acr);
   	// printf("%f \n",myAbsorp.acir);

   	// printf(" FIR : %.0f : ", fir_acr );
   	// printf("%.0f\n", fir_acir );

    myAbsorp.acr = fir_acr;     //on stoque les nouvelles val de acr et ecir deans myabsorp et pas dcr et dcir car on filtre simplement acr et acir
    myAbsorp.acir = fir_acir;





return myAbsorp; //on retourne notre val de type absorp
}

