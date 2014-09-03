#include <stdio.h>
#include <stdlib.h>
int main (void)
{
	int result,sum;
	float p;
	printf("Enter sum: ");
	scanf("%d",&sum);
	printf("Enter percents: ");
	scanf("%f",&p);
	result=sum+((sum/100*p)*5);
		printf("Result 5y =%d \n",result);
	system("pause");
	return 0;
}
