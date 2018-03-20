#include "mesinkataCNF.h"
#include "stdio.h"
#include <string.h>
#include "mesinkarCNF.h"


boolean EndKataCNF;
Kata CKataCNF;



void IgnoreBlankCNF()	{
/* Mengabaikan satu atau beberapa BLANK
   I.S. : CC sembarang 
   F.S. : CC ≠ BLANK atau CC = MARK */
    while (((CC == BLANKCNF1) || (CC == BLANKCNF2)) && (CC != MARK)) {
        ADVCNF();
    }
    if (CC == MARK) {
      EndKataCNF = true;
    }
}

void IgnoreEnterCNF() {
  ADVCNF();
  if (CC == MARK) {
      EndKataCNF = true;
  }
}

void STARTKATACNF()	{
/* I.S. : CC sembarang 
   F.S. : EndKataCNF = true, dan CC = MARK; 
          atau EndKataCNF = false, CKataCNF adalah kata yang sudah diakuisisi,
          CC karakter pertama sesudah karakter terakhir kata */
    STARTCNF();
    IgnoreBlankCNF();
    if ((CC == MARK)) {
        EndKataCNF = true;
    } else {
        EndKataCNF = false;
        SalinKataCNF();

    }
}

void ADVKATACNF()	{
/* I.S. : CC adalah karakter pertama kata yang akan diakuisisi 
   F.S. : CKataCNF adalah kata terakhir yang sudah diakuisisi, 
          CC adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika CC = MARK, EndKataCNF = true.		  
   Proses : Akuisisi kata menggunakan procedure SalinKataCNF */
    IgnoreBlankCNF();
    if ((CC == MARK)) {
        EndKataCNF = true;
    } else  {
        SalinKataCNF();
    }
}

void SalinKataCNF()	{
/* Mengakuisisi kata, menyimpan dalam CKataCNF
   I.S. : CC adalah karakter pertama dari kata
   F.S. : CKataCNF berisi kata yang sudah diakuisisi; 
          CC = BLANK atau CC = MARK; 
          CC adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi NMax, maka sisa kata "dipotong" */
	int i = 0;
	memset(CKataCNF.TabKata,0,sizeof(CKataCNF.TabKata));
  while ((CC!=MARK)&&(CC!=ENTER)&&(CC!=BLANKCNF1)&&(CC!=BLANKCNF2)&&i<=NMax) {
		CKataCNF.TabKata[i]=CC;
		ADVCNF();
		i++;
	}
	CKataCNF.Length=i-1;
}



