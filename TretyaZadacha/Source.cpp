#include <iostream>
using namespace std;

//Length
int Rasriad(int enterNumber);

//Input 2 numbers,
//Sort digits to get maxim num
//Output max num
//Shkolnikov Fedor 13501/4
int main()
{
   int FirstNumber,
	   SecondNumber,
	   FirstNumLength,
	   SecondNumLength,
	   Digit,
	   Decimal1=1,
       Decimal2=1;

   int  *DigitStr1,
        *DigitStr2,
        *Res;
		
   bool Length=false;

   cout << "Enter First Number: ";
   cin >> FirstNumber;
   cout << "Enter Second Number: ";
   cin >> SecondNumber;

   FirstNumLength = Rasriad(FirstNumber);
   SecondNumLength = Rasriad(SecondNumber);
   DigitStr1 = new int[FirstNumLength];
   DigitStr2 = new int[SecondNumLength];



   //Matchin arrays
   for(int j = 1; j < FirstNumLength; j++)
      Decimal1 *= 10;
   for(int i = 0; i < FirstNumLength; i++)
   {
	   Digit = FirstNumber / Decimal1 % 10;
	   DigitStr1[i] = Digit; 
      Decimal1 /= 10;
   }

  for(int j = 1; j < SecondNumLength; j++)
      Decimal2 *= 10;
   for(int i = 0; i < SecondNumLength; i++)
   {
	   Digit = SecondNumber / Decimal2 % 10;
	   DigitStr2[i] = Digit; 
      Decimal2 /= 10;
   }



   if (FirstNumLength>SecondNumLength)
   {
	   Res = new int[FirstNumLength];
	   for(int i=0;i<FirstNumLength;i++)
		   if (DigitStr1[i]>DigitStr2[i])
		   {
			  Res[i]+ DigitStr1[i];
		   }
		   else
		   {
			   Res[i]=DigitStr2[i];
		   }
		   Length=true;
   }
   else
   {
	   Res = new int[SecondNumLength];

	   for (int i = 0; i < SecondNumLength; i++)
	   {
		   if (DigitStr1[i]>DigitStr2[i])
		   {
			   Res[i]=DigitStr1[i];
		   }
		   else
		   {
			   Res[i]=DigitStr2[i];
		   }
	   }
   }
   if (Length)
   {
	   for (int i = 0; i < FirstNumLength; i++)
	   {
		   cout<<Res[i];
	   }
   }
   else
   {
	   for (int i = 0; i < SecondNumLength; i++)
	   {
		   cout<<Res[i];
	   }
   }

cout<<endl;
system("pause");
return 0;
}

int Rasriad(int enterNumber)
{
   int n = enterNumber, x = 0;
   while (n != 0) 
   {
      n /= 10;
      x++;
     }
   return x;
}