#include <iostream>
#include "TournamentTable.h"
#include "GroupStage.h"


Team enterData();
void simulationGame();
int whoPlay();
//int countStat();
void saveTable(std::vector<Team>* h);
std::vector<Team>* loadTable();
std::vector<Team> Table;

int main()
{
	TournamentTable r;
	/*r.createTable();
	r.printFunc();
	simulationGame();
	r.printFunc();*/
	Qualification q;
	q.fillTable();
	q.groupPlay(2);
	system("pause");

}

Team  enterData() //Procedyra zapolneniya
{
  TournamentTable z;
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
  z.sumPoints(r);
  z.countDifference(r);
  return r;
}

 void simulationGame() //Procedyra igri
	{
		TournamentTable r;
		Team g;
		r.clearStruct(&g);
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
        std::cout<<"Who won?(0....n): ";
		std::cin>>res;

		if(res == t1)
		{
			r.clearStruct(&g);
			g.Played++;
			g.Win++;
			std::cout<<"Goals for (1): ";
			std::cin>>g.GoalsFor;
			std::cout<<"GoalsAgainst (1): ";
			std::cin>>g.GoalsAgainst;
			r.changeSit(&g,&t1); //out of range

			

			if(res != t2)
			{
            r.clearStruct(&g);
            g.Played++;
			g.Loose++;
			std::cout<<"Goals for (2): ";
			std::cin>>g.GoalsFor;
			std::cout<<"GoalsAgainst (2): ";
			std::cin>>g.GoalsAgainst;
			r.changeSit(&g,&t2);

			}
		}

		if(res == t2)
		{
			r.clearStruct(&g);
			g.Played++;
			g.Win++;
			std::cout<<"Goals for (2): ";
			std::cin>>g.GoalsFor;
			std::cout<<"GoalsAgainst (2): ";
			std::cin>>g.GoalsAgainst;
			r.changeSit(&g,&t2);
			

			if(res != t1)
			{
            r.clearStruct(&g);
            g.Played++;
			g.Loose++;
			std::cout<<"Goals for (1): ";
			std::cin>>g.GoalsFor;
			std::cout<<"GoalsAgainst (1): ";
			std::cin>>g.GoalsAgainst;
			r.changeSit(&g,&t1);

			}
		}

		if(res != t1 || res != t2) //Draw
			{
            r.clearStruct(&g);
            g.Played++;
			g.Draw++;
			std::cout<<"Goals for (1): ";
			std::cin>>g.GoalsFor;
			std::cout<<"GoalsAgainst (1): ";
			std::cin>>g.GoalsAgainst;
			r.changeSit(&g,&t1);
			if(res != t1 || res != t2)
			{
            r.clearStruct(&g);
            g.Played++;
			g.Draw++;
			std::cout<<"Goals for (2): ";
			std::cin>>g.GoalsFor;
			std::cout<<"GoalsAgainst (2): ";
			std::cin>>g.GoalsAgainst;
			r.changeSit(&g,&t2);

			}

			}


	}

 void saveTable(std::vector<Team> *h) //Help with table
 {
	 Table = *h;
 }
 std::vector<Team>* loadTable() //Help with table
 {
	 return(&Table);
 }