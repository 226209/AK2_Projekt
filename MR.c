#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
 
char testMR(unsigned int n,unsigned int p); // n-sprawdzana liczba , p- dokladnosc
unsigned int potegowanieModulo(unsigned int a,unsigned int b,unsigned int n); // funkcja oblicza a^b mod n
char testPoprawnosci(unsigned int p); // p-dokladnosc
 
 
int main()
{
    srand(time(NULL));
    unsigned int n=7;
    unsigned int p=1000;
    if(testPoprawnosci(p)==1)
        printf("Program dziala prawidlowo\n");
    else printf("Program nie dziala prawidlowo\n");
    
    if(n<2)
        printf("NIE\n");
    else if(n==2)
        printf("TAK\n");
    else if(n%2==0)
            printf("NIE\n");
    else
    {
        if(testMR(n,p)==1)
            printf("TAK\n");
        else printf("NIE\n");
    }
    getchar();
 
    return 0;
}
 
char testMR(unsigned int n,unsigned int p)
{
   long s,d,a;
   char liczbaZlozona;
   s=0;
   d=n-1;
   while(1) // petla oblicza s,d
   {
       if(d%2==0)
       {
            d=d/2;
            s++;
       }
       else break;
   }
   for(int i=0;i<p;i++) // ilsoc testow
   {
       a=rand() %(n-2) +2;  // losuj a gdzie 1 < a <n-2
       if(potegowanieModulo(a,d,n)!=1)
       {
           liczbaZlozona =0;
            for(int r=0;r<s;r++)
            {
                if(potegowanieModulo(a,d*(pow(2,r)),n)==n-1)
                {
                    liczbaZlozona=1;
                    break;
                }
            }
            if(liczbaZlozona!=1)
                return 0;
        }
   }
   return 1;
}
 
unsigned int potegowanieModulo(unsigned int a,unsigned int b,unsigned int n)
{
    unsigned long long r=a; // reszta
    unsigned long long w=1; // wynik
    unsigned int m=1; // maska bitowa
    while (m)
    {
        if(b&m)
            w=(w*r)%n;
        r=(r*r)%n;
        m<<=1;
    }
    return w;
}
 
char testPoprawnosci(unsigned int p)
{
    //wszystkie liczby znajdujace sie w pliku sa pierwsze
    FILE *plik = fopen("/home/ak2-linux/Pulpit/Ak-Projekt/liczby", "r");
    if(plik==NULL)
        printf("Nie udalo sie otworzyc pliku\n");
    else
    {
        unsigned int n;
	while(feof(plik)==0)
        {
            fscanf(plik,"%u",&n); // wczytanie kolejnej liczby
	    //printf("%u\n",n);
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
