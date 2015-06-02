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
	//C������������ �����
	void slotStartSimulationButtonHandler();
	//�������� ��������� �������
	void slotClearGroupResults();
	//ComboBox ������ �����
	void slotSimulation01GroupChanged(int);
	//������� �� ������ play-off
	void slotStartPlayOffStageButton();
	//��������� ������� �������� � play-off
	void goToPlayOff();
	//��� ���� �������� �� ������ ������ � ���� ������ � ������ play-off
	void slotStartSimulationPlayOffStage18Button();
	void slotStartSimulationPlayOffStage14Button();
	void slotStartSimulationPlayOffStage12Button();
	void slotStartSimulationPlayOffStage11Button();
	//��������� ������� � ��������� ������
	void slotSaveTeamsButton();
	//��������� ������� ��� ��������� ������
	void slotLoadTeamsButton();

private:
	//���������� ��� ������ QLineEdit,fieldName (team,score,points)
	QString getObjectName(int group, int posInGroup, QString fieldName);
	//���� QLineEdit �� �����
	QLineEdit* getFieldForGroup(int group, int posInGroup, QString fieldName);
	//������ �������� QLineEdit
	void setFieldValue (int group, int posInGroup, QString fieldName, QString value);
	//������ �������� QLineEdit
	void setFieldValue (int group, int posInGroup, QString fieldName, int value);
	//������ �������� QLineEdit
	void  setFieldValue(QString objectName, QString value);
	//������� �������� QLineEdit
	QString getFieldValue(int group, int posInGroup, QString fieldName);
	//������� �������� QLineEdit
	QString getFieldValue(QString objectName);
	
	//����� ������� �� ���������� ������
	QStringList getTeamsForGroup(int group);
	//����� ������� �� ���������� ������
	Group getGroupData(int group);
	//������� ��� �������
	QList<TeamData> getGroupData();
	//��������� ������
	void setGroupData(int group,Group data);
	//������������ ����������� ������� � ������� �� � �������
	void setAllGroupData(QList<TeamData> data);
	//����� QList ����� ��������� ��������� ��� ������ ������������ ���������
	std::map<int, std::vector<TeamData>>  splitTeams(QList<TeamData> data);
	

	//������� stl ��������� multimap,��� �������� ��������� ��� � Group Stage
	typedef std::multimap<QString,QString> GroupGames_t;
	typedef std::map<int,GroupGames_t> AllGames_t;
	AllGames_t allGames;


	Ui::HelloQTClass ui;

};

#endif // HELLOQT_H
