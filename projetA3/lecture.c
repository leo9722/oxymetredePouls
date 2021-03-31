#include "lecture.h"
#include "fichiers.h"
#include <string.h>



absorp lecture(FILE* file_pf,  int* file_state){




    absorp myAbsorp = {0};
    char  octet_recu = 0;
    int i =0; 
    char tram[21]; 

    if(file_pf == NULL) { 
        *file_state = EOF; 
    }
    else{
        for(i=0; i < 21; i++){ 
            octet_recu = fgetc(file_pf); 
            if(octet_recu == EOF){ 
                *file_state = EOF;
            }
            else{
                tram[i]= (octet_recu);
            }
        }
        

        //printf("%.0d,%.0d,%.0d,%.0d ", tram[0],tram[1], tram[2], tram[3]);
                                                                                                                                 
        myAbsorp.acr = (float)((tram[0]-48)*1000 + (tram[1]-48)*100 + (tram[2]-48) * 10 + (tram[3]-48));
        myAbsorp.dcr = (float)((tram[5]-48)*1000 + (tram[6]-48)*100 + (tram[7]-48) * 10 + tram[8]-48);
        myAbsorp.acir = (float)((tram[10]-48) *1000 + (tram[11]-48) * 100 + (tram[12]-48) * 10 +( tram[13]-48));
        myAbsorp.dcir = (float)(( tram[15] -48)*1000 + (tram[16]-48) * 100 + (tram[17]-48) * 10 +( tram[18]-48));

       // printf("%.0f,%.0f,%.0f,%.0f ", myAbsorp.acr, myAbsorp.acir, myAbsorp.dcr, myAbsorp.dcir);
        myAbsorp.acr -= 2048;
        myAbsorp.acir -= 2048;

        //printf("%.0f,%.0f,%.0f,%.0f \n ", myAbsorp.acr, myAbsorp.acir, myAbsorp.dcr, myAbsorp.dcir);

        }
   
	return myAbsorp; 
}
