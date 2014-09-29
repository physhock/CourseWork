#include <stdio.h>
#include <stdlib.h>
int main ()
{
	int a,b,l1,w1,l2,w2;
	printf("Area length: ");
	scanf_s("%d",&a);
	printf("Area width: ");
	scanf_s("%d",&b);
	printf("First house lenght: ");
	scanf_s("%d",&l1);
	printf("First house width: ");
	scanf_s("%d",&w1);
	printf("Second house length: ");
	scanf_s("%d",&l2);
	printf("Second house width: ");
	scanf_s("%d",&w2);
	//Schitali

	if(l1+l2<a && w1<b && w2<b)
		printf("Doma po dlinne\n");
	else if (w1+w2<b && l1<a && l2<a)
		printf("Doma vlezli po shirine\n");
	else if (l1+w2<b && l2<a && w1<a) //povorachivaem po dlinne
		printf("Povernyli dom po dlinne\n");
	else if (l2+w1<b && l1<a && w2<a) // povorachivaem po shirine
		printf("Povernyli dom po shirine\n");
	else if(l1+l2<b && w1<a && w2<a) //povernyli oba doma
		printf("Oba doma po dlinne");
	else if(w1+w2<a && l1<b && l2<b)//povernyli oba doma
		printf("Povernyli doma po dlinne\n");
	else
		printf("Doma ne vlezli");
	system("pause");
	return 0;
}