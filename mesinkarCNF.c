/* File: mesinkar.c */
/* Implementasi Mesin Karakter */

#include "mesinkarCNF.h"
#include <stdio.h>

char CC;
boolean EOP;

static FILE * CNF;
static int retval;

void STARTCNF() {
/* Mesin siap dioperasikan. Pita disiapkan untuk dibaca.
   Karakter pertama yang ada pada pita posisinya adalah pada jendela.
   I.S. : sembarang
   F.S. : CC adalah karakter pertama pada pita. Jika CC != MARK maka EOP akan padam (false).
          Jika CC = MARK maka EOP akan menyala (true) */

	/* Algoritma */
	CNF = fopen("CNF.txt","r");
	ADVCNF();
}

void ADVCNF() {
/* Pita dimajukan satu karakter. 
   I.S. : Karakter pada jendela = 
          CC, CC != MARK
   F.S. : CC adalah karakter berikutnya dari CC yang lama, 
          CC mungkin = MARK.
		  Jika  CC = MARK maka EOP akan menyala (true) */

	/* Algoritma */
	retval = fscanf(CNF,"%c",&CC);
  if (retval == EOF) {
    CC='\0';
    fclose(CNF);
  }
}
