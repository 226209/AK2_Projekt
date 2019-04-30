#include <stdio.h>
#include <stdlib.h>

unsigned long rozmiarTablicy = 5;

extern void dziel(unsigned long* dzielna, unsigned long* dzielnik, 
		unsigned long* reszta_z_dzielenia, unsigned long rozmiar, unsigned long* wynik);
extern void dodaj(unsigned long * arg1, unsigned long * arg2, unsigned long * wynik, unsigned long rozmiar);
extern void przesunBityWLewo(unsigned long *arg1, unsigned long rozmiar);
extern void odejmij(unsigned long *arg1, unsigned long *arg2, unsigned long * wynik, unsigned long rozmiar);
extern void mnoz(unsigned long *arg1, unsigned long *arg2, unsigned long rozmiar, unsigned long * wynik); 
extern void kopiujArg1DoArg2(unsigned long *arg1, unsigned long *arg2,unsigned long rozmiar);
void potegowanieModulo(unsigned long *a, unsigned long *b, unsigned long *n, unsigned long *w);
void wyzerujTablice(unsigned long *tab, unsigned long rozmiar);
void wczytajLiczbe(unsigned long *liczba,unsigned long rozmiarTablicy, char * napis);  
int main() {
    
    unsigned long a[rozmiarTablicy];
    unsigned long b[rozmiarTablicy];
    unsigned long n[rozmiarTablicy];
    unsigned long w[rozmiarTablicy];
    char  napis[600];
    fgets(napis,600,stdin);
    wczytajLiczbe(a,rozmiarTablicy,napis);
    //potegowanieModulo(a,b,n,w);    
     //for(int i=0;i<rozmiarTablicy;i++)
//	    printf("%ld\n",w[i]);
}

void potegowanieModulo(unsigned long *a, unsigned long *b, unsigned long *n,unsigned long *w)
{
	unsigned long r[rozmiarTablicy];  // reszta
	wyzerujTablice(r,rozmiarTablicy);
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
	for (int i=0; i<rozmiar;i++)
		tab[i]=0;
}
void wczytajLiczbe(unsigned long *liczba,unsigned long rozmiarTablicy, char * napis)
{	//tymczasowa funkcja 
	unsigned long waga[rozmiarTablicy];
	unsigned long dziesiec[rozmiarTablicy];
	unsigned long wynik_mnozenia[rozmiarTablicy*2];
	unsigned long wartosc_znaku[rozmiarTablicy];
	wyzerujTablice(waga,rozmiarTablicy);
	waga[0]=1;
	wyzerujTablice(dziesiec,rozmiarTablicy);
	dziesiec[0]=10;
	wyzerujTablice(wartosc_znaku,rozmiarTablicy);
	unsigned long i=0;
	while(napis[i]!='\0')
		i++; //oblicz ilosc elementow 
	for(;i>=0;i--)
	{
		wyzerujTablice(wynik_mnozenia,rozmiarTablicy*2);
		//waga*wartosc_znaku
		wartosc_znaku[0]=napis[i];
		wartosc_znaku[0]-=48;
		printf("%ld",wartosc_znaku[0]);
		mnoz(waga,wartosc_znaku,rozmiarTablicy,wynik_mnozenia);
		//liczba=liczba+waga*kolejna_cyfra
		dodaj(liczba,wynik_mnozenia,liczba,rozmiarTablicy);
		wyzerujTablice(wynik_mnozenia,rozmiarTablicy*2);
		//oblicz kolejna wage 
		mnoz(waga,dziesiec,rozmiarTablicy,wynik_mnozenia);
		kopiujArg1DoArg2(waga,wynik_mnozenia,rozmiarTablicy);
	}
}




