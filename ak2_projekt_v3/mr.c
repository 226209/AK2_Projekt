#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

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
int main() {
	testPoprawnosci(10);
	//_Bool x=testPoprawnosci(100);
//	if(x==1)
//		printf("Program dziala prawidlowo\n");
//	else printf("Program nie dziala prawidlowo\n");
    	/*char napis[600];
	unsigned int p=10;
	printf("Prosze podac liczbe ,ktora ma byc przetestowana.\n Liczbe prosze podac w systestemie o podstawie 16.\n Liczby od A do F prosze wpisywac z wielkich liter.\n");
	fgets(napis,600,stdin);
	rozmiarTablicy=obliczWielkoscTablicy(napis);
	unsigned long n[rozmiarTablicy];
	wyzerujTablice(n,rozmiarTablicy);
	wczytajLiczbeSzestnastkowo(napis,n,rozmiarTablicy);
	unsigned long dwa[rozmiarTablicy];
	wyzerujTablice(dwa,rozmiarTablicy);
	dwa[0]=2;
	unsigned long a[rozmiarTablicy];
	wylosujOdDwaDoNMinusTrzy(n,a,rozmiarTablicy);
	if(czyArg1WiekszyOdArg2(dwa,n,rozmiarTablicy))
		printf("NIE\n");
	else if(czyArg1RownyArg2(dwa,n,rozmiarTablicy))
		printf("TAK\n");
	else if(modulo2(n)==0)
		printf("NIE\n");
	else
	{
		if(testMR(n,p)==1)
			printf("TAK\n");
		else printf("NIE\n");
	}
	getchar();
   /* unsigned long a[rozmiarTablicy];
    unsigned long b[rozmiarTablicy];
    unsigned long n[rozmiarTablicy];
    unsigned long w[rozmiarTablicy];
    wyzerujTablice(a,rozmiarTablicy);
    wyzerujTablice(b,rozmiarTablicy);
    wyzerujTablice(n,rozmiarTablicy);
    wyzerujTablice(w,rozmiarTablicy);
    char  napis[600];
    fgets(napis,600,stdin);
    wczytajLiczbeSzestnastkowo(napis,a,rozmiarTablicy);
    wyzerujNapis(napis);
    fgets(napis,600,stdin);
    wczytajLiczbeSzestnastkowo(napis,b,rozmiarTablicy);
    wyzerujNapis(napis);
    fgets(napis,600,stdin);
    wczytajLiczbeSzestnastkowo(napis,n,rozmiarTablicy);
    potegowanieModulo(a,b,n,w);    
     //for(int i=0;i<rozmiarTablicy;i++)
//	    printf("%ld\n",w[i]);
*/
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
		if(modulo2==0)
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
		//a=rand() % (n-2) +2
		
		wylosujOdDwaDoNMinusTrzy(n,a,rozmiarTablicy);
	
	potegowanieModulo(a,d,n,_w);
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
		i++;
	i=i/4;
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
		while(feof(plik)==0)
		{
		fgets(string,600,plik);
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
	FILE *plik =fopen("liczbyCzasTestuMR","r");
	if(plik==NULL)
		printf("Nie udalo sie otworzyc pliku\n");
	else
	{

		char string[600];
		while(feof(plik)==0)
		{
		fgets(string,600,plik);
		rozmiarTablicy=obliczWielkoscTablicy(string);
		unsigned long n[rozmiarTablicy];
		wyzerujTablice(n,rozmiarTablicy);
		wczytajLiczbeSzestnastkowo(string,n,rozmiarTablicy);
			start=clock();
			testMR(n,p);
			end=clock();
			cpu_time_used = ((double)(end-start))/CLOCKS_PER_SEC;
			fprintf(plikCzas,"%f %ld\n",cpu_time_used,rozmiarTablicy);
		}
		fclose(plik);
	}

	fclose(plik);


}
