#include "mesinkata.h"
#include "stdio.h"
#include <string.h>
#include "mesinkar.h"


boolean EndKata;
Kata CKata;



void IgnoreBlank()	{
/* Mengabaikan satu atau beberapa BLANK
   I.S. : CC sembarang 
   F.S. : CC ≠ BLANK atau CC = MARK */
    while (((CC == BLANK) || (CC == TAB) || (CC == ENTER)) && (CC != MARK)) {
        ADV();
    } 
}

void STARTKATA()	{
/* I.S. : CC sembarang 
   F.S. : EndKata = true, dan CC = MARK; 
          atau EndKata = false, CKata adalah kata yang sudah diakuisisi,
          CC karakter pertama sesudah karakter terakhir kata */
    START();
    IgnoreBlank();
    if ((CC == MARK)) {
        EndKata = true;
    } else {
        EndKata = false;
        SalinKata();

    }
}

void ADVKATA()	{
/* I.S. : CC adalah karakter pertama kata yang akan diakuisisi 
   F.S. : CKata adalah kata terakhir yang sudah diakuisisi, 
          CC adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika CC = MARK, EndKata = true.		  
   Proses : Akuisisi kata menggunakan procedure SalinKata */
    IgnoreBlank();
    if ((CC == MARK)) {
        EndKata = true;
    } else  {
        SalinKata();
    }
}

boolean ischr(){
  return ((CC == ';')||(CC == '.')||(CC ==':')||(CC=='=')||(CC=='>')||(CC=='<')||(CC==',')||(CC=='+')||(CC=='-')||(CC=='*')||(CC=='(')||(CC==')'));
}

void SalinKata()	{
/* Mengakuisisi kata, menyimpan dalam CKata
   I.S. : CC adalah karakter pertama dari kata
   F.S. : CKata berisi kata yang sudah diakuisisi; 
          CC = BLANK atau CC = MARK; 
          CC adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi NMax, maka sisa kata "dipotong" */
	int i = 0;
	memset(CKata.TabKata,0,sizeof(CKata.TabKata));
  if (ischr()){
      CKata.TabKata[i]=CC;
      ADV();
      i++;
      if ((CC=='=')&&((CKata.TabKata[0]==':')||(CKata.TabKata[0]=='>')||(CKata.TabKata[0]=='<')))  {
        CKata.TabKata[i]=CC;
        ADV();
        i++;
      } else if ((CC=='>')&&(CKata.TabKata[0]=='<'))  {
        CKata.TabKata[i]=CC;
        ADV();
        i++;
      } else if ((CC=='.')&&(CKata.TabKata[0]=='.'))  {
        CKata.TabKata[i]=CC;
        ADV();
        i++;
      }
  } else {
    while ((CC!=MARK)&&(CC!=ENTER)&&(CC!=BLANK)&&(CC!=TAB)&&i<=NMax &&!ischr()){
  		CKata.TabKata[i]=CC;
  		ADV();
  		i++;
  	}
  }
	CKata.Length=i;
}
