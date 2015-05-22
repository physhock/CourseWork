#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <string>
#include "TournamentTable.h"

std::vector<Team> qualTop;//First teams table

std::vector<Team> qualSec;//Second place teams

class Qualification
{
	private:

		std::vector<Team> QualificationGroup;
		std::vector<std::vector<Team>> QualificationTable;

    public:

	Qualification():QualificationTable(0) {};
	~Qualification() {};

	std::vector<Team> fillGroup()
	{
		QualificationGroup.resize(4);
		
		for (int i = 0; i < 4; i++)
		{
			enterData();
			QualificationGroup[i] = r;
		}

		return QualificationGroup;
		
	}

	void fillTable()
	{
		QualificationTable.resize(3);//8

		for (int i = 0; i < 3; i++)//8
		{
			fillGroup();
			QualificationTable[i] = QualificationGroup;
		}
	}

	void unpackTeams()
	{
		for (int i = 0; i < QualificationTable.size(); i++)
		{
			QualificationGroup = QualificationTable[i];
			QualificationGroup[0] = qualTop[i];

		}
		for (int i = 0; i < QualificationTable.size(); i++)
		{
			QualificationGroup = QualificationTable[i];
			QualificationGroup[1] = qualSec[i];
		}
	}

	void groupPlay(int n)//Prinimaet nomer grypu v kotory igra
	{

		 *loadTable() = QualificationTable[n]; //Теперь группа у нас в Table
		 simulationGame();
		 QualificationTable[n] = *loadTable();
	}

};
