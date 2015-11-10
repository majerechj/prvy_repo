
// Juraj Majerech

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


//pomocna funkcia na vyratanie dlzky cisla 
int dlzkaCisla(double a) {
    long int x,i=0;
    x=a/1;
//delim 10 dokym cislo nieje nula, kolko krat vydelim, taka je jeho dlzka  
  while (x>0)
  	{
    x=x/10;
    i++;
  	}
      
 return i;        
}

void vypis(FILE *podujatia)
{
	char a;
    int deti;
    double cena, datum, cas;
      
   	rewind(podujatia);
//nacitavam a hned vypisujem údaje zo súboru
  	
   	while (feof(podujatia)==0)
  	 {
       	//názov
      	printf("nazov: ");
		while (a=getc(podujatia),a!='\n') printf("%c",a);
		
      	//organizátor
      	printf("\norganizator: ");
		while (a=getc(podujatia),a!='\n') printf("%c",a);
  		
      	//pre deti?
      	printf("\npre deti: ");
  		fscanf(podujatia,"%d\n",&deti);
        printf("%d",deti);
       	
      	//cena
      	printf("\ncena: ");
		fscanf(podujatia,"%lf\n",&cena);
        printf("%.2lf",cena);
       	
      	//datum
  		printf("\ndatum: ");
		fscanf(podujatia,"%lf\n",&datum);
        printf("%08.0lf",datum);
      	
      	//cas podujatia
  		printf("\ncas: ");
    	fscanf(podujatia,"%lf\n",&cas);
        printf("%.2lf\n\n",cas);
       
    	
 	 }
	
}

// vo funkcii som nepouzil pole, pretoze je to zbytocne zaberanie pamate
void cas(FILE *podujatia)
{
   rewind(podujatia);
	char a;
    int riadok=0, deti=0,rok,i;
    double cas,vyslednycas=-1,maxRok=-1,pomRok;
/*prechadzam subor po riadkoch, zapamätávam si cas, rok a informaciu ci je
podujatie pre deti,

na konci kazdého podujatia vyhodnotím, či to je podujatie pre deti s najneskorsím rokom,
najneskorsim casom. Ak áno, zapamatam si to v premennych vyslednyCas, pomRok.

na konci funkcie vypisem najneskorsi cas pre deti v poslednom roku. Ak existuje.*/  
    while (a=getc(podujatia), feof(podujatia)==0)
    	{
    	if (a=='\n') riadok++;
     	if (riadok==2){ if ((a=getc(podujatia))=='1') deti=1; else deti =0;}
      	if (riadok==4)
        	{
          	for(i=1;i<=4;i++) a=getc(podujatia); 
          	fscanf(podujatia,"%d",&rok); 
        	} 
        if (riadok==5) fscanf(podujatia,"%lf",&cas);
      	if (riadok==5)
      		{	
            if (maxRok<=rok) maxRok=rok;  	
         	if (deti==1 && rok==maxRok && cas>=vyslednycas) {vyslednycas=cas; pomRok=rok;}
          	if (deti==0 && rok==maxRok && maxRok!=pomRok) {vyslednycas=-1;}          	 
        	}
      	if (riadok==7) riadok=0;
    	}
  if (vyslednycas>=0) printf("%.2lf\n",vyslednycas);
}

/* Vo funkcí vytvorím pole (x), prechádzam súbor a postupne zvacsujem pole(realloc)
a naplnam pole cenami.

výsledné pole vraciam do funkcie MAIN*/
double *epole(FILE *podujatia,int *n)
{
  rewind(podujatia);
  char a;
  double *x;
  int riadok=0, i=-1;
  x = malloc(sizeof(double)); 
  while (a=getc(podujatia), feof(podujatia)==0)
    	{
    	if (a=='\n') riadok++;
    	if (riadok==3) 
			{
          	i++;
          	x = realloc(x, (i+1)*sizeof(double));
          	fscanf(podujatia,"%lf",&x[i]);
          	
			
        	}
    
    	if (riadok==7) riadok=0;
    	}
  *n=i;
  return x;
 
}

/*Najskor zistim v prvom for cykle najvacsiu dlzku cisla z pomedzi cisiel z pola.
pomáha mi k tomu pomocná funkcia dlzka cisla, ktorá vracia dlzku základu reálneho cisla

potom zistujem kolko medzier budem vypisovat pred jednotlive cisla.
pocet medzier = maximalna dlzka cisla z pola - dlzka aktualneho cisla
nakoniec vypíšem cislo a odriadkujem. opakujem n krát, pricom n je velkost pola.*/
void VypisPole(double *x, int n)
{
 int i,j,max=0;
  for (i=0;i<=n;i++) 
  	{ 
    if(dlzkaCisla(x[i])>=max) max=dlzkaCisla(x[i]);
    }

  for (i=0;i<=n;i++) {
	for (j=1;j<=(max-dlzkaCisla(x[i]));j++) printf(" ");
    printf("%.2lf\n",x[i]);
    
  
  }
  
}



/*vytvorim pole desiatich integerov, ktoré bude predstavovat moj histogram.
na zaciatku funkcie ho vynulujem.
index pola predstavuje danú cislicu.
preto si zoberiem cislo z pola a 	cislo MODULO 10 = cislica 
inkrementujem pocet danej cislice prikazom histogram[cislo%10]++

na konci funkcie histogram vypisem v tvare: cislica(index pola) : pocet cislic*/
void Histogram(double *x, int n)
{
  int i, histogram[10];
  long int cislo;
  
  for (i=0;i<=9;i++) histogram[i]=0;
  for (i=0;i<=n;i++)
  	{
    cislo=x[i];
    do	{
    histogram[cislo%10]++;
    cislo=cislo/10;        
    	}
  	while(cislo!=0);
  	}    
  for (i=9;i>=0;i--) printf("%d:%d\n",i,histogram[i]);
}


/* Na usporiadanie pola vyuzivam bublinkove triedenie.*/
void UsporiadaniePola(double *x,int n)
{
  double pom;
  int i,j;
  
for (i=1;i<=n;i++)
	{
  	for (j=0;j<=n-i;j++)
  		{
      	if (x[j]<x[j+1]) 
        	{
        	pom = x[j];
            x[j] = x[j+1];
            x[j+1] = pom;
        	}
    	}
	}
} 



void organizator(FILE *podujatia)
{
  rewind(podujatia);
  char a, *organizatori[3];
  int riadok=0, *org, i=-1,ktory,j,max,tento,k,kolkoOrg,pocet,vyslednyPocet[3];
  

/* V tomto cykle prechádzam súbor. vždy sledujem položku organizátor (riadok 1, 
ak cislujem riadky od 0)
Spocitam kolko samohlasok ma jednotlivy organizator a zapisem do pola org, ktore samozrejme
rozsirujem behom cyklu, podla poctu organizatorov
Vysledkom cyklu je naplnene pole s poctom samohlasok jednotlivych organizatorov.*/  
  org = malloc(sizeof(int));
  org[0]=0;
  while (a=getc(podujatia), feof(podujatia)==0)
    	{
    	if (a=='\n') riadok++;
    	if (riadok==1) 
			{
			i++;
            org = realloc(org, (i+1)*sizeof(int));          
            org[i]=0;
          	while (a=getc(podujatia), a!='\n')
          		{if (a=='a' || a=='e' || a=='i' || a=='o' || a=='u' || a=='y' || a=='A' ||a=='E' ||a=='I' || a=='O' || a=='U' || a=='Y' ) 
          	 	 org[i]++;
                
           		}
          if(a=='\n') riadok++;
        	}
    
    	if (riadok==7) riadok=0;
    	}
//ifom osetrim pocet organizatorov, aby sa program nemylil a nevypisoval niektoreho viac krat  
if (i<=2) kolkoOrg=i; else kolkoOrg=2; 
/*Cyklus bude opakovane vyhladavat organizatora s najvacsim poctom samohlasok.
Ked ho najde, zapamata si ho do pola "organizatori" a vymaze ho z pola "org"(kde si pamata pocet samohlasok),
aby mohol nájst druheho (...tretieho..) organizatora. Opakuje maximalne 3 krat alebo závisle
od počtu organizatorov v subore.*/  
for (k=0;k<=kolkoOrg;k++)
	{
	ktory=0;  	
  	max=org[0];
/*prechadzam pole a zistujem maximalny pocet samohlasok. zapamatam si ho(premenna max) 
  a zapamatam si aj index pola(premenna ktory) */
  	for (j=0;j<=i;j++)
  		{
    	if (max<org[j]) {max=org[j]; ktory=j;}
   		}
  	rewind(podujatia);
  	riadok=0;
  	tento=-1;
  
/*Vdaka premennym "ktory" a "max" viem zistit ktoreho organizatora v subore hladam. 
Je na pozicii "ktory" a má "max" samohlasok.
Zvacsujem pole "organizatori" do ktoreho zapisem organizatora s najvacsim poctom samohlasok.
Jeho pocet samohlasok zapisujem od pola "vyslednyPocet"*/  
  	while (a=getc(podujatia), feof(podujatia)==0)
    	{  
    		if (a=='\n') 					
    		{
      			riadok++;
    			if (riadok==1) 
					{  
					tento++;
            		if (tento==ktory)
            			{
              			//printf("\n");
                        pocet=0;
                        organizatori[k] = malloc(sizeof(char));
                     	while (a=getc(podujatia), a!='\n') 
                        	{
                          	organizatori[k] = realloc(organizatori[k], (pocet+1)*sizeof(char));
                       	 	organizatori[k][pocet]=a; 
                          	pocet++;
                        	}          				
                      	organizatori[k] = realloc(organizatori[k], (pocet+1)*sizeof(char));
                       	organizatori[k][pocet]=':';
                      	/*teraz musim tohto organizatora z pola "org" vymazat, 
						aby som mohol zistit druheho (tretieho...)*/
                      	org[ktory]=0;
                      	vyslednyPocet[k]=max;
              			};             
        			}
  			}
   			if (riadok==7) riadok=0;
  		}
	}
//vypis organizatorov a ich pocet samohlasok.  
for (k=0;k<=kolkoOrg;k++) 
	{
	printf("%s",organizatori[kolkoOrg-k]);
    printf("%d\n",vyslednyPocet[kolkoOrg-k]);
	}
  
}







int main()
{
   	FILE *podujatia;
    int otvoreny=0,n=-1,vytvorene=0; /*"otvoreny"-premenna ktora hovori ci je subor otvoreny
    								   "vytvorene" - hovori ci je pole uz vytvorene*/
    double *pole;
	char pismeno;
 /*nacitava znaky na vstupe, dokym nenacita k. Pismeno k ukonci program.*/ 
  while(scanf("%c",&pismeno), pismeno!='k')
  {
  	if (pismeno=='v') 
    	{
      	if (otvoreny != 1) 
        	{
        	if((podujatia = fopen("podujatia.txt", "r")) == NULL) printf("Neotvoreny subor\n");
        	}
      else 	{/*ak je "v" stlacene znovu, zavrie subor a otvori ho znovu*/
      		fclose(podujatia);
        	if((podujatia = fopen("podujatia.txt", "r")) == NULL) printf("Neotvoreny subor\n");
      		}
      	vypis(podujatia); 
      	otvoreny=1;
    	}
	if (pismeno=='c' && otvoreny==1) cas(podujatia);
	if (pismeno=='e' && otvoreny==1) 
    	{
      	if (n>-1) free(pole); /* toto je dealokacia pola, ak uz bolo vytvorene.*/
      	pole = epole(podujatia,&n);
      	vytvorene=1;
    	}
    if (pismeno=='r' && otvoreny==1 && vytvorene==1) VypisPole(pole,n);
    if (pismeno=='r' && vytvorene!=1) printf("Pole nie je vytvorene\n");
    if (pismeno=='h' && otvoreny==1 && vytvorene==1) Histogram(pole,n);
    if (pismeno=='h' && vytvorene!=1) printf("Pole nie je vytvorene\n");
  	if (pismeno=='z' && otvoreny==1 && vytvorene==1) UsporiadaniePola(pole,n);
    if (pismeno=='s' && otvoreny==1) organizator(podujatia);
  
   	
  }
  if (otvoreny==1) fclose(podujatia);
    return 0;
}
