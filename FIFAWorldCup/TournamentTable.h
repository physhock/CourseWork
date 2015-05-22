#pragma once
#include <string>
#include <vector>
#include <algorithm>


struct Team
	{
		std::string name;
		int 
	    Played,
		Win,
		Draw,
		Loose,
		GoalsFor,
		GoalsAgainst,
		Difference,
		Points;

	};

Team r;

class TournamentTable
{
   private:
		
	std::vector<Team> TableString;
	friend Team enterData();
	friend void simulationGame();
	friend void saveTable(std::vector<Team>* h);
	friend std::vector<Team>* loadTable();

   public:

	TournamentTable():TableString(0) {};
    ~TournamentTable() {};

	Team sumPoints(Team)
	{
		int w,d;
		w = 0;
		d = 0;
		w = r.Win;
		d = r.Draw;		
		r.Points = (w*3) + d;
		return r;
	}

	Team countDifference(Team)
	 {
		 int f,a;
		 f = 0;
		 a = 0;
		 f = r.GoalsFor;
		 a = r.GoalsAgainst;
		 r.Difference = f - a;
		 return r;
	 }

	void createTable() //Zapolnyaem
	{
		//int t = 0;
		//std::cout<<"Enter 1 if it play-off stage, or 0 if it group stage: "; 
		//std::cin>>t;
		//if(t!=0)
		//{
		//	TableString.resize(15);
		//	for(int i = 0; i <= 15; i++)
		//	{
		//		TableString.resize(15);
		//		enterData();
		//		TableString[i] = r;
		//	}
		//	sort(TableString);
		//	for(int i = 0; i < 2; i++)//Just 4 test
		//	{
		//		enterData();
		//		TableString[i] = r;
		//	}
		//	
		//}
		//else
		//{
		//	
		//}
	 //  

		TableString.resize(31);
			for (int i = 0; i <= 31; i++)
			{
				
				enterData();
				TableString[i] = r;
			}

		saveTable(&TableString);

	}

	static bool compare(const Team& a, const Team& b) //Compare funktor
    {
		if (a.Points == b.Points)
		{
			if (a.Difference == b.Difference)
			{
				return(a.GoalsFor > b.GoalsFor);
			}
		
			return (a.Difference > b.Difference);
		}
		else
		{
			return (a.Points > b.Points);
		}
		
    }

	void sort(std::vector<Team>)  //Sort 
	{

		std::sort(TableString.begin(), TableString.end(), &TournamentTable::compare);

	}
	
	void changeSit(Team *h,int* t) //Main event sim
	{
		TableString = *loadTable();
		Team a;
		Team b;
		a = *h;
		b = TableString[*t];
		r.name = b.name;
		r.GoalsAgainst = a.GoalsAgainst + b.GoalsAgainst;
		r.GoalsFor = a.GoalsFor + b.GoalsFor;
		r.Played = a.Played + b.Played;
		r.Loose = a.Loose + b.Loose;
		r.Draw = a.Draw + b.Draw;
		r.Win = a.Win + b.Win;
		sumPoints(r);
		countDifference(r);
		TableString[*t] = r;
		sort(TableString);
		saveTable(&TableString);
	}
	
	 void printFunc() //Trash (4print)
	 {
		 TableString = *loadTable();
		 for (int i = 0; i < TableString.size(); i++)
		 {
			 r = TableString[i];
			 std::cout<<"Mesto:"<<(i+1)<<"  "<<r.name<<" Played:"<<r.Played<<" Points:"<<r.Points<<"\n";
		 }
	 }

	 void clearStruct(Team* h)
	 {
		 Team r;
		 r.name  = "default";
		 r.Difference = 0;
		 r.Draw = 0;
		 r.GoalsAgainst = 0;
		 r.GoalsFor = 0;
		 r.Loose = 0;
		 r.Played = 0;
		 r.Points = 0;
		 r.Win = 0;
		 *h = r;
		 
	 }
	
};


