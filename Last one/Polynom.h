#pragma once

#include <string>
#include<vector>
#include <sstream>
#include <iostream>

//Class opisivaushiy polinom
class Polynom
{
	
public:
    
	
	Polynom()   { key = 0.0;}; //Constructor nylevogo
	
	Polynom( std::vector<double>& d, double k) // Konstructor
	{
		setData(d);
		setKey(k);
	}
	Polynom (const Polynom & p) // operator COPPY
	{
		data = p.data;
		key = p.key;
	}
	virtual ~Polynom(){}; // Destructor

	
	
	Polynom Polynom::operator + (const Polynom & p); // operator slozgheniya

	Polynom Polynom::operator - (const Polynom & p); //Operator vichit

	Polynom Polynom::operator * (const Polynom &p ) const; // Operator ymnozgha

	Polynom Polynom::operator / (const Polynom &p); // Operator delena

    Polynom & operator = (const Polynom & p) //Operator prisvaivaniya
	{
		key=p.key;
		data=p.data;
		return *this;
	}
	
	bool operator == (const Polynom & p) const;

	 std::string toString () const
	{
		std::stringstream s;
		
		for ( size_t i = 0; i < data.size(); ++i )
			s << data[i] << "x^" << i  << " + ";
		return s.str();
	}

	void  Polynom::setData( std::vector<double>& d); // zapolnyaem

	void Polynom::setData( size_t index, double value);

	void Polynom::setKey( double k); //Znachenie STEPENI

	static void testFunction(); // ETO TEST

	double Polynom::calcValue( int x); // shcitaem po x


	


private:
    
    double key; 
	std::vector<double> data;
	std::vector<double> newdata;
};



