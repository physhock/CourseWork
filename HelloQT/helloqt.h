#ifndef HELLOQT_H
#define HELLOQT_H

#include <QtWidgets/QMainWindow>
#include "ui_helloqt.h"


struct TeamData
{
	TeamData () {gamesCount=ballsDiff=points=0;}
	QString name;
	int gamesCount;
	int ballsDiff;
	int points;
};
typedef std::vector<TeamData> Group;


class HelloQT : public QMainWindow
{
	Q_OBJECT

public:
	HelloQT(QWidget *parent = 0);
	~HelloQT();
	void clearGroupResults();

public slots:
	void slotStartSimulationButtonHandler();
	void slotClearGroupResults();
	void slotSimulation01GroupChanged(int);

	void slotStartPlayOffStageButton();
	void goToPlayOff();

	void slotStartSimulationPlayOffStage18Button();
	void slotStartSimulationPlayOffStage14Button();
	void slotStartSimulationPlayOffStage12Button();
	void slotStartSimulationPlayOffStage11Button();
	

private:

	QString getObjectName(int group, int posInGroup, QString fieldName);
	QLineEdit* getFieldForGroup(int group, int posInGroup, QString fieldName);
	
	void setFieldValue (int group, int posInGroup, QString fieldName, QString value);
	void setFieldValue (int group, int posInGroup, QString fieldName, int value);
	QString getFieldValue(int group, int posInGroup, QString fieldName);

	QString getFieldValue(QString objectName);
	void  setFieldValue(QString objectName, QString value);
	
	QStringList getTeamsForGroup(int group);

	Group getGroupData(int group);
	void setGroupData(int group,Group data);


	typedef std::multimap<QString,QString> GroupGames_t;
	typedef std::map<int,GroupGames_t> AllGames_t;
	AllGames_t allGames;



	Ui::HelloQTClass ui;

};

#endif // HELLOQT_H
