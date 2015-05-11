#pragma once
#include <string>
#include<vector>
#include <algorithm>

class TournamentTable
{
   private:
		
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
	std::vector<Team> TableString;

   public:
	
	TournamentTable():TableString(0) {};
    ~TournamentTable() {};
	friend int main();
	Team  setData() //Procedyra zapolneniya
{
  std::cout<<"Enter Team name: ";
  std::cin>>r.name;
  std::cout<<"\n";
  std::cout<<"Enter games played: ";
  std::cin>>r.Played;
  std::cout<<"\n";
  std::cout<<"Enter games win: ";
  std::cin>>r.Win;
  std::cout<<"\n";
  std::cout<<"Enter games draw: ";
  std::cin>>r.Draw;
  std::cout<<"\n";
  std::cout<<"Enter games loose: ";
  std::cin>>r.Loose;
  std::cout<<"\n";
  std::cout<<"Enter goals for: ";
  std::cin>>r.GoalsFor;
  std::cout<<"\n";
  std::cout<<"Enter goals against: ";
  std::cin>>r.GoalsAgainst;
  std::cout<<"\n";
  sumPoints(r);
  countDifference(r);
  return r;
}

	Team sumPoints(Team)
	{
		int w,l,d;
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

	void createTable()
	{
		int t = 0;
		std::cout<<"Enter 1 if it play-off stage, or 0 if it group stage: ";
		std::cin>>t;
		if(t!=0)
		{
			/*for(int i = 0; i <= 15; i++)
			{
				TableString.resize(15);
				setData();
				TableString[i] = r;
			}*/
			for(int i = 0; i < 3; i++)//Just 4 test
			{
				TableString.resize(3);
				setData();
				TableString[i] = r;
			}
			sort(TableString);
		}
		else
		{
			for (int i = 0; i <= 31; i++)
			{
				TableString.resize(31);
				setData();
				TableString[i] = r;
			}
		}
		
	}

	void sort(std::vector<Team>)  //Sort TableString Points
	{
		std::sort(TableString.begin(), TableString.end(), [](Team &a, Team &b) { return a.Points > b.Points; });

	}
	/*void myCompare(Team1,Team2)
	{
		if(Team1.Points = Team2.Points)
		{
			if(Team1.Difference > Team2.Difference)
			{
				TableString[Team1] higher 
			}
			else
			{
				TableString[Team2] higher
			}
		}
		else if (Team1.Points > Team2.Points)
		{
			TableString[Team1] higher
		}
		else
		{
			TableString[Team2] higher
		}
		
	}
	*/
	 void simulationGame() //Procedyra igri
	{
		int t1,t2,res;
		t1 = 0;
		t2 = 0;
		res = 0;
		std::cout<<"Enter 1 team played(0...n): ";//Index in the vector of strurct
		std::cin>>t1;
		std::cout<<"\n";
		std::cout<<"Enter 2 team played(0...n): ";
		std::cin>>t2;
		std::cout<<"\n";
        std::cout<<"Who won?(0....n)";
		std::cin>>res;
		if (res=t1)
		{
			
		}


	}
	

	
};


