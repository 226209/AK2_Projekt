#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <math.h>

unsigned long rozmiarTablicy = 5;
unsigned int rozmiarStringa = 600;

extern _Bool modulo2(unsigned long * liczba);
extern _Bool czyArg1WiekszyOdArg2(unsigned long* arg1, unsigned long* arg2,unsigned long  rozmiarTablicy);
extern _Bool czyArg1RownyArg2(unsigned long*arg1, unsigned long* arg2, unsigned long rozmiarTablicy);
extern void wczytajLiczbeSzestnastkowo(char *napis, unsigned long* liczba, unsigned long rozmiar);
extern void dziel(unsigned long* dzielna, unsigned long* dzielnik, 
		unsigned long* reszta_z_dzielenia, unsigned long rozmiar, unsigned long* wynik);
extern void dodaj(unsigned long * arg1, unsigned long * arg2, unsigned long * wynik, unsigned long rozmiar);
extern void przesunBityWLewo(unsigned long *arg1, unsigned long rozmiar);
extern void przesunBityWPrawo(unsigned long *arg, unsigned long rozmiar);
extern void odejmij(unsigned long *arg1, unsigned long *arg2, unsigned long * wynik, unsigned long rozmiar);
extern void mnoz(unsigned long *arg1, unsigned long *arg2, unsigned long rozmiar, unsigned long * wynik); 
extern void kopiujArg1DoArg2(unsigned long *arg1, unsigned long *arg2,unsigned long rozmiar);
void potegowanieModulo(unsigned long *a, unsigned long *b, unsigned long *n, unsigned long *w);
void wyzerujTablice(unsigned long *tab, unsigned long rozmiar);  
void wyzerujNapis(char *napis);
void wylosujOdDwaDoNMinusTrzy(unsigned long* liczba, unsigned long* resztaZDzielenia, unsigned long rozmiar);
unsigned long obliczWielkoscTablicy(char* napis);
_Bool testPoprawnosci(unsigned long p);
_Bool testMR(unsigned long * n, unsigned int p);
void czasPotegowania(int ilosc);
void czasTestuMR(unsigned int p);
void czyPierwsza(unsigned int p);
int main() {
	srand(time(NULL));
	//czyPierwsza(1);
	/*_Bool x=testPoprawnosci(10);
	if(x==1)
		printf("Program dziala prawidlowo\n");
	else printf("Program nie dziala prawidlowo\n");
    	}*/
	czasTestuMR(20);
	//czasPotegowania(65);
	}

void potegowanieModulo(unsigned long *a, unsigned long *b, unsigned long *n,unsigned long *w)
{
	unsigned long r[rozmiarTablicy];  // reszta
	//wyzerujTablice(r,rozmiarTablicy);
	kopiujArg1DoArg2(a,r,rozmiarTablicy); //r=a
	wyzerujTablice(w,rozmiarTablicy); // w=0
	w[0]=1;				   // wynik = 1 
        unsigned long m[rozmiarTablicy];    // maska bitowa
	wyzerujTablice(m,rozmiarTablicy);
	m[0]=1;				   // maska bitowa = 1 
	unsigned long wynik_mnozenia[rozmiarTablicy*2];
	unsigned long bufor_na_n[rozmiarTablicy*2];
	unsigned long reszta_z_dzielenia[rozmiarTablicy*2];
	unsigned long wynik_dzielenia[rozmiarTablicy*2];
	for(int i=0;i<rozmiarTablicy;i++)
	{
	     while(m[i])
             {
		 if(b[i]&m[i])
	         {
		 //w=(w*r)%n
		 wyzerujTablice(wynik_mnozenia,rozmiarTablicy*2);
		 wyzerujTablice(bufor_na_n,rozmiarTablicy*2);
		 wyzerujTablice(reszta_z_dzielenia,rozmiarTablicy*2);
		 wyzerujTablice(wynik_dzielenia,rozmiarTablicy*2);
		 mnoz(w,r,rozmiarTablicy,wynik_mnozenia); 
		 kopiujArg1DoArg2(n,bufor_na_n,rozmiarTablicy); // kopiuje rozmiarTablicy pierwszych elementow 
		 dziel(wynik_mnozenia,bufor_na_n,reszta_z_dzielenia,rozmiarTablicy*2,wynik_dzielenia);
		 kopiujArg1DoArg2(reszta_z_dzielenia,w,rozmiarTablicy);
		 }	 	
		//r=(r*r)%n
		 wyzerujTablice(wynik_mnozenia,rozmiarTablicy*2);
		 wyzerujTablice(bufor_na_n,rozmiarTablicy*2);
		 wyzerujTablice(reszta_z_dzielenia,rozmiarTablicy*2);
		 wyzerujTablice(wynik_dzielenia,rozmiarTablicy*2);
		 mnoz(r,r,rozmiarTablicy,wynik_mnozenia); 
		 kopiujArg1DoArg2(n,bufor_na_n,rozmiarTablicy); // kopiuje rozmiarTablicy pierwszych elementow 
		 dziel(wynik_mnozenia,bufor_na_n,reszta_z_dzielenia,rozmiarTablicy*2,wynik_dzielenia);
		 kopiujArg1DoArg2(reszta_z_dzielenia,r,rozmiarTablicy);
		 przesunBityWLewo(m,rozmiarTablicy);

	     }
	}
        	
}
void wyzerujTablice(unsigned long *tab, unsigned long rozmiar)
{
	for (unsigned long i=0; i<rozmiar;i++)
		tab[i]=0;
}
void wyzerujNapis(char* napis)
{
	for(int i=0;i<rozmiarStringa;i++)
		napis[i]=0;
}
_Bool testMR(unsigned long * n, unsigned int p)
{
	char liczbaZlozona;
	unsigned long s[rozmiarTablicy];
        unsigned long d[rozmiarTablicy];
        unsigned long a[rozmiarTablicy];
	unsigned long r[rozmiarTablicy];
	wyzerujTablice(s,rozmiarTablicy);     //s=0
	 kopiujArg1DoArg2(n,d,rozmiarTablicy); // d=n
	unsigned long jeden[rozmiarTablicy];  
	wyzerujTablice(jeden,rozmiarTablicy); 
	jeden[0]=1;
	odejmij(d,jeden,d,rozmiarTablicy);  //d=d-1

	while(1)
	{
		if(modulo2(d)==0)
		{
			przesunBityWPrawo(d,rozmiarTablicy); // d=d/2
			dodaj(s,jeden,s,rozmiarTablicy); // s++
		}else
			break;
	}
unsigned long _w[rozmiarTablicy];
unsigned long _d[rozmiarTablicy];
unsigned long nMinus1[rozmiarTablicy];
kopiujArg1DoArg2(n,nMinus1,rozmiarTablicy);
odejmij(nMinus1,jeden,nMinus1,rozmiarTablicy);
for(int i=0;i<p;i++) // ilosc testow
{
		// wylosuj liczbe z przedzialy [2,n-2]	
		wylosujOdDwaDoNMinusTrzy(n,a,rozmiarTablicy);
	
	potegowanieModulo(a,d,n,_w);
	// jezeli a^d mod n !=1
	if(!czyArg1RownyArg2(_w,jeden,rozmiarTablicy))
	{
		liczbaZlozona=0;
		kopiujArg1DoArg2(d,_d,rozmiarTablicy);
		wyzerujTablice(r,rozmiarTablicy);
		potegowanieModulo(a,_d,n,_w);
		if(czyArg1RownyArg2(_w,nMinus1,rozmiarTablicy))
		{
			liczbaZlozona=1;
			break;
		}
		dodaj(r,jeden,r,rozmiarTablicy); 
		// dla r >0
		while(czyArg1WiekszyOdArg2(s,r,rozmiarTablicy)) //dopoki r<s
		{
			przesunBityWLewo(_d,rozmiarTablicy);
			potegowanieModulo(a,_d,n,_w);
			if(czyArg1RownyArg2(_w,nMinus1,rozmiarTablicy))
			{
				liczbaZlozona=1;
				break;
			}

			dodaj(r,jeden,r,rozmiarTablicy); // r++
		}
		if(liczbaZlozona!=1)
			return 0;
	}		
}
return 1;	




}


unsigned long obliczWielkoscTablicy(char* napis)
{
	int i=0;
	while(napis[i]!='\n')
	{
		i++;
	}
	i=i/8;
	i++;
	return i;
}

void wylosujOdDwaDoNMinusTrzy(unsigned long* liczba, unsigned long* resztaZDzielenia, unsigned long rozmiar) {
    unsigned long liczbaDoWylosowania[rozmiar];
    unsigned long kopiaLiczby[rozmiar];
    unsigned long wynikDzielenia[rozmiar];
    unsigned long trzy[rozmiar];
    unsigned long piec[rozmiar];
    unsigned long dwa[rozmiar];
    unsigned long jeden[rozmiar];
    wyzerujTablice(jeden, rozmiar);
    wyzerujTablice(dwa, rozmiar);
    wyzerujTablice(piec, rozmiar);
    wyzerujTablice(trzy, rozmiar);
    wyzerujTablice(liczbaDoWylosowania, rozmiar);
    wyzerujTablice(resztaZDzielenia, rozmiar);
    wyzerujTablice(kopiaLiczby, rozmiar);
    wyzerujTablice(wynikDzielenia, rozmiar);
 
    trzy[0] = 3;
    piec[0] = 5;
    dwa[0] = 2;
    jeden[0] = 1;
 
    int i;
    for (i = 0; i<rozmiar; i++) {
        liczbaDoWylosowania[i] = rand() + 2;
    }
 
    kopiujArg1DoArg2(liczba,kopiaLiczby,rozmiar);
    dziel(liczbaDoWylosowania, kopiaLiczby, resztaZDzielenia, rozmiar, wynikDzielenia);
    if (czyArg1WiekszyOdArg2(dwa, resztaZDzielenia, rozmiar))
        resztaZDzielenia[0] = 2;
}

_Bool testPoprawnosci(unsigned long p)
{
	FILE *plik =fopen("liczbyhex","r");
	if(plik==NULL)
		printf("Nie udalo sie otworzyc pliku\n");
	else
	{
		char string[600];
		while(fgets(string,600,plik)!=NULL)
		{
		rozmiarTablicy=obliczWielkoscTablicy(string);
		unsigned long n[rozmiarTablicy];
		wyzerujTablice(n,rozmiarTablicy);
		wczytajLiczbeSzestnastkowo(string,n,rozmiarTablicy);
			if(testMR(n,p)==0)
			{
				fclose(plik);
				return 0;
			}

		}
		fclose(plik);
		return 1;
	}
	return 0;
}

void czasPotegowania(int ilosc)
{
	FILE *plik;
	plik = fopen("/home/sebastian/AK2_Projekt/ak2_projekt_v3/czasPotegowania","w");
	clock_t start,end;
	double cpu_time_used;
	for(int i=1;i<=ilosc;i++)
	{
		rozmiarTablicy=i;
		unsigned long a[rozmiarTablicy];
		unsigned long b[rozmiarTablicy];
		unsigned long n[rozmiarTablicy];
		unsigned long w[rozmiarTablicy];
		wyzerujTablice(w,rozmiarTablicy);
		for(int i=0;i<rozmiarTablicy;i++)
		{
			a[i]=rand() %ULONG_MAX;
			b[i]=rand() %ULONG_MAX;
			n[i]=rand() %ULONG_MAX;
		}

		start=clock();
		potegowanieModulo(a,b,n,w);
		end=clock();
		cpu_time_used = ((double)(end-start))/CLOCKS_PER_SEC;
		fprintf(plik,"%f\n",cpu_time_used);

	}
	fclose(plik);


}

void czasTestuMR(unsigned int p)
{
	FILE *plikCzas;
	plikCzas = fopen("/home/sebastian/AK2_Projekt/ak2_projekt_v3/czasTestuMR","w");
	clock_t start,end;
	double cpu_time_used;
	int cos=0
		;
	FILE *plik =fopen("liczbyhex","r");
	if(plik==NULL)
		printf("Nie udalo sie otworzyc pliku\n");
	else
	{

		char string[600];
		while(fgets(string,600,plik)!=NULL)
		{
		
		rozmiarTablicy=obliczWielkoscTablicy(string);
		unsigned long n[rozmiarTablicy];
		wyzerujTablice(n,rozmiarTablicy);
		wczytajLiczbeSzestnastkowo(string,n,rozmiarTablicy);
			start=0;
			end=0;
			cpu_time_used=0;
			start=clock();
			testMR(n,p);
			end=clock();
			cpu_time_used = ((double)(end-start))/CLOCKS_PER_SEC;
			fprintf(plikCzas,"%f %ld\n",cpu_time_used,rozmiarTablicy*32);
		}
		fclose(plik);
		
	}

	fclose(plik);


}

void czyPierwsza(unsigned int p)
{
	FILE *plik;
	clock_t start,end;
	double cpu_time_used;
	plik = fopen("/home/sebastian/AK2_Projekt/ak2_projekt_v3/czyPierwsza","r");
	if(plik==NULL)
		printf("Nie udalo sie otworzyc pliku\n");
	else
	{

		char string[600];
		fgets(string,600,plik);
		rozmiarTablicy=obliczWielkoscTablicy(string);
		unsigned long n[rozmiarTablicy];
		wyzerujTablice(n,rozmiarTablicy);
		wczytajLiczbeSzestnastkowo(string,n,rozmiarTablicy);
				start=clock();
		
			if(testMR(n,p))
				printf("Liczba jest prawdopodonie pierwsza z prawdopodobienstwem 1-1/4^%u\n", p);
			else printf("Liczba zlozona\n");
			printf("%ld bitow", rozmiarTablicy*32);
			end=clock();
		cpu_time_used = ((double)(end-start))/CLOCKS_PER_SEC;
		printf("Test trwal %f sekund", cpu_time_used);

	}

	fclose(plik);


}


