##Kody funkcji systemoych
EXIT = 1
READ = 3
WRITE = 4
STDIN = 0
STDOUT = 1
SYSCALL32 = 0x80
ERR_CODE =0
.data
dzieleniePrzezZero: .ascii "Proba dzielenia przez 0"
dzieleniePrzezZero_dlugosc = . - dzieleniePrzezZero
.global porownaj2Liczby
.global kopiujArg1DoArg2
.global przesunBityWLewo
.global przesunBityWPrawo
.global odejmij
.global dodaj
.global mnoz
.global dziel
.global wczytajLiczbeSzestnastkowo
.global modulo2
.global czyArg1WiekszyOdArg2
.global czyArg1RownyArg2
.text

#argumenty (adres stringa, adres liczby, rozmair liczby)
#zmienne lokalne dlugosc stringa
.type wczytajLiczbeSzestnastkowo, @function
wczytajLiczbeSzestnastkowo:
	pushl %ebp
	movl %esp, %ebp
	pushl %ecx
	pushl %edi
	pushl %eax
	pushl %edx
	movl $0, %ecx	#licznik=0
	oblicz_dlugosc:
		movl 8(%ebp), %edi		#adres lancucha znakow
		movb (%edi,%ecx,1), %al		#pobierz znak
		cmpb $10, %al 			 #sprawdz czy koniec ciagu
		je koniec_oblicz_dlugosc	 
			cmpb $65, %al	
			jae litera
			subb $'0', %al		
			jmp koniec_sprawdzania
			litera:
			subb $55, %al
			koniec_sprawdzania:
			##przsuwanie bitow
			pushl %ecx
			movl $4, %edx 	#licznik petli
			wykonuj4Razy:
			movl 12(%ebp), %edi 	#adres liczby 
			cmpl $0, %edx		
			je koniecWykonuj4Razy
			movl $1, %ecx		
			shll $1, (%edi)
			przesunWszystkieBityWlewo:
			pushf			#zachowaj przeniesienie
			cmpl 16(%ebp), %ecx
			je koniecPrzesunWszystkieBityWlewo
			popf		#pobierz flage cf
			rcll $1, (%edi,%ecx,4)	
			incl %ecx
			jmp przesunWszystkieBityWlewo
			koniecPrzesunWszystkieBityWlewo:
			popf
			decl %edx
			jmp wykonuj4Razy
			koniecWykonuj4Razy:
			#koniec
			popl %ecx
			movl 12(%ebp), %edi		#adres liczby
			addb %al, (%edi)		#dodaj do liczby
			incl %ecx
		jmp oblicz_dlugosc
	koniec_oblicz_dlugosc: 
	popl %eax
	popl %edi
	popl %ecx
	movl %ebp, %esp
	popl %ebp
	ret
# adres stringa, adres liczby, rozmair liczby
#(adres 1 liczby, adres 2 liczby, rozmiar argumentow)
.type porownaj2Liczby, @function
porownaj2Liczby:
    pushl %ebp
    movl %esp, %ebp
    pushl %edx
    pushl %edi
    pushl %ecx
    movl 8(%ebp), %edx  #adres 1 liczby
    movl 12(%ebp), %edi #adres 2 liczby
    movl 16(%ebp), %ecx #rozmiar argumentow
    decl %ecx      
    sprawdzaj_wszystkie:
    cmpl $0, %ecx  
    jl koniec_sprawdzaj_wszystkie
    movl (%edx,%ecx,4), %eax
    cmpl (%edi,%ecx,4), %eax
    ja pierwsza_wieksza
    jb druga_wieksza
    decl %ecx
    jmp sprawdzaj_wszystkie
    koniec_sprawdzaj_wszystkie:
    movl $0, %eax           #zwraca zero gdy liczby sa rowne
    jmp koniec_porownywania
    pierwsza_wieksza:
    movl $1, %eax           #zwraca 1 gdy pierwsza wieksza
    jmp koniec_porownywania    
    druga_wieksza:
    movl $2, %eax           #zwraca 2 gdy druga wieksza
    koniec_porownywania:
    popl %ecx
    popl %edi
    popl %edx
    movl %ebp, %esp
    popl %ebp
        ret
#(Arg1, Arg2, rozmiar)
.type kopiujArg1DoArg2, @function
kopiujArg1DoArg2:
    pushl %ebp
    movl %esp, %ebp
    movl 8(%ebp), %edi #arg1
    movl 12(%ebp), %edx #arg2
    movl $0, %ecx
    kopiuj:
    cmpl 16(%ebp), %ecx
    je koniec_kopiowania
    movl (%edi,%ecx,4), %eax
    movl %eax, (%edx,%ecx,4)
    incl %ecx
    jmp kopiuj
    koniec_kopiowania:
    movl %ebp, %esp
    popl %ebp
    ret
#(adres arg, arg_size)
.type przesunBityWLewo, @function
przesunBityWLewo:
    pushl %ebp
    movl %esp, %ebp
    pushl %edi
    pushl %ecx
    movl 8(%ebp), %edi
    movl $1, %ecx
    shll $1, (%edi)
    przesunWLewo:
    pushf           #zachowaj przeniesienie
    cmpl 12(%ebp), %ecx
    je koniecPrzesunWLewo
    popf        #pobierz flage cf
    rcll $1, (%edi,%ecx,4) 
    incl %ecx
    jmp przesunWLewo
    koniecPrzesunWLewo:
    popf
    popl %ecx
    popl %edi
    movl %ebp, %esp
    popl %ebp  
ret
#(arg1, arg1_size)
.type przesunBityWPrawo, @function
przesunBityWPrawo:
    pushl %ebp
    movl %esp, %ebp
    pushl %edi
    pushl %ecx
    movl 8(%ebp), %edi  #adres argumentu
    movl 12(%ebp), %ecx #rozmiar argumentow
    decl %ecx      
    shrl $1, (%edi,%ecx,4)
    decl %ecx
    przesunWPrawo:
    pushf           #zachowaj przeniesienie
    cmpl $0, %ecx
    jl koniecPrzesunWPrawo
    popf        #pobierz flage cf
    rcrl $1, (%edi,%ecx,4) 
    decl %ecx
    jmp przesunWPrawo
    koniecPrzesunWPrawo:
    popf
    popl %ecx
    popl %edi
    movl %ebp, %esp
    popl %ebp    
ret
 
#Funkcja dodaje liczby o dowolnej wielokrotnosci 4bajtow
#Funkcja przyjmuje 4 argumenty: adres 1 skladnika , adres 2 skaldnika,
# adres wyniku, rozmiar argumentow
.type dodaj, @function
dodaj:
    pushl %ebp
    movl %esp, %ebp
    movl 8(%ebp), %edx      #wpisz adres arg1
    movl (%edx), %eax   #wpisz wartosc z pod arg1
    movl 12(%ebp), %edx #wpisz adres arg2
    addl (%edx), %eax   #dodaj arg2 od arg1
    movl 16(%ebp), %edx #wpisz adres wyniku
    movl %eax, (%edx)   #wpisz wartosc dodawania do wyniku
    movl $1, %ecx       #licznik 1
    dodaj_:
    pushf           #zachowaj flagi
    cmpl 20(%ebp), %ecx #dopoki rozne od dlugosci argumentow
    je koniec_dodaj
    popf             #pobierz flagi ze stosu
    movl 8(%ebp), %edx   #wez adres arg1
    movl (%edx,%ecx,4), %eax #wez i-ty wyraz arg1
    movl 12(%ebp), %edx  #wez adres arg2
    adcl (%edx,%ecx,4), %eax #dodaj arg2 do arg1
    movl 16(%ebp), %edx #wez adres wyniku
    movl %eax, (%edx,%ecx,4)
    incl %ecx        #zwieksz licznik
    jmp dodaj_
    koniec_dodaj:
    popf
    movl %ebp, %esp
    popl %ebp
    ret
 
#Funkcja odejmuje liczby o dowolnej wielokrotnosci 4bajtow
#Funkcja przyjmuje 4 argumenty: adres 1 skladnika , adres 2 skaldnika,
# adres wyniku, rozmiar argumentow
.type odejmij, @function  
odejmij:
    pushl %ebp
    movl %esp, %ebp
    movl 8(%ebp), %edx      #wpisz adres arg1
    movl (%edx), %eax   #wpisz wartosc z pod arg1
    movl 12(%ebp), %edx #wpisz adres arg2
    subl (%edx), %eax   #odejmij arg2 od arg1
    movl 16(%ebp), %edx #wpisz adres wyniku
    movl %eax, (%edx)   #wpisz wartosc odejmowania do wyniku
    movl $1, %ecx       #licznik 1
    odejmij_:  
    pushf           
    cmpl 20(%ebp), %ecx #dopoki rozne od dlugosci argumentow
    je koniec_odejmij
    popf             #pobierz flagi ze stosu
    movl 8(%ebp), %edx   #wez adres arg1
    movl (%edx,%ecx,4), %eax #wez i-ty wyraz arg1
    movl 12(%ebp), %edx  #wez adres arg2
    sbbl (%edx,%ecx,4), %eax #wez i-ty wyraz arg2
    movl 16(%ebp), %edx  #wez adres wyniku
    movl %eax, (%edx,%ecx,4) #wpisz wartosc do i-tego elementu wyniku
    incl %ecx        #zwieksz licznik
    jmp odejmij_
    koniec_odejmij:
    popf
    movl %ebp, %esp
    popl %ebp
    ret
 
.type mnoz, @function
mnoz:
    #argumenty (adres mnoznej, adres mnoznika, rozmiar arg, adr wynik (size*2)
    #ecx - licznik petli wewnetrznej
    #ebx - licznik petli zewnetrznej
    pushl %ebp
    movl %esp, %ebp
    pushl %ebx
    pushl %edi
    movl $0, %ebx
    petla_zewnetrzna:
    cmpl 16(%ebp), %ebx # sprawdz warunek
    je koniec_petla_zewnetrzna
        #---------------------------petla wewnetrzna-------------------
        movl $0, %ecx # wyzerowanie licznika petli wewnetrznej
        petla_wewnetrzna:
        cmpl 16(%ebp), %ecx # sprawdzenie warunku petli
        je koniec_petla_wewnetrzna
        movl 8(%ebp), %edi      # adres mnoznej
        movl (%edi,%ecx,4), %eax # 4 bajty mnoznej do eax
        xor %edx, %edx          #wyzerowanie edx
        movl 12(%ebp), %edi      #adres mnoznika
        mull (%edi,%ebx,4) # 4 bajty mnoznika do ebx
        # eax mlodsza czesc , edx starsza
        pushl %ecx # zachowaj licznik petli
        # dodaj do wyniku
        movl 20(%ebp), %edi     #adres wyniku
        addl %ebx, %ecx         #ustaw wage w ecx ecx=ecx+ebx
        addl %eax, (%edi,%ecx,4)
        incl %ecx               #kolejna waga
        adcl %edx, (%edi,%ecx,4)
        #dodaj przeniesienie jezeli wystapilo
    dodawaj_przeniesienie:
    jnc koniec_dodawaj_przeniesienie    
        incl %ecx               #kolejna waga
        adcl $0, (%edi,%ecx,4)
    jmp dodawaj_przeniesienie
    koniec_dodawaj_przeniesienie:
        popl %ecx               #pobierz licznik
        incl %ecx              
        jmp petla_wewnetrzna
        koniec_petla_wewnetrzna:
        #---------------------------koniec petla wewnetrzna-------------------
    incl %ebx           #zwieksz licznik petli zewnetrznej
    jmp petla_zewnetrzna
    koniec_petla_zewnetrzna:
    popl %edi
    popl %ebx
    movl %ebp, %esp
    popl %ebp
    ret
   
#(dzielna, dzielnik,reszta_z_dzielenia, rozmiar)
.type dziel, @function
dziel:
      #arg1- dzielna, arg2- dzielnik, reszta_z_dzielenia,rozmiar, adr wyniku
pushl %ebp
movl %esp, %ebp
pushl %ebx
pushl %edi
    #sprawdz czy dzielnik = 0
    movl 12(%ebp), %edi     #adres dzielnika
    movl $0, %ecx       #licznik
    sprawdz_wszystkie_elementy:
    cmpl 20(%ebp), %ecx    
    je koniec_sprawdz_wszystkie_elementy
    cmpl $0, (%edi,%ecx,4) 
    jne nie_zero
    incl %ecx
    jmp sprawdz_wszystkie_elementy
    koniec_sprawdz_wszystkie_elementy:
    movl $WRITE, %eax
    movl $STDOUT, %ebx
    movl $dzieleniePrzezZero, %ecx
    movl $dzieleniePrzezZero_dlugosc, %edx
    int $SYSCALL32
    popl %edi
    popl %ebx
    movl %ebp, %esp
    popl %ebp
    ret
    nie_zero:
    #kopiuj dzielna do reszty_z_dzielenia
    pushl 20(%ebp)  #rozmiar arg
    pushl 16(%ebp)  #reszta_z_dzielenia
    pushl 8(%ebp)   #dzielna
    call kopiujArg1DoArg2
    addl $12, %esp
    movl $0, %ecx   #licznik przesuniec
    #sprawdz czy najstarszy bit dzielnej =1
    movl 8(%ebp), %edi  #adres dzielnej
    movl 20(%ebp), %edx #rozmiar
    decl %edx       #rozmiar -1
    movl $2147483648, %eax  #10....0
    andl (%edi,%edx,4), %eax    #najstarszy bit =1
    jz skalowanie
    movl 12(%ebp), %edi #adres dzielnika
    przeskaluj_maksymalnie_dzielnik:
    movl $2147483648, %eax 
    andl (%edi,%edx,4), %eax
    jnz koniec_skalowania
    pushl 20(%ebp)  #rozmiar argumentow
    pushl 12(%ebp)  #dzielnik
    call przesunBityWLewo
    addl $8, %esp
    incl %ecx
    jmp przeskaluj_maksymalnie_dzielnik
    #------
    #skalowanie dzielnej:
    #(adres 1 liczby, adres 2 liczby, rozmiar argumentow)
    skalowanie:
    pushl 20(%ebp) #rozmiar argumentow
    pushl 12(%ebp)  #dzielnik
    pushl 16(%ebp) #reszta_z_dzielenia
    call porownaj2Liczby    #eax=0 rowne, eax=1 pierwsza wieksza, eax=2 druga wieksza
    addl $12, %esp
    cmpl $2, %eax
    je koniec_skalowania
    incl %ecx
    #(adres arg, arg_size)
    pushl 20(%ebp)  #rozmiar argumentow
    pushl 12(%ebp)  #dzielnik
    call przesunBityWLewo
    addl $8, %esp
    jmp skalowanie
    koniec_skalowania:
    #Dzielna przeskalowana
    #sprawdz i odejmij     ##########do tad dziala
    odejmuj_kolejne:
    cmpl $0, %ecx       #tyle samo sprawdzen co skalowac w lewo
    je koniec_odejmuj_kolejne
    #sprawdz czy mniejsze jezeli tak odejmij jezeli nie skaluj w prawo dzielnik
    #wynik przesun w lewo
    pushl 20(%ebp)  #rozmiar
    pushl 24(%ebp)  #wynik dzielenia ###############
    call przesunBityWLewo  
    addl $8, %esp
    pushl 20(%ebp) #rozmiar argumentow
    pushl 12(%ebp)  #dzielnik
    pushl 16(%ebp) #reszta_z_dzielenia      #BLAD !!!!!!!!!!!!!!!!!---------
call porownaj2Liczby#eax=0 rowne, eax=1 pierwsza wieksza, eax=2 druga wieksza
    addl $12, %esp
    cmpl $2, %eax
    je wiekszy#wiekszy dzielnik
    #dzielnik mniejszy -> odejmij,wynik+1, przeskaluj
    pushl %ecx  #odejmowanie wykorzystuje ecx
    pushl 20(%ebp)  #rozmiar argumentow
    pushl 16(%ebp)  #adres wyniku
    pushl 12(%ebp)  #adres 2 arg
    pushl 16(%ebp)  #adres 1 arg
    call odejmij    #arg1-arg2      #modyfikuje rejestry
    addl $16, %esp
    popl %ecx
    movl 24(%ebp), %edi
    addl $1, (%edi)
    decl %ecx
    pushl 20(%ebp)  #rozmiar argumentow
    pushl 12(%ebp)  #adres dzielnika
    call przesunBityWPrawo
    addl $8, %esp
    jmp odejmuj_kolejne
 
    wiekszy:
    pushl 20(%ebp)  #rozmiar argumentow
    pushl 12(%ebp)  #adres dzielnika
    call przesunBityWPrawo
    addl $8, %esp
    decl %ecx
    jmp odejmuj_kolejne
    koniec_odejmuj_kolejne:
    #Ostatni odejmowanie bez przesuwania dzielnika
    pushl 20(%ebp)  #rozmiar
    pushl 24(%ebp)  #wynik dzielenia
    call przesunBityWLewo  
    addl $8, %esp
    pushl 20(%ebp) #rozmiar argumentow
    pushl 12(%ebp)  #dzielnik
    pushl 16(%ebp) #reszta_z_dzielenia     
    call porownaj2Liczby#eax=0 rowne, eax=1 pierwsza wieksza, eax=2 druga wieksza
    addl $12, %esp
    cmpl $2, %eax
    je koniec_dzielenia #wiekszy dzielnik
    #dzielnik mniejszy -> odejmij,wynik+1
    pushl %ecx  #odejmowanie wykorzystuje ecx
    pushl 20(%ebp)  #rozmiar argumentow
    pushl 16(%ebp)  #adres wyniku
    pushl 12(%ebp)  #adres 2 arg
    pushl 16(%ebp)  #adres 1 arg
    call odejmij    #arg1-arg2      #modyfikuje rejestry
    addl $16, %esp
    popl %ecx
    movl 24(%ebp), %edi
    addl $1, (%edi)
    decl %ecx
    koniec_dzielenia:
popl %edi
popl %ebx
movl %ebp ,%esp
popl %ebp
ret
.type modulo2, @function
modulo2:
	pushl %ebp
	movl %esp,%ebp
	movl 8(%ebp), %edi
	movl (%edi), %eax
	andl $1, %eax
	movl %ebp, %esp
	popl %ebp
	ret
# adres 1 liczby, adres 2 liczby, rozmiar argumentow
#funckja zwraca 1 jezeli pierwsza liczba wieksza, 0 w przeciwnym razie 
.type czyArg1WiekszyOdArg2, @function
czyArg1WiekszyOdArg2:
    pushl %ebp
    movl %esp, %ebp  
    pushl %edx
    pushl %edi
    pushl %ecx
    movl 8(%ebp), %edx  #adres 1 liczby
    movl 12(%ebp), %edi #adres 2 liczby
    movl 16(%ebp), %ecx #rozmiar argumentow
    decl %ecx      
    __sprawdzaj_wszystkie:
    cmpl $0, %ecx  
    jl __koniec_sprawdzaj_wszystkie
    movl (%edx,%ecx,4), %eax
    cmpl (%edi,%ecx,4), %eax
    ja __pierwsza_wieksza
    jb __koniec_sprawdzaj_wszystkie
    decl %ecx
    jmp __sprawdzaj_wszystkie
    __koniec_sprawdzaj_wszystkie:
    movl $0, %eax           
    jmp __koniec_porownywania
    __pierwsza_wieksza:
    movl $1, %eax           #zwraca 1 gdy pierwsza wieksza
    __koniec_porownywania:
    popl %ecx
    popl %edi
    popl %edx
    movl %ebp, %esp
    popl %ebp
ret
.type czyArg1RownyArg2, @function
czyArg1RownyArg2:
    pushl %ebp
    movl %esp, %ebp  
    pushl %edx
    pushl %edi
    pushl %ecx
    movl 8(%ebp), %edx  #adres 1 liczby
    movl 12(%ebp), %edi #adres 2 liczby
    movl 16(%ebp), %ecx #rozmiar argumentow 
    decl %ecx      
    _sprawdzaj_wszystkie:
    cmpl $0, %ecx  
    jl _koniec_sprawdzaj_wszystkie
    movl (%edx,%ecx,4), %eax
    cmpl (%edi,%ecx,4), %eax
    jne nie_rowne
    decl %ecx
    jmp _sprawdzaj_wszystkie
    _koniec_sprawdzaj_wszystkie:
    movl $1, %eax           
    jmp _koniec_porownywania
    nie_rowne:
    movl $0, %eax           #zwraca 1 gdy pierwsza wieksza
    _koniec_porownywania:
    popl %ecx
    popl %edi
    popl %edx
    movl %ebp, %esp
    popl %ebp
ret


