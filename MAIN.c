#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mesinkata.h"
#include "mesinkar.h"
#include "boolean.h"
#include "mesinkataCNF.h"
#include "mesinkarCNF.h"


int LENGTH, NProduction;
Kata Table[100][100], CNF[100][100], strInput[100], var, temp;
char kombinasi[200][100];


////////////////////////////////////
/*INPUT STRING DARI FILE EKSTERNAL*/
////////////////////////////////////
void Scan_String()	{
	int i=0;
	STARTKATA();
	strInput[i]=CKata;
	while (!EndKata)	{
		ADVKATA();
		i++;
		strInput[i]=CKata;
	}
	LENGTH=i;
	printf("Memuat..\n");
	printf("Sukses Memuat File String\n");
}

/////////////////////////////////
/*INPUT CNF DARI FILE EKSTERNAL*/
/////////////////////////////////
void Scan_CNF()	{
	int i=1;
	int j=0;
	STARTKATACNF();
	while (!EndKataCNF)		{
		CNF[i][j]=CKataCNF;
		IgnoreBlankCNF();
		while (CC!=ENTER)	{
			SalinKataCNF();
			j++;
			CNF[i][j]=CKataCNF;
			IgnoreBlankCNF();
		}
		IgnoreEnterCNF();
		i++;
		j=0;
		SalinKataCNF();
	}
	printf("Memuat..\n");
	printf("Sukses Memuat File CNF\n");
}

/////////////////////////////////////////////////////
/*MENENTUKAN SUATU TERMINAL INTEGER/REAL/IDENTIFIER*/
/////////////////////////////////////////////////////
Kata IntegerRealIdentifier(Kata Input)	{
	int i=0;
	Kata Out;
	if (!((Input.TabKata[0]>=48&&Input.TabKata[0]<=57)||(Input.TabKata[0]>=65&&Input.TabKata[0]<=90)||(Input.TabKata[0]>=97&&Input.TabKata[0]<=122)||Input.TabKata[0]==95)) {
		strcpy(Out.TabKata,"false");
		Out.Length=5;
		return Out;
	}
	if (!(Input.TabKata[0]>=48&&Input.TabKata[0]<=57))	{
		i=1;
		while (i<Input.Length)	{
			if (!((Input.TabKata[i]>=48&&Input.TabKata[i]<=57)||(Input.TabKata[i]>=65&&Input.TabKata[i]<=90)||(Input.TabKata[i]>=97&&Input.TabKata[i]<=122)||Input.TabKata[i]==95)) {
				strcpy(Out.TabKata,"false");
				Out.Length=5;
				return Out;
			}
			i++;
		}
		strcpy(Out.TabKata,"identifier");
		Out.Length=10;
		return Out;
	}
	i++;
	int cnt=0;
	while (i<Input.Length)	{
		if (!((Input.TabKata[i]>=48&&Input.TabKata[i]<=57)||Input.TabKata[i]==46)) {
			strcpy(Out.TabKata,"false");
			Out.Length=5;
			return Out;
		}
		if (Input.TabKata[i]==46)	{
			cnt++;
		}
		i++;
	}
	if (cnt==0)	{
		strcpy(Out.TabKata,"integer");
		Out.Length=7;
		return Out;
	} else if ((cnt==1)&&Input.TabKata[i-1]==46)	{
		strcpy(Out.TabKata,"real");
		Out.Length=4;
		return Out;
	}
	strcpy(Out.TabKata,"false");
	Out.Length=5;
	return Out;
}

int main(){
	int i, j, k, l,m,n,p;
	char A[100], B[100];
	/////////////////////////////////////////////////
	/*Inisialisasi simbol start dan jumlah profuksi*/
	/////////////////////////////////////////////////
	char S[]="Pascal";
	NProduction=118;

	//Input CNF dan String dari File Eksternal
	Scan_CNF();
	Scan_String();	

	//////////////////////////////////////////
	/*Mengisi TABEL CYK dengan Algoritma CYK*/
	//////////////////////////////////////////
	//Mengisi Diagonal (String 1 length, Tabel[i][i])
	for(i=0; i<LENGTH; i++){
		boolean found = false;
		var.TabKata[0]='\0';
		//Mencari Variabel yang menghasilkan terminal tersebut
		for(j=1; j<=NProduction; j++){
			for(k=1; k<20; k++){
					if(strcmp(CNF[j][k].TabKata,strInput[i].TabKata)==0){
						found=true;
						if (var.TabKata[0]!=0) strcat(var.TabKata, ",");
						strcat(var.TabKata, CNF[j][0].TabKata);
					}
			}
		}
		//mengisikannya ke tabel
		if (found)	Table[i][i]=var;
		else	{
			temp=IntegerRealIdentifier(strInput[i]);
			if (strcmp(temp.TabKata,"false")!=0)	{
				var.TabKata[0]='\0';
				//Mencari Variabel yang menghasilkan terminal tersebut
				for(j=1; j<=NProduction; j++){
					for(k=1; k<20; k++){
							if(strcmp(CNF[j][k].TabKata,temp.TabKata)==0){
								found=true;
								if (var.TabKata[0]!=0) strcat(var.TabKata, ",");
								strcat(var.TabKata, CNF[j][0].TabKata);
							}
					}
				}
				Table[i][i]=var;
			} else Table[i][i]=temp;
		}
	}

	char* strA;
	char* strB;
	char arstrA[50][50];
	char arstrB[50][50];
	//Mengisi Sisa Tabel
	for (i=1; i<=LENGTH; i++) {
		for(j=i; j<LENGTH; j++){
			int cnt = 0;
			for(k=j-i; k<j; k++){
				//printf("TABEL[%d][%d] || TABEL[%d][%d]\n",j-i,k,k+1,j);
				//////////////
				//*KOMBINASI*/
				//////////////
				/*CONTOH : A dan A,B. kombinasinya AA, dan AB*/
				strcpy(A, Table[j-i][k].TabKata);
				strcpy(B, Table[k+1][j].TabKata);
				strA = strtok(A, ",");
				l=0;
				while(strA != NULL){
					arstrA[l][0]='\0';
					strcpy(arstrA[l], strA);
					strA = strtok(NULL, ",");
					l++;
				}
				strB = strtok(B, ",");
				m=0;
				while(strB != NULL){
					arstrB[m][0]='\0';
					strcpy(arstrB[m], strB);
					strB = strtok(NULL, ",");
					m++;
				}
				for(n=0; n<l; n++){
					for(p=0; p<m; p++){
						kombinasi[cnt][0]='\0';
						strcat(kombinasi[cnt], arstrA[n]);
						strcat(kombinasi[cnt], arstrB[p]);
						//printf("kombinasi = %s,tes\n", kombinasi[cnt]);
						cnt++;
					}
				}
			}
			var.TabKata[0]='\0';
			for(k=0; k<=NProduction; k++){
				for(l=1; l<20; l++){
					for(m=0; m<cnt; m++){
						if(strcmp(kombinasi[m], CNF[k][l].TabKata) == 0){
							boolean found = false;		
							if (strstr(var.TabKata,CNF[k][0].TabKata)!=NULL)	{
								found = true;
							}
							if(!found){
								if (var.TabKata[0]!=0) strcat(var.TabKata, ",");
								strcat(var.TabKata, CNF[k][0].TabKata);
							}
						}
					}
				}
			}
			strcpy(Table[j-i][j].TabKata, var.TabKata);
			
		}
	}

	//////////////////////
	/* Print Input User */
	//////////////////////
	printf("Input User :\n");	
	for(i=0; i<LENGTH; i++){
		printf("  %d. %s\n",i+1, strInput[i].TabKata);
	}

	/////////////////////
	/* Print Tabel CYK */
	/////////////////////
	printf("== TABEL CYK ==\n");
	for(i=LENGTH-1; i>=0; i--){
		k = 0;
		printf("- String (Length %d)\n", LENGTH-i);
		for(j=LENGTH-i-1; j<LENGTH; j++){
			printf("  (%d,%d)    \t{%s}\n", k+1, j+1, Table[k][j].TabKata);
			k++;
		}
		printf("\n");
	}
	// for(i=0; i<LENGTH; i++){
	// 	k = 0;
	// 	for(j=LENGTH-i-1; j<LENGTH; j++){
	// 		printf("[%s]\t", Table[k++][j].TabKata);
	// 	}
	// 	printf("\n");
	// }

	/////////////////////////////////////////////
	/* Menentukan String diterima atau ditolak */
	/////////////////////////////////////////////
	if (strstr(Table[0][LENGTH-1].TabKata,S)!=NULL)	printf("\nString diterima!\n");
	else printf("\nString ditolak!\n");
}