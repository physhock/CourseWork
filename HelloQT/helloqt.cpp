#include <QMessageBox>
#include <QDebug>
#include <QSettings>
#include "helloqt.h"



const size_t maxGroup = 8;
const size_t maxRowsInGroup = 4;


const QString teamName = "teamName";
const QString gamesPlayed =  "gamesPlayed";
const QString ballsDiff = "ballsDiff";
const QString points = "points";
const QString score = "score";
QStringList fields;
QStringList allGroups;




HelloQT::HelloQT(QWidget *parent)
	: QMainWindow(parent)
{
	
	fields<<teamName<<gamesPlayed<<ballsDiff<<points;
	allGroups<<""<<"A"<<"B"<<"C"<<"D"<<"E"<<"F"<<"G"<<"H";

	ui.setupUi(this);
	connect ( ui.startSimulationButton, SIGNAL(clicked()), this, SLOT (slotStartSimulationButtonHandler()) );	
	connect ( ui.applyDataButton, SIGNAL(clicked()), this, SLOT (slotClearGroupResults()) );
	connect(ui.startPlayOffStageButton ,SIGNAL(clicked()), this, SLOT(slotStartPlayOffStageButton()));

	connect ( ui.cbSimulate01Group, SIGNAL(currentIndexChanged(int)), this, SLOT (slotSimulation01GroupChanged(int)) );
	ui.cbSimulate01Group->insertItems(0,allGroups);

	connect ( ui.cbSimulate01Team1, SIGNAL(currentIndexChanged(int)), this, SLOT (slotSimulate01Team1Changed(int)) );
	connect ( ui.cbSimulate01Team2, SIGNAL(currentIndexChanged(int)), this, SLOT (slotSimulate02Team2Changed(int)) );
	
	connect ( ui.startSimulationPlayOffStage18Button, SIGNAL(clicked()), this, SLOT (slotStartSimulationPlayOffStage18Button()) );
	connect ( ui.startSimulationPlayOffStage14Button, SIGNAL(clicked()), this, SLOT (slotStartSimulationPlayOffStage14Button()) );
	connect ( ui.startSimulationPlayOffStage12Button, SIGNAL(clicked()), this, SLOT (slotStartSimulationPlayOffStage12Button()) );
	connect ( ui.startSimulationPlayOffStage11Button, SIGNAL(clicked()), this, SLOT (slotStartSimulationPlayOffStage11Button()) );
	connect ( ui.saveTeamsButton, SIGNAL(clicked()), this, SLOT (slotSaveTeamsButton()) );
	connect ( ui.loadTeamsButton, SIGNAL(clicked()), this, SLOT (slotLoadTeamsButton()) );


	foreach (QLineEdit* le, this->findChildren<QLineEdit*>(QRegularExpression("score*")) )
	{
		QIntValidator *val = new QIntValidator(0,99,le);
		le->setValidator(val);
	}


	clearGroupResults();
}

HelloQT::~HelloQT()
{
	
}

void HelloQT::clearGroupResults()
{
	ui.cbSimulate01Group->setCurrentIndex(0);
	ui.cbSimulate01Team1->clear();
	ui.cbSimulate01Team2->clear();
	ui.score01->setText("");
	ui.score02->setText("");

	allGames.clear();
	for ( int g = 0; g < maxGroup; ++g )
	{
		for ( int r = 0; r < maxRowsInGroup; ++r )
		{
			for (int f = 0 ; f < fields.size(); ++f )
			{
				QString objectName = getObjectName(g,r,fields[f]);
				QLineEdit* le = getFieldForGroup(g, r,fields[f]);
				if ( !le )
				{		
					qDebug() << objectName << " NOT Found ";
				}
				else if ( fields[f] == teamName )
					le->setText(objectName);
				else
					le->setText("0");
			}
		}
	}
}

QString HelloQT::getObjectName(int group, int posInGroup, QString fieldName)
{
	QString objectName = QString("%1_%2%3").arg(fieldName).arg(group).arg(posInGroup);
	return objectName;
}

QLineEdit* HelloQT::getFieldForGroup(int group, int posInGroup, QString fieldName)
{
	QString objectName = getObjectName(group,posInGroup,fieldName);
	QLineEdit* le = this->findChild<QLineEdit*>(objectName);
	return le;
}

QString HelloQT::getFieldValue(QString objectName)
{
	QLineEdit* le = this->findChild<QLineEdit*>(objectName);
	return le->text();
}

void HelloQT::setFieldValue (int group, int posInGroup, QString fieldName, QString value)
{
	QLineEdit* le = getFieldForGroup(group,posInGroup,fieldName);
	le->setText(value);

}

void HelloQT::setFieldValue (int group, int posInGroup, QString fieldName, int value)
{
	setFieldValue (group, posInGroup,fieldName, QString::number(value));
}

QString  HelloQT::getFieldValue(int group, int posInGroup, QString fieldName) 
{
	QLineEdit* le = getFieldForGroup(group,posInGroup,fieldName);
	return le->text();
}


void  HelloQT::setFieldValue(QString objectName,QString value)
{
	QLineEdit* le = this->findChild<QLineEdit*>(objectName);
	le->setText(value);
}

inline bool compareTeamData(const TeamData& a, const TeamData& b) //Compare funktor
{
	if (a.points == b.points)
	{			
		
		return (a.ballsDiff > b.ballsDiff);
	}
	else
	{
		return (a.points > b.points);
	}		
}

Group HelloQT::getGroupData(int group)
{
	Group g;
	
	
	for(int i = 0; i < maxRowsInGroup; ++i)
	{
		TeamData r;
		r.name = getFieldValue(group,i, teamName);
		r.gamesCount = getFieldValue(group,i, gamesPlayed ).toShort();
		r.ballsDiff = getFieldValue(group,i, ballsDiff ).toShort();
		r.points = getFieldValue(group,i, points ).toShort();
		g.push_back(r);
	}

	return g;
}

QList<TeamData> HelloQT::getGroupData()
{
	QList<TeamData> group;

	for (int g = 0; g < maxGroup; g++)
	{

	
	for(int i = 0; i < maxRowsInGroup; ++i)
	{
		TeamData r;
		r.name = getFieldValue(g,i, teamName);
		r.gamesCount = getFieldValue(g,i, gamesPlayed ).toShort();
		r.ballsDiff = getFieldValue(g,i, ballsDiff ).toShort();
		r.points = getFieldValue(g,i, points ).toShort();
		group << r;
	}

	}

	return group;
}

void HelloQT::setGroupData(int group,Group data)
{
	for(int i = 0; i < maxRowsInGroup; ++i)
	{
		setFieldValue(group,i, teamName,data[i].name);
		setFieldValue(group,i, gamesPlayed,data[i].gamesCount);
		setFieldValue(group,i, ballsDiff,data[i].ballsDiff);
		setFieldValue(group,i, points,data[i].points);

	}
}
 
void HelloQT::setAllGroupData(QList<TeamData> data)
{

	std::map<int, std::vector<TeamData>> allTeams = splitTeams(data);;
	for ( int i=0; i < maxGroup; ++i)
	{
		setGroupData(i,allTeams[i]);
	}	
}

std::map<int, std::vector<TeamData>> HelloQT::splitTeams(QList<TeamData> data)
{
	std::map<int, std::vector<TeamData>> teamsMap;

	for ( int i =0; i < data.size(); ++i )
	{
		size_t groupIndex =  i/maxRowsInGroup;
		teamsMap[groupIndex].push_back(data[i]);
	}
	return teamsMap;
}

void HelloQT::slotStartSimulationButtonHandler()
{
	QString team01 = ui.cbSimulate01Team1->currentText();
	QString team02= ui.cbSimulate01Team2->currentText();

	QString score01 = ui.score01->text();
	QString score02 = ui.score02->text();

	if ( team01.isEmpty() )
	{
		QMessageBox::warning(this,"Invalid data","Unknown 1 team");
		return;
	}

	if ( team02.isEmpty() )
	{
		QMessageBox::warning(this,"Invalid data","Unknown 2 team");
		return;
	}

	if ( team01 == team02  )
	{
		QMessageBox::warning(this,"Invalid data","Same team selected");
		return;
	}

	bool ok01 = false;
	bool ok02 = false;
	int iScore01 = score01.toUShort(&ok01);
	int iScore02 = score02.toUShort(&ok02);
	if ( !ok01 || !ok01 )
	{
		QMessageBox::warning(this,"Invalid data","Invalid score");
		return;
	}



	int group = ui.cbSimulate01Group->currentIndex()-1;
	if ( group < 0 ) return;

	AllGames_t::iterator groupIt = allGames.find(group);
	if ( groupIt != allGames.end() )
	{
		std::pair <std::multimap<QString,QString>::iterator, std::multimap<QString,QString>::iterator> ret 
			= groupIt->second.equal_range(team01);
		for (std::multimap<QString,QString>::iterator it=ret.first; it!=ret.second; ++it)
			if ( it->second == team02)
			{
				QMessageBox::warning(this,"Invalid data","Teams already played");
				return;
			}

		ret	= groupIt->second.equal_range(team02);
		for (std::multimap<QString,QString>::iterator it=ret.first; it!=ret.second; ++it)
			if ( it->second == team01)
			{
				QMessageBox::warning(this,"Invalid data","Teams already played");
				return;
			}
	}
	else 
	{
		GroupGames_t t;
		allGames[group]=t;
	}



	int teamIndex01 =  ui.cbSimulate01Team1->currentIndex()-1;
	int teamIndex02 =  ui.cbSimulate01Team2->currentIndex()-1;

	Group g  =  getGroupData(group);
	
	for ( int i =0; i < g.size(); ++i )
	{
		if ( g[i].name == team01 )
		{
			g[i].gamesCount++;
			g[i].ballsDiff += iScore01-iScore02;
			if ( iScore01 == iScore02) 
				g[i].points += 1;
			else if ( iScore01 > iScore02) 
				g[i].points += 3;
		}
		else if ( g[i].name == team02 )
		{
			g[i].gamesCount++;
			g[i].ballsDiff += iScore02-iScore01;
			if ( iScore01 == iScore02) 
				g[i].points += 1;
			else if ( iScore02 > iScore01) 
				g[i].points += 3;
		} 
	}

	std::sort(g.begin(),g.end(),compareTeamData);

	setGroupData(group,g);

	ui.cbSimulate01Group->setCurrentIndex(0);
	ui.cbSimulate01Team1->clear();
	ui.cbSimulate01Team2->clear();
	ui.score01->setText("");
	ui.score02->setText("");


	allGames[group].insert(std::pair<QString,QString>(team01,team02));

}

void  HelloQT::slotClearGroupResults()
{
	clearGroupResults();
}

void HelloQT::slotSimulation01GroupChanged(int group)
{
	ui.cbSimulate01Team1->clear();
	ui.cbSimulate01Team2->clear();
	if  ( group == 0 )
	{		
		return;
	}
	group--;
	QStringList groupTeams = getTeamsForGroup(group);
	groupTeams.prepend("");
	ui.cbSimulate01Team1->insertItems(0,groupTeams);
	ui.cbSimulate01Team2->insertItems(0,groupTeams);

}

QStringList HelloQT::getTeamsForGroup(int group)
{
	QStringList groupTeams;		
	for(int i = 0; i < maxRowsInGroup; ++i)
	{
		QString tn  = getFieldValue(group,i, teamName );
		groupTeams<<tn;
	}

	return groupTeams;
}

void HelloQT::slotStartPlayOffStageButton()
{
	Group h;
	TeamData r;
	bool ok = true;

	for ( int g = 0; g < maxGroup; ++g )
	{
		h = getGroupData(g);

		for (int i = 0; i < maxRowsInGroup; i++)
		{
			r = h[i];

			if (r.gamesCount!=3)
			{
				ok = false;
			}
		}
	}
	
	if (!ok)
	{
		QMessageBox::warning(this,"Invalid data","NOT enough games played");
	}
	else
	{
		goToPlayOff();
	}
		
}

void HelloQT::slotStartSimulationPlayOffStage18Button()
{
	
		
	
		QString t00 = getFieldValue(QString("%1_%2_%3%4").arg(teamName).arg(18).arg(0).arg(0));
		QString t01 = getFieldValue(QString("%1_%2_%3%4").arg(teamName).arg(18).arg(0).arg(1));
		QString s00 = getFieldValue(QString("%1_%2_%3%4").arg(score).arg(18).arg(0).arg(0));
		QString s01 = getFieldValue(QString("%1_%2_%3%4").arg(score).arg(18).arg(0).arg(1));
		s01.toInt();
		s00.toInt();

		if (s00>s01)
		{
			setFieldValue(QString("%1_%2_%3%4").arg(teamName).arg(14).arg(0).arg(0),t00);
		}
		
	
		else
		{
			setFieldValue(QString("%1_%2_%3%4").arg(teamName).arg(14).arg(0).arg(0),t01);
		}
		
		QString t10 = getFieldValue(QString("%1_%2_%3%4").arg(teamName).arg(18).arg(1).arg(0));
		QString t11 = getFieldValue(QString("%1_%2_%3%4").arg(teamName).arg(18).arg(1).arg(1));
		QString s10 = getFieldValue(QString("%1_%2_%3%4").arg(score).arg(18).arg(1).arg(0));
		QString s11 = getFieldValue(QString("%1_%2_%3%4").arg(score).arg(18).arg(1).arg(1));
		s10.toInt();
		s11.toInt();

		if (s10>s11)
		{
			setFieldValue(QString("%1_%2_%3%4").arg(teamName).arg(14).arg(0).arg(1),t10);
		}
		
	
		else
		{
			setFieldValue(QString("%1_%2_%3%4").arg(teamName).arg(14).arg(0).arg(1),t11);
		}

		QString t20 = getFieldValue(QString("%1_%2_%3%4").arg(teamName).arg(18).arg(2).arg(0));
		QString t21 = getFieldValue(QString("%1_%2_%3%4").arg(teamName).arg(18).arg(2).arg(1));
		QString s20 = getFieldValue(QString("%1_%2_%3%4").arg(score).arg(18).arg(2).arg(0));
		QString s21 = getFieldValue(QString("%1_%2_%3%4").arg(score).arg(18).arg(2).arg(1));
		s20.toInt();
		s21.toInt();

		if (s20>s21)
		{
			setFieldValue(QString("%1_%2_%3%4").arg(teamName).arg(14).arg(1).arg(0),t20);
		}
		
	
		else
		{
			setFieldValue(QString("%1_%2_%3%4").arg(teamName).arg(14).arg(1).arg(0),t21);
		}

		QString t30 = getFieldValue(QString("%1_%2_%3%4").arg(teamName).arg(18).arg(3).arg(0));
		QString t31 = getFieldValue(QString("%1_%2_%3%4").arg(teamName).arg(18).arg(3).arg(1));
		QString s30 = getFieldValue(QString("%1_%2_%3%4").arg(score).arg(18).arg(3).arg(0));
		QString s31 = getFieldValue(QString("%1_%2_%3%4").arg(score).arg(18).arg(3).arg(1));
		s30.toInt();
		s31.toInt();

		if (s30>s31)
		{
			setFieldValue(QString("%1_%2_%3%4").arg(teamName).arg(14).arg(1).arg(1),t30);
		}
		else
		{
			setFieldValue(QString("%1_%2_%3%4").arg(teamName).arg(14).arg(1).arg(1),t31);
		}

		QString t40 = getFieldValue(QString("%1_%2_%3%4").arg(teamName).arg(18).arg(4).arg(0));
		QString t41 = getFieldValue(QString("%1_%2_%3%4").arg(teamName).arg(18).arg(4).arg(1));
		QString s40 = getFieldValue(QString("%1_%2_%3%4").arg(score).arg(18).arg(4).arg(0));
		QString s41 = getFieldValue(QString("%1_%2_%3%4").arg(score).arg(18).arg(4).arg(1));
		s41.toInt();
		s40.toInt();

		if (s40>s41)
		{
			setFieldValue(QString("%1_%2_%3%4").arg(teamName).arg(14).arg(2).arg(0),t40);
		}
		
	
		else
		{
			setFieldValue(QString("%1_%2_%3%4").arg(teamName).arg(14).arg(2).arg(0),t41);
		}

		QString t50 = getFieldValue(QString("%1_%2_%3%4").arg(teamName).arg(18).arg(5).arg(0));
		QString t51 = getFieldValue(QString("%1_%2_%3%4").arg(teamName).arg(18).arg(5).arg(1));
		QString s50 = getFieldValue(QString("%1_%2_%3%4").arg(score).arg(18).arg(5).arg(0));
		QString s51 = getFieldValue(QString("%1_%2_%3%4").arg(score).arg(18).arg(5).arg(1));
		s51.toInt();
		s50.toInt();

		if (s50>s51)
		{
			setFieldValue(QString("%1_%2_%3%4").arg(teamName).arg(14).arg(2).arg(1),t50);
		}
		
	
		else
		{
			setFieldValue(QString("%1_%2_%3%4").arg(teamName).arg(14).arg(2).arg(1),t51);
		}

		QString t60 = getFieldValue(QString("%1_%2_%3%4").arg(teamName).arg(18).arg(6).arg(0));
		QString t61 = getFieldValue(QString("%1_%2_%3%4").arg(teamName).arg(18).arg(6).arg(1));
		QString s60 = getFieldValue(QString("%1_%2_%3%4").arg(score).arg(18).arg(6).arg(0));
		QString s61 = getFieldValue(QString("%1_%2_%3%4").arg(score).arg(18).arg(6).arg(1));
		s61.toInt();
		s60.toInt();

		if (s60>s61)
		{
			setFieldValue(QString("%1_%2_%3%4").arg(teamName).arg(14).arg(3).arg(0),t60);
		}
		
	
		else
		{
			setFieldValue(QString("%1_%2_%3%4").arg(teamName).arg(14).arg(3).arg(0),t61);
		}

		QString t70 = getFieldValue(QString("%1_%2_%3%4").arg(teamName).arg(18).arg(7).arg(0));
		QString t71 = getFieldValue(QString("%1_%2_%3%4").arg(teamName).arg(18).arg(7).arg(1));
		QString s70 = getFieldValue(QString("%1_%2_%3%4").arg(score).arg(18).arg(7).arg(0));
		QString s71 = getFieldValue(QString("%1_%2_%3%4").arg(score).arg(18).arg(7).arg(1));
		s71.toInt();
		s70.toInt();

		if (s70>s71)
		{
			setFieldValue(QString("%1_%2_%3%4").arg(teamName).arg(14).arg(3).arg(1),t70);
		}
		
	
		else
		{
			setFieldValue(QString("%1_%2_%3%4").arg(teamName).arg(14).arg(3).arg(1),t71);
		}
	
			

			
			

	
		//1-2 => 00
		//3-4 => 01
		//5-6 => 10
		//7-8 => 11
		//setFieldValue (QString("%1_%2_%3%4").arg(teamName).arg(14).arg(0));		
		
			/*QMessageBox::warning (this,"Invalid data", "Wrong score/teams for group "+ QString::number(i+1));*/
	
}

void HelloQT::slotStartSimulationPlayOffStage14Button()
{
		QString t00 = getFieldValue(QString("%1_%2_%3%4").arg(teamName).arg(14).arg(0).arg(0));
		QString t01 = getFieldValue(QString("%1_%2_%3%4").arg(teamName).arg(14).arg(0).arg(1));
		QString s00 = getFieldValue(QString("%1_%2_%3%4").arg(score).arg(14).arg(0).arg(0));
		QString s01 = getFieldValue(QString("%1_%2_%3%4").arg(score).arg(14).arg(0).arg(1));
		s01.toInt();
		s00.toInt();

		if (s00>s01)
		{
			setFieldValue(QString("%1_%2_%3%4").arg(teamName).arg(12).arg(0).arg(0),t00);
		}
		
	
		else
		{
			setFieldValue(QString("%1_%2_%3%4").arg(teamName).arg(12).arg(0).arg(0),t01);
		}

		QString t10 = getFieldValue(QString("%1_%2_%3%4").arg(teamName).arg(14).arg(1).arg(0));
		QString t11 = getFieldValue(QString("%1_%2_%3%4").arg(teamName).arg(14).arg(1).arg(1));
		QString s10 = getFieldValue(QString("%1_%2_%3%4").arg(score).arg(14).arg(1).arg(0));
		QString s11 = getFieldValue(QString("%1_%2_%3%4").arg(score).arg(14).arg(1).arg(1));
		s11.toInt();
		s10.toInt();

		if (s10>s11)
		{
			setFieldValue(QString("%1_%2_%3%4").arg(teamName).arg(12).arg(0).arg(1),t10);
		}
		
	
		else
		{
			setFieldValue(QString("%1_%2_%3%4").arg(teamName).arg(12).arg(0).arg(1),t11);
		}

		QString t20 = getFieldValue(QString("%1_%2_%3%4").arg(teamName).arg(14).arg(2).arg(0));
		QString t21 = getFieldValue(QString("%1_%2_%3%4").arg(teamName).arg(14).arg(2).arg(1));
		QString s20 = getFieldValue(QString("%1_%2_%3%4").arg(score).arg(14).arg(2).arg(0));
		QString s21 = getFieldValue(QString("%1_%2_%3%4").arg(score).arg(14).arg(2).arg(1));
		s21.toInt();
		s20.toInt();

		if (s20>s21)
		{
			setFieldValue(QString("%1_%2_%3%4").arg(teamName).arg(12).arg(1).arg(0),t20);
		}
		
	
		else
		{
			setFieldValue(QString("%1_%2_%3%4").arg(teamName).arg(12).arg(1).arg(0),t21);
		}

		QString t30 = getFieldValue(QString("%1_%2_%3%4").arg(teamName).arg(14).arg(3).arg(0));
		QString t31 = getFieldValue(QString("%1_%2_%3%4").arg(teamName).arg(14).arg(3).arg(1));
		QString s30 = getFieldValue(QString("%1_%2_%3%4").arg(score).arg(14).arg(3).arg(0));
		QString s31 = getFieldValue(QString("%1_%2_%3%4").arg(score).arg(14).arg(3).arg(1));
		s31.toInt();
		s30.toInt();

		if (s30>s31)
		{
			setFieldValue(QString("%1_%2_%3%4").arg(teamName).arg(12).arg(1).arg(1),t30);
		}
		
	
		else
		{
			setFieldValue(QString("%1_%2_%3%4").arg(teamName).arg(12).arg(1).arg(1),t31);
		}
}

void HelloQT::slotStartSimulationPlayOffStage12Button()
{
		QString t00 = getFieldValue(QString("%1_%2_%3%4").arg(teamName).arg(12).arg(0).arg(0));
		QString t01 = getFieldValue(QString("%1_%2_%3%4").arg(teamName).arg(12).arg(0).arg(1));
		QString s00 = getFieldValue(QString("%1_%2_%3%4").arg(score).arg(12).arg(0).arg(0));
		QString s01 = getFieldValue(QString("%1_%2_%3%4").arg(score).arg(12).arg(0).arg(1));
		s01.toInt();
		s00.toInt();

		if (s00>s01)
		{
			setFieldValue(QString("%1_%2_%3%4").arg(teamName).arg(11).arg(0).arg(0),t00);
			setFieldValue(QString("%1_%2_%3%4").arg(teamName).arg(33).arg(0).arg(0),t01);
		}
		
	
		else
		{
			setFieldValue(QString("%1_%2_%3%4").arg(teamName).arg(11).arg(0).arg(0),t01);
			setFieldValue(QString("%1_%2_%3%4").arg(teamName).arg(33).arg(0).arg(0),t00);
		}

		QString t10 = getFieldValue(QString("%1_%2_%3%4").arg(teamName).arg(12).arg(1).arg(0));
		QString t11 = getFieldValue(QString("%1_%2_%3%4").arg(teamName).arg(12).arg(1).arg(1));
		QString s10 = getFieldValue(QString("%1_%2_%3%4").arg(score).arg(12).arg(1).arg(0));
		QString s11 = getFieldValue(QString("%1_%2_%3%4").arg(score).arg(12).arg(1).arg(1));
		s11.toInt();
		s10.toInt();

		if (s10>s11)
		{
			setFieldValue(QString("%1_%2_%3%4").arg(teamName).arg(11).arg(0).arg(1),t10);
			setFieldValue(QString("%1_%2_%3%4").arg(teamName).arg(33).arg(0).arg(1),t11);
		}
		
	
		else
		{
			setFieldValue(QString("%1_%2_%3%4").arg(teamName).arg(11).arg(0).arg(1),t11);
			setFieldValue(QString("%1_%2_%3%4").arg(teamName).arg(33).arg(0).arg(1),t10);
		}
}

void HelloQT::slotStartSimulationPlayOffStage11Button()
{
		QString t00 = getFieldValue(QString("%1_%2_%3%4").arg(teamName).arg(11).arg(0).arg(0));
		QString t01 = getFieldValue(QString("%1_%2_%3%4").arg(teamName).arg(11).arg(0).arg(1));
		QString s00 = getFieldValue(QString("%1_%2_%3%4").arg(score).arg(11).arg(0).arg(0));
		QString s01 = getFieldValue(QString("%1_%2_%3%4").arg(score).arg(11).arg(0).arg(1));
		s01.toInt();
		s00.toInt();

		if (s00>s01)
		{
			setFieldValue(QString("%1%2").arg(teamName).arg(1),t00);
			setFieldValue(QString("%1%2").arg(teamName).arg(2),t01);
		}
		
	
		else
		{
			setFieldValue(QString("%1%2").arg(teamName).arg(1),t01);
			setFieldValue(QString("%1%2").arg(teamName).arg(2),t00);
		}

		QString t10 = getFieldValue(QString("%1_%2_%3%4").arg(teamName).arg(33).arg(0).arg(0));
		QString t11 = getFieldValue(QString("%1_%2_%3%4").arg(teamName).arg(33).arg(0).arg(1));
		QString s10 = getFieldValue(QString("%1_%2_%3%4").arg(score).arg(33).arg(0).arg(0));
		QString s11 = getFieldValue(QString("%1_%2_%3%4").arg(score).arg(33).arg(0).arg(1));
		s11.toInt();
		s10.toInt();

		if (s10>s11)
		{
			setFieldValue(QString("%1%2").arg(teamName).arg(3),t10);
		}
		
	
		else
		{
			setFieldValue(QString("%1%2").arg(teamName).arg(3),t11);
		}
}

void HelloQT::goToPlayOff()
{

			
			setFieldValue(QString("%1_%2_%3%4").arg(teamName).arg(18).arg(0).arg(0),getFieldValue(QString("%1_%2%3").arg(teamName).arg(0).arg(0)));
			setFieldValue(QString("%1_%2_%3%4").arg(teamName).arg(18).arg(0).arg(1),getFieldValue(QString("%1_%2%3").arg(teamName).arg(1).arg(1)));
			setFieldValue(QString("%1_%2_%3%4").arg(teamName).arg(18).arg(1).arg(0),getFieldValue(QString("%1_%2%3").arg(teamName).arg(2).arg(0)));
			setFieldValue(QString("%1_%2_%3%4").arg(teamName).arg(18).arg(1).arg(1),getFieldValue(QString("%1_%2%3").arg(teamName).arg(3).arg(1)));
			setFieldValue(QString("%1_%2_%3%4").arg(teamName).arg(18).arg(2).arg(0),getFieldValue(QString("%1_%2%3").arg(teamName).arg(4).arg(0)));
			setFieldValue(QString("%1_%2_%3%4").arg(teamName).arg(18).arg(2).arg(1),getFieldValue(QString("%1_%2%3").arg(teamName).arg(5).arg(1)));
			setFieldValue(QString("%1_%2_%3%4").arg(teamName).arg(18).arg(3).arg(0),getFieldValue(QString("%1_%2%3").arg(teamName).arg(6).arg(0)));
			setFieldValue(QString("%1_%2_%3%4").arg(teamName).arg(18).arg(3).arg(1),getFieldValue(QString("%1_%2%3").arg(teamName).arg(7).arg(1)));
	


			setFieldValue(QString("%1_%2_%3%4").arg(teamName).arg(18).arg(4).arg(0),getFieldValue(QString("%1_%2%3").arg(teamName).arg(1).arg(0)));
			setFieldValue(QString("%1_%2_%3%4").arg(teamName).arg(18).arg(4).arg(1),getFieldValue(QString("%1_%2%3").arg(teamName).arg(0).arg(1)));
			setFieldValue(QString("%1_%2_%3%4").arg(teamName).arg(18).arg(5).arg(0),getFieldValue(QString("%1_%2%3").arg(teamName).arg(3).arg(0)));
			setFieldValue(QString("%1_%2_%3%4").arg(teamName).arg(18).arg(5).arg(1),getFieldValue(QString("%1_%2%3").arg(teamName).arg(2).arg(1)));
			setFieldValue(QString("%1_%2_%3%4").arg(teamName).arg(18).arg(6).arg(0),getFieldValue(QString("%1_%2%3").arg(teamName).arg(5).arg(0)));
			setFieldValue(QString("%1_%2_%3%4").arg(teamName).arg(18).arg(6).arg(1),getFieldValue(QString("%1_%2%3").arg(teamName).arg(4).arg(1)));
			setFieldValue(QString("%1_%2_%3%4").arg(teamName).arg(18).arg(7).arg(0),getFieldValue(QString("%1_%2%3").arg(teamName).arg(7).arg(0)));
			setFieldValue(QString("%1_%2_%3%4").arg(teamName).arg(18).arg(7).arg(1),getFieldValue(QString("%1_%2%3").arg(teamName).arg(6).arg(1)));
	
}



void HelloQT::slotSaveTeamsButton()
{	
	QString iniName = QCoreApplication::applicationDirPath() + "/" + QCoreApplication::applicationName() + ".ini" ;
	QSettings settings(iniName, QSettings::Format::IniFormat);
	QList<TeamData> teams;
	teams = getGroupData();
	settings.remove("TeamsGroupData");
	settings.beginGroup("TeamsGroupData");
	settings.beginWriteArray("teams");
	for (int i = 0; i < teams.size(); ++i)
	{
		settings.setArrayIndex(i);
		settings.setValue("name", teams.at(i).name);
		settings.setValue("gamesCount", teams.at(i).gamesCount);
		settings.setValue("ballsDiff", teams.at(i).ballsDiff);
		settings.setValue("points", teams.at(i).points);
	}
	settings.endArray();
	settings.endGroup();
}

void HelloQT::slotLoadTeamsButton()
{
	QString iniName = QCoreApplication::applicationDirPath() + "/" + QCoreApplication::applicationName() + ".ini" ;
	QSettings settings(iniName, QSettings::Format::IniFormat);
	settings.beginGroup("TeamsGroupData");
	TeamData r;
	QList<TeamData> teams;
	int size = settings.beginReadArray("teams");
	for (int i = 0; i < size; ++i)//?????????????????size || teams.size()
	{
		settings.setArrayIndex(i);
		TeamData r;		
		r.name = settings.value("name").toString();
		r.gamesCount = settings.value("gamesCount").toInt();
		r.ballsDiff = settings.value("ballsDiff").toInt();
		r.points = settings.value("points").toInt();
		teams.push_back(r);
	}
	settings.endArray();
	settings.endGroup();
	setAllGroupData(teams);
}