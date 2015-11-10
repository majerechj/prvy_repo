// uloha-5-1.c -- Tyzden 5 - Uloha 1
// Juraj Majerech, 18.10.2015 16:43:37

#include <stdio.h>



void vypis(FILE *podujatia)
{
  
  
	
	char a;
    int deti;
    double cena, datum, cas;
      

	

  	printf("nazov: ");
   	while (feof(podujatia)==0)
  	 {
    
	    
		while (a=getc(podujatia),a!='\n') printf("%c",a);
		printf("\norganizator: ");
		while (a=getc(podujatia),a!='\n') printf("%c",a);
  		printf("\npre deti: ");
  		fscanf(podujatia,"%d\n",&deti);
        printf("%d",deti);
      
      	printf("\ncena: ");
		fscanf(podujatia,"%lf\n",&cena);
        printf("%.2lf",cena);
      
  		printf("\ndatum: ");
		fscanf(podujatia,"%lf\n",&datum);
        printf("%08.0lf",datum);
      
  		printf("\ncas: ");
    	fscanf(podujatia,"%lf\n",&cas);
        printf("%.2lf",cas);
        getc(podujatia);
    	if (feof(podujatia)==0) printf("\n\nnazov: ");
 	 }
	
}


void cas(FILE *podujatia)
{
   rewind(podujatia);
	char a;
    int riadok=0, deti=0,rok,i;
    double cas,vyslednycas=0,vyslednyrok=0;
  
    while (a=getc(podujatia), feof(podujatia)==0)
    	{
    	if (a=='\n') riadok++;
     	if (riadok==2){ if ((a=getc(podujatia))==1) deti=1; else deti =0;}
      	if (riadok==4){for(i=1;i<=4;i++) a=getc(podujatia); fscanf(podujatia,"%d",&rok); } 
        if (riadok==5) fscanf(podujatia,"%lf",&cas);
      	if (riadok==6)
      		{	
        	if (deti=1 && rok==vyslednyrok && cas>=vyslednycas) vyslednycas=cas;
          	if (deti=1 && rok>vyslednyrok) {vyslednycas=cas; vyslednyrok=rok;}
        	}
      	if (riadok==7) riadok=0;
    	}
  printf("\n%.2lf",vyslednycas);
}



int main()
{
   	FILE *podujatia;
    int i,otvoreny=0;
  
    if((podujatia = fopen("NASOBKY.TXT", "r")) == NULL)
 	printf("Neotvoreny subor\n");
  
	char pismeno;
 // for (i=1;i<=2;i++) {
	scanf("%c",&pismeno);
  	if (pismeno=='v') {vypis(podujatia); otvoreny=1;}
	//if (pismeno=='c' && otvoreny==1) 
 // }
  	cas(podujatia);
  
    fclose(podujatia);	
  	return 0;
}
