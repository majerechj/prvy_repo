#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

void vypis()
{
FILE *podujatia;
char a;

podujatia = ("podujatia.txt","r");
printf("nazov:");
while (a=getc(podujatia), a!='\n')
	{
		printf("a");
	}

	
}


int main(int argc, char *argv[])
{
	char pismeno;
	scanf("%c",pismeno);
	if (pismeno=='v') vypis();
	return 0;
}
