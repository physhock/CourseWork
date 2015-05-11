#include <iostream>
#include "TournamentTable.h"

//struct Team
//	{
//		std::string name;
//		int
//	    Played,
//		Win,
//		Draw,
//		Loose,
//		GoalsFor,
//		GoalsAgainst,
//		Difference,
//		Points;
//
//	};
int main()
{
	
  /*std::vector<Team> TableString;*/ //Elements of this vector will make a full sport table 0,1...n strings of
  //team info
  /*Team r;
  r.Difference = 0;
  r.Draw = 0;
  r.GoalsAgainst =0;
  r.GoalsFor = 0;
  r.Loose = 0;
  r.Loose = 0;
  r.Played = 0;
  r.Points = 0;
  r.Win = 0;
  std::cout<<"Enter Team name: ";
  std::cin>>r.name;
  std::cout<<"\n";
  std::cout<<"Enter Team win: ";
  std::cin>>r.Win;
  TableString.push_back(r);*/

	TournamentTable r;
	r.createTable();
	r.saveFunc();
	system("pause");

}