// Adam Perliñski, grupa 213B, SDIZO_NR1



// ConsoleApplication49.cpp : Defines the entry point for the console application.
//
//visual studio wywala³ security warning, wy³aczy³em warningi(zwi¹zane z bezpieczeñstwem zmiennych pobieraj¹cych dane z pliku (co mo¿e zoverflowowaæ buffer, ale nie w naszym wwypadku)//
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <tchar.h>
#include <time.h>
#include <stdlib.h>


struct strtype {
	int strint;
	char strchar;
	float strfloat;
};


struct strtype **losowanie(int N) { // funkcja typu wskaznik do tablicy wskazników do  struktur
	/*calloc*/
	int i;
	srand(time(NULL)); // seeduje randa, by generowa³ wynik ró¿ny
	struct strtype **PointerForArray = calloc(N,sizeof(struct strtype*)); // alokuje pamiec dla samej tablicy
	for (i = 0; i <= N-1; i++)
	{
		PointerForArray[i] = calloc(N,sizeof(struct strtype)); //calloc dla kolejnych struktur
		PointerForArray[i]->strint = (1 + rand() % 9999); 
		PointerForArray[i]->strchar = (65 + rand() % (25 - 1 + 1)); // ascii dla du¿ych liter (od 65 do 90) 
		PointerForArray[i]->strfloat = ((float)100 + i); // float by unikn¹æ mo¿liwej stratych danych
	}
	return PointerForArray;
}
void usuwanie(struct strtype **PointerForArray, int N) {
     int i;
	for (i = 0; i <= N-1; i++) {
		free(PointerForArray[i]);
	}
	free(PointerForArray);
}
void sortowanie(struct strtype **PointerForArray, int N) {
	struct strtype *placeholder;
	int posortowane = 0;
	int zeswapowane = 0;
	int length = N - 1;
	int i;
	while((length>0) && (!posortowane)) {
		for (i = 0; i < length; i++) {
			if (PointerForArray[i]->strint > PointerForArray[i + 1]->strint) {
				placeholder = PointerForArray[i];
				PointerForArray[i] = PointerForArray[i + 1];
				PointerForArray[i + 1] = placeholder;
				zeswapowane = 1;
			}
		}
		if (!zeswapowane) {
			posortowane = 1;
		}
		zeswapowane = 0;
		length--;
	}
}
 int  zliczanie(struct strtype **PointerForArray, int N, char x) {
	int counter=0;
	int i;
	for (i = 0; i <= N-1; i++) {
		if (PointerForArray[i]->strchar == x) {
			counter++;
		}
	}

	return counter;
}
int main()
{
	struct strtype **PointerForArray; // deklaruje znienne, tablice wskazników na strukturê
									  // deklaruje znienne, tablice wskazników na strukturê
	int znaki;
	int i;
	clock_t begin, end;
	double time_spent;
	begin = clock();
	/* here, do your time-consuming job */
	int N;
	char X;
	FILE* fp = fopen("inlab01.txt", "r");
	if (fp == NULL)
		return -1;
	fscanf(fp, "%d %c", &N, &X);
	fclose(fp);
	PointerForArray=losowanie(N); // przypisujemy naszemu wskaŸnikowi, adres wygenerowanej tablicy
	sortowanie(PointerForArray, N); // sortujemy ni¹
	
	
	znaki = zliczanie(PointerForArray, N, X); // zliczamy znak
		for (i = 0; i < 20;i++) {
		printf("%d	%c	%1.f\n", PointerForArray[i]->strint,PointerForArray[i]->strchar,PointerForArray[i]->strfloat); //%1.f, by nie wyswieta³o zer po przecinku
	} // wypisanie 20 pierwszych struktur
	usuwanie(PointerForArray, N);
	end = clock(); 

	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;	
	printf("%f spedzonego czasu, znaleziono %d wyszukiwanego znaku %c\n", time_spent, znaki, X);


	getch(); // holdujemy konsole w miejscu
	return 0;

}

