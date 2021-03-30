#include "affichage.h"


void affichage(oxy myOxy){

	FILE* data = NULL;
	FILE* verrou = NULL;



  if( access( ".verrouData", F_OK ) != -1 ){ // On teste l'existance de .verrouData
  	// Fichier existe
  	printf(".verrouData existe");
  }else{
  // Fichier n'existe pas
  	verrou = fopen(".verrouData","w"); // Création du fichier .verrouData
  	data = fopen("Data.txt","w+"); // On ouvre Data.txt
		fprintf(data, "%d\n%d", myOxy.spo2, myOxy.pouls);
  	fclose(data);
		fclose(verrou);
  	remove(".verrouData"); // On supprime le fichier .verrouData
  }
}
