#include <stdio.h>
#include <stdlib.h>
int main (void)
{
	int result,sum;
	float z,y,p;
	printf("Enter sum: ");
	scanf("%d",&sum);
	printf("Enter percents: ");
	scanf("%f",&p);
	z=sum;
	y=0;

	for (int t=0 ; t<=5;)
	{
		result=((z/100)*p);
        z=z+result;   
	t++;
	}
	printf("rusult %f \n",z);
	system ("pause");
}
