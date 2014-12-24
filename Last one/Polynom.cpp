#include "Polynom.h"
#include <iostream>



Polynom Polynom::operator + (const Polynom & p) // operator slozgheniya
	{
		Polynom r;
		size_t pSize = p.data.size();
		size_t size  = data.size();
		for(size_t i=0; i < std::max(pSize,size); ++i)
		{
			if ( i < pSize && i < size )
				r.data.push_back(data[i] + p.data[i]);
			else if ( i < pSize )
				r.data.push_back(p.data[i]);
			else 
				r.data.push_back(data[i]);
		}

		return r;
	}

Polynom Polynom::operator - (const Polynom & p) //Operator vichit
	{
		Polynom r;
		size_t pSize = p.data.size();
		size_t size  = data.size();
		for(size_t i=0; i < std::min(pSize,size); i++ )
		{
			r.data.push_back(data[i] - p.data[i]);
		}
		if (pSize != size)
		{
			for (size_t i = std::min(pSize,size); i<std::max(pSize,size); i++ )
			{
				if(size<pSize)
				{
					r.data.push_back(-p.data[i]);
				}
				else
				{
					r.data.push_back(data[i]);
				}
			}
		}

		return r;
	}

Polynom Polynom::operator * (const Polynom &p ) const // Operator ymnozgha
	{
		Polynom r;
		size_t pSize = p.data.size();
		size_t size  = data.size();
		size_t max = (pSize+size)-1;

		/*index= 0  1  2  3
		---------------
		A = 1x^0 + 2x^1 + 4x^2 + 8x^3
		B = 3x^0 + 5x^1 + 7x^2  +9x^3

		C = A*B;
			 0    1		2	3	4 ...
		------------------------
		C =  1*3x^0 + 1*5x^1 + 1*7x^2 + 1*9x^3 + 2*3x^1 + 2*5x^2 + 2*7x^3 + 2*9x^4 + 4*3x^2 + 4*6x^3 + 4*7x^4

		r.data[0]= ?

		     
		1*3+1*5+1*7+1*9+2*3+*2*5

		x0 * 1*3 + x1 * 1*5 + x*/

		r.data.resize(max);
		for ( size_t i=0; i < r.data.size(); ++i )
			r.data[i]=0;


		for ( size_t i = 0; i < data.size(); ++i )
			for ( size_t j =0; j < p.data.size(); ++j)
			{
				r.data[i+j] += data[i] * p.data[j];
			}

		return r;
	}

Polynom Polynom::operator / (const Polynom &p) // Operator delena
	{
		Polynom a,b,r,res1,res2,odnochlen;

		size_t pSize = p.data.size();
		size_t size  = data.size();
		size_t max = size*pSize;
		size_t mPow = pSize-1;
		size_t maxPow = size-1;
	
		a.data.resize(size,0);
		b.data.resize(size,0);
		res1.data.resize(size,0);
		res2.data.resize(size,0);
		odnochlen.data.resize(size,0);

		a.data = data;
		b.data = p.data;



		for(size_t i = maxPow; i >= mPow; --i)
	  {

		  res1.data[i-mPow] = a.data[i]/b.data[mPow];
		  odnochlen.data[i-mPow] = res1.data[i-mPow];
		  res2 = b * odnochlen;
		  a = a - res2;
		  //Obnylyau
		  for ( size_t i=0; i < res2.data.size(); ++i )
			  res2.data[i]=0;
		  for ( size_t i=0; i < odnochlen.data.size(); ++i )
			  odnochlen.data[i]=0;

	  }

		r = res1;
		return r;

		//###################### a/b

	  /*
	  Polynom a;
	  a.data.push_back(0);
	  a.data.push_back(1);
	  a.data.push_back(1);
	  a.data.push_back(1);
	  a.data.push_back(0);
	  a.data.push_back(0);
	  a.data.push_back(1);

        Polynom b;	  
	    b.data.push_back(1);
		b.data.push_back(1);
		b.data.push_back(0);
		b.data.push_back(1);

	Polynom odnochlen1;
	Polynom odnochlen2;
	Polynom odnochlen3;
	Polynom odnochlen4;

	Polynom res1;
	Polynom res2;
	Polynom res3;
	Polynom res4;

	Polynom result;
 

	Polynom sum  = a +b;
	Polynom dif  = a*  b + b + b + a;
	Polynom di2f = dif - a; 

	//Polynom mul  = a*  b * sum;



	result.data.resize(a.data.size(),0);

	 //should be a.size() instead of max
	res1.data.resize(a.data.size(),0);
	odnochlen1.data.resize(a.data.size(),0);
	res2.data.resize(a.data.size(),0);
	odnochlen2.data.resize(a.data.size(),0);
	res3.data.resize(a.data.size(),0);
	odnochlen3.data.resize(a.data.size(),0);
	res4.data.resize(a.data.size(),0);
	odnochlen4.data.resize(a.data.size(),0);

	result.data[6-3] = a.data[6]/b.data[3];
	odnochlen1.data[6-3] = result.data[6-3];
	res1 = odnochlen1 * b;
	a = a - res1;


	result.data[5-3] = a.data[5]/b.data[3];
	odnochlen2.data[5-3] = result.data[5-3];
	res2 = odnochlen2 * b;
	a = a - res2;



    result.data[4-3] = a.data[4]/b.data[3];
	odnochlen3.data[4-3] = result.data[4-3];
	res3 = odnochlen3 * b;
	a = a - res3;


	result.data[3-3] = a.data[3]/b.data[3];
	odnochlen4.data[3-3] = result.data[3-3];
	res4 = odnochlen4 * b;
	a = a - res4;
*/
	
	}

void  Polynom::setData( std::vector<double>& d) // zapolnyaem
	{
		data=d;
	}

void Polynom::setData( size_t index, double value)
	{
		if ( data.size() > index )
			data[index]=value;
	}

double Polynom::calcValue( int x) // shcitaem po x
	{
		double total = 0.0;

		for ( size_t i=0; i < data.size(); ++i)
		{
			double xx = pow(x,i);
			total += data[i]*xx;
		}
		return total;
	}
