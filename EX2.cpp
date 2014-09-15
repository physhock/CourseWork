#include <stdio.h>
#include <stdlib.h>
int main (void)
{
	int sq,sq1,sq2,a,b,p,q,r,s;
	printf("Enter area length: ");
	scanf("%d",&a);
	printf("Enter area width: ");
	scanf("%d",&b);
	printf("House1 length: ");
	scanf("%d",&p);
	printf("House1 width: ");
	scanf("%d",&q);
	printf("House2 length: ");
	scanf("%d",&r);
	printf("House2 width: ");
	scanf("%d",&s);
	sq=a*b;
	sq1=p*q;
	sq2=r*s;



	if (a<p)
		printf("Not enough space\n");
	else if (b<q)
		printf("Not enough space\n");



	if (a<r)
		printf("Not enough space\n");
	else if (b<s)
		printf("Not enough space\n");

	if(sq<(sq1+sq2))
		printf("Not enough space\n");
	else
printf("Its OK\n");



system("pause");
}
