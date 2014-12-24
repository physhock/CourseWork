#include "Polynom.h"
#include <iostream>

static void testFunction();

//Реализовать класс многочлен.
//Школьников Фёдор, 13501/4
//Размещение начинается с x^0, отсутствующие коэффиценты следует заполнить нулями.
//В деление к сожалению не успел вернуть остаток, он содерижится в Polynom a)
int main()
{
	setlocale(LC_ALL,"Russia");
	testFunction();
	system("pause");
}

static void testFunction() //TEST
	{
		Polynom a;
		std::vector<double> v1; 
		v1.push_back(-42);
		v1.push_back(0);
		v1.push_back(-12);
		v1.push_back(1);
		a.setData(v1);

		Polynom b;
		std::vector<double> v2;
		v2.push_back(-3);
		v2.push_back(1);
		//v2.push_back(5);
		//v2.push_back(7);
		b.setData(v2);


		Polynom testSum1;		
		std::vector<double> v3;
		v3.push_back(10);
		v3.push_back(9);
		v3.push_back(15);
		v3.push_back(21);
		testSum1.setData(v3);

		


		std::cout << "#########   *   ############"  << std::endl; 
		Polynom m = a * b;
		std::cout 
			<< "m = a * b " << std::endl 
			<< " a = " << a.toString() << std::endl 
			<< " b = " << b.toString() << std::endl 
			<< " m = " << m.toString() << std::endl;

		std::cout << "#########   /   ############"  << std::endl; 
		Polynom d = a / b;
		std::cout 
			<< "d = a / b " << std::endl 
			<< " a = " << a.toString() << std::endl 
			<< " b = " << b.toString() << std::endl 
			<< " d = " << d.toString() << std::endl;

		std::cout << "#########   +   ############"  << std::endl; 
		Polynom s = a + b;
		std::cout 
			<< "s = a + b " << std::endl 
			<< " a = " << a.toString() << std::endl 
			<< " b = " << b.toString() << std::endl 
			<< " s = " << s.toString() << std::endl;

		std::cout << "#########   -   ############"  << std::endl; 
		Polynom r = a - b;
		std::cout 
			<< "r = a - b " << std::endl 
			<< " a = " << a.toString() << std::endl 
			<< " b = " << b.toString() << std::endl 
			<< " r = " << r.toString() << std::endl;
	}

