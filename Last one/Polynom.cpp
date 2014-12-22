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
		Polynom r;
		newdata=data;
		size_t pSize = p.data.size();
		size_t size  = data.size();
		size_t pMaxPow = pSize-1;
		size_t MaxPow = size-1;
		size_t max = size*pSize;
		r.data.resize(max);
		for ( size_t i=0; i < r.data.size(); ++i )
			r.data[i]=0;



		for(size_t i = MaxPow; i > pMaxPow; --i)
		{
			r.data[i - pMaxPow] = newdata[i]/p.data[pMaxPow];
			newdata = r.data[i - pMaxPow]*p.data;
		}
		
		
		 
		

			

		
			


		
















		return r;
	}

bool Polynom::operator == (const Polynom & p) const
{
	if ( p.data.size() != data.size() )
		false;
	for ( size_t i =0; i < data.size(); ++i )
		if ( data[i] != p.data[i] ) return false;
	return true;
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

void Polynom::setKey( double k) //Znachenie STEPENI
	{
		key=k;
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
