#pragma once

#include <string>
#include<vector>
#include <sstream>
#include <iostream>

//Class opisivaushiy polinom
class Polynom
{
	
public:
    
	
	Polynom()   {}; //Constructor nylevogo
	
	Polynom( std::vector<double>& d, double k) // Konstructor
	{
		setData(d);
	}
	Polynom (const Polynom & p) // operator COPPY
	{
		data = p.data;
	}
	virtual ~Polynom(){}; // Destructor

	

	Polynom Polynom::operator + (const Polynom & p); // operator slozgheniya

	Polynom Polynom::operator - (const Polynom & p); //Operator vichit

	Polynom Polynom::operator * (const Polynom &p ) const; // Operator ymnozgha

	Polynom Polynom::operator / (const Polynom &p); // Operator delena

    Polynom & operator = (const Polynom & p) //Operator prisvaivaniya
	{
		data=p.data;
		return *this;
	}
	
	std::string toString () const
	{
		std::stringstream s;
		
		for ( size_t i = 0; i < data.size(); ++i )
		{
			s << data[i] << "x^" << i;
			if (i < (data.size() -1) )
			{
			   s<<"+";
			}
		}
		return s.str();
	}

	void  Polynom::setData( std::vector<double>& d); // zapolnyaem

	void Polynom::setData( size_t index, double value);

	static void testFunction(); // ETO TEST

	double Polynom::calcValue( int x); // shcitaem po x


	


private:

	std::vector<double> data;
};



