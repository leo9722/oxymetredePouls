#include "fir.h"
#include "fichiers.h"

absorp firTest(char* filename){
	absorp	myAbsorp;
    absorp vartemp;

	int etat = 0;
	FILE* fic = initFichier(filename);
	
	absorp tab[51] = {0};

	while (etat != EOF){

		
		vartemp = lireFichier(fic, &etat);

        if ( etat != EOF){
		printf("%.0f,%.0f,%.0f,%.0f :", myAbsorp.acr, myAbsorp.acir, myAbsorp.dcr, myAbsorp.dcir);
		myAbsorp = fir(vartemp,tab);
			
			
		
    }

		
	}
	
	finFichier(fic);

    //printf("%.0f,%.0f,%.0f,%.0f\n", myAbsorp.acr, myAbsorp.acir, myAbsorp.dcr, myAbsorp.dcir);
	return myAbsorp;
}

absorp fir(absorp myAbsorp, absorp *tab){
	float FIR_TAPS[51]={
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


   int i,j;
   float fir_acr = 0;
   float fir_acir = 0;
 



   for (i = 0; i < 50; i ++){
			tab[50 -i] = tab[49-i];

		}
		tab[0]= myAbsorp;


    for (j =0 ; j < 51 ; j ++){
    	fir_acr += FIR_TAPS[j] * tab[j].acr;
    	fir_acir += FIR_TAPS[j] * tab[j].acir;
    	 
    	
    }
   	// printf("MABSORP : %f :",myAbsorp.acr);
   	// printf("%f \n",myAbsorp.acir);

   	// printf(" FIR : %.0f : ", fir_acr );
   	// printf("%.0f\n", fir_acir );

    myAbsorp.acr = fir_acr;
    myAbsorp.acir = fir_acir;





return myAbsorp;
}

