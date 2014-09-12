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

	for(int t=0; t<=5; )
	{
	result=sum+(sum/100*p);
	t++;
	}
	printf("result",result);
	system ("pause");
	//Проблемы с переменной в которой хранится сумма каждый год,к ней должный суммироватся проценты и от нее расчитываться.


}
