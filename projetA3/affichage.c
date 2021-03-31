#include "affichage.h" // Directives du pré processeur


//  -------------------------------------------- //
//  | Projet: Oxymetre de pouls                | //
//  | Auteurs: PRALAIN Léopold - GURVAN ROUET  | //
//  | Date de creation: 29/03/2021             | // 
//  | Fonction : affichageTest                 | //
//  | Role: fonction testant l'affichage des   | //
//  | valeurs de Spo2 et pouls dans Data.txt   | //
//  -------------------------------------------- //

void affichageTest(){

  oxy myOxy;// on declare une var de type oxy
  myOxy.pouls=50;//on initialise les var de oxy et de pouls
  myOxy.spo2=100;
  affichage(myOxy);// on appelle la fonction affichage pour tester cette fonction
  
}



void affichage(oxy myOxy){

  FILE* data = NULL; // on met data à NULL
  FILE* verrou = NULL; // et verrou à NULL

//Pourquoi avoir un verrou Data :
//il n’est pas possible de lire  et  écrire  en  même  temps  dans  un fichier. 
//C’est ce qu’on appelle l’exclusion mutuelle. Ce mécanisme de verrou est mis en œuvrele fichier .
//verrouData La présence du fichier verrou indique qu’une opération   de   lecture   ou   écriture   est   en  cours   sur   le fichier   de   données correspondant. 
//L’absence de verrou autorise la lecture ou l’écriture

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
