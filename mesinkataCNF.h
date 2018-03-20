/* File: mesinkata.h */
/* Definisi Mesin Kata: Model Akuisisi Versi I */

#ifndef __MESINKATACNF_H__
#define __MESINKATACNF_H__

#include "boolean.h"
#include "mesinkarCNF.h"
#include "mesinkata.h"

#define NMax 50
#define BLANKCNF1 ' '
#define BLANKCNF2 '|'
#define ENTER '\n'

/*typedef struct {
	char TabKata[NMax+1];  container penyimpan kata, indeks yang dipakai [1..NMax] 
    int Length;
} Kata;*/

/* State Mesin Kata */
extern boolean EndKataCNF;
extern Kata CKataCNF;

void IgnoreBlankCNF();
/* Mengabaikan satu atau beberapa BLANK
   I.S. : CC sembarang 
   F.S. : CC ≠ BLANK atau CC = MARK */

void IgnoreEnterCNF();

void STARTKATACNF();
/* I.S. : CC sembarang 
   F.S. : EndKataCNF = true, dan CC = MARK; 
          atau EndKataCNF = false, CKata adalah kata yang sudah diakuisisi,
          CC karakter pertama sesudah karakter terakhir kata */

void ADVKATACNF();
/* I.S. : CC adalah karakter pertama kata yang akan diakuisisi 
   F.S. : CKata adalah kata terakhir yang sudah diakuisisi, 
          CC adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika CC = MARK, EndKataCNF = true.		  
   Proses : Akuisisi kata menggunakan procedure SalinKataCNF */

void SalinKataCNF();
/* Mengakuisisi kata, menyimpan dalam CKata
   I.S. : CC adalah karakter pertama dari kata
   F.S. : CKata berisi kata yang sudah diakuisisi; 
          CC = BLANK atau CC = MARK; 
          CC adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi NMax, maka sisa kata "dipotong" */

/*void CopyKata(char S[100], Kata CKata);*/

#endif
