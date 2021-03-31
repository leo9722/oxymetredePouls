#include "lecture.h"         //-->    Directives du pré-processeur
#include "fichiers.h"        //
#include <string.h>          //


//----------------------------PARTIE POUR USB FTDI------------------------
//#include "ftd2xx.h"


// FT_HANDLE ftHandle;
// FT_STATUS ftStatus;
// DWORD BytesWritten;
// char TxBuffer[256]; // Contains data to write to device
// ftStatus = FT_Open(0, &ftHandle);
// if(ftStatus != FT_OK) {
//  FT_Open failed;
// return;
// }
// ftStatus = FT_Write(ftHandle, TxBuffer, sizeof(TxBuffer), &BytesWritten);
// if (ftStatus == FT_OK) {
//  FT_Write OK;
//  ftStatus = file_pf;
// }
// else {
//  FT_Write Failed;
// }

// FT_Close(ftHandle);
// ------------------------------------------------------------------------



//  -------------------------------------------- //
//  | Projet: Oxymetre de pouls                | //
//  | Auteurs: PRALAIN Léopold - GURVAN ROUET  | //
//  | Date de creation: 29/03/2021             | // 
//  | Fonction : lecture                       | //
//  | Role: fonction permettant de recupérer   | //
//  | des valeurs du  module  interface        | //
//  | capteur oxymètre                         | //
//  -------------------------------------------- //

absorp lecture(FILE* file_pf,  int* file_state){

    absorp myAbsorp = {0}; // intialisation d'une var absorp
    char  octet_recu = 0; // initialisation de la var octet reçu de type char à 0
    int i =0; //initialisation de la var i de type int à 0
    char tram[21]; // on creer un tableau de charcatère  qui nous permettra de sttocker la trame 
    // Le tableau à une taille de 21 car :
    // acr = 4 octets + acir = 4 octets + dcr = 4 octest + dcir = 4 octets  + 4 virgules sur 1 octet + LR et CR sur 1 octets chacunes
    // tram = 4 *4 +4 + 2 = 22

    if(file_pf != NULL) { //si on a des données reçu on poursuis le programme

        for(i=0; i < 21; i++){  //on creer une boucle de la taille de notre tableau
            octet_recu = fgetc(file_pf); //on recupère chaques char que l'on stoque dans notre octet reçu
            if(octet_recu == EOF){ // si celui -ci est le EOF on change l'état à EOF
                *file_state = EOF;
                return myAbsorp;
            }
            else{
                    tram[i]= (octet_recu);//sinon on stock l'octet_reçu dans la tram à la position i
            }
        }
        

        //printf("%.0d,%.0d,%.0d,%.0d ", tram[0],tram[1], tram[2], tram[3]); // décomenter pour voir la trame



        //on applique -48 pour passer de ASCII à un nombre entier. et selon la place de notre octet on le multiplie par 1000-100-10-1
                                                                                                                                 
        myAbsorp.acr = (float)((tram[0]-48)*1000 + (tram[1]-48)*100 + (tram[2]-48) * 10 + (tram[3]-48));
        myAbsorp.dcr = (float)((tram[5]-48)*1000 + (tram[6]-48)*100 + (tram[7]-48) * 10 + tram[8]-48);
        myAbsorp.acir = (float)((tram[10]-48) *1000 + (tram[11]-48) * 100 + (tram[12]-48) * 10 +( tram[13]-48));
        myAbsorp.dcir = (float)(( tram[15] -48)*1000 + (tram[16]-48) * 100 + (tram[17]-48) * 10 +( tram[18]-48));

       // printf("%.0f,%.0f,%.0f,%.0f ", myAbsorp.acr, myAbsorp.acir, myAbsorp.dcr, myAbsorp.dcir); // Décommenter pour voir les vals

        myAbsorp.acr -= 2048; //on centre acr et  acir en 0 car avant elles évoluaient entre 0 et 4096
        myAbsorp.acir -= 2048;


    }

    else{
        
        *file_state = EOF;
    }
   
    return myAbsorp; // on retourne une val de type absorp
}
