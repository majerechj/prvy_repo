// uloha-5-1.c -- Tyzden 5 - Uloha 1
// Juraj Majerech, 18.10.2015 16:43:37

#include <stdio.h>



void vypis()
{
	FILE *podujatia;
	char a;
    int deti;
    double cena, datum, cas;
      
  
	if((podujatia = fopen("NASOBKY.TXT", "r")) == NULL)
   printf("Neotvoreny subor\n");

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
	fclose(podujatia);	
}


int main()
{
	char pismeno;
	scanf("%c",&pismeno);
	if (pismeno=='v') vypis();
	return 0;
}
