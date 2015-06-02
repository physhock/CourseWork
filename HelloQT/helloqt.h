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
	//Cимулирование матча
	void slotStartSimulationButtonHandler();
	//Очиастка групповой таблицы
	void slotClearGroupResults();
	//ComboBox выбора групп
	void slotSimulation01GroupChanged(int);
	//Переход на стадию play-off
	void slotStartPlayOffStageButton();
	//Переносим команды вышедшие в play-off
	void goToPlayOff();
	//Все ниже отвечает на проход команд в след стадию в рамках play-off
	void slotStartSimulationPlayOffStage18Button();
	void slotStartSimulationPlayOffStage14Button();
	void slotStartSimulationPlayOffStage12Button();
	void slotStartSimulationPlayOffStage11Button();
	//Сохраняем команды в групповой стадии
	void slotSaveTeamsButton();
	//Загружаем команды для групповой стадии
	void slotLoadTeamsButton();

private:
	//Генерируем имя ячейки QLineEdit,fieldName (team,score,points)
	QString getObjectName(int group, int posInGroup, QString fieldName);
	//Ищем QLineEdit по имени
	QLineEdit* getFieldForGroup(int group, int posInGroup, QString fieldName);
	//Задаем значение QLineEdit
	void setFieldValue (int group, int posInGroup, QString fieldName, QString value);
	//Задаем значение QLineEdit
	void setFieldValue (int group, int posInGroup, QString fieldName, int value);
	//Задаем значение QLineEdit
	void  setFieldValue(QString objectName, QString value);
	//Достаем значение QLineEdit
	QString getFieldValue(int group, int posInGroup, QString fieldName);
	//Достаем значение QLineEdit
	QString getFieldValue(QString objectName);
	
	//Берем команды из получаемой группы
	QStringList getTeamsForGroup(int group);
	//Берем команды из получаемой группы
	Group getGroupData(int group);
	//Достаем все команды
	QList<TeamData> getGroupData();
	//Заполняем группу
	void setGroupData(int group,Group data);
	//Обрабатываем загруженные команды и заносим их в таблицу
	void setAllGroupData(QList<TeamData> data);
	//Делим QList чтобы нормально заполнить все группы загруженными командами
	std::map<int, std::vector<TeamData>>  splitTeams(QList<TeamData> data);
	

	//Создаем stl контейнер multimap,для проверки сыгранных игр в Group Stage
	typedef std::multimap<QString,QString> GroupGames_t;
	typedef std::map<int,GroupGames_t> AllGames_t;
	AllGames_t allGames;


	Ui::HelloQTClass ui;

};

#endif // HELLOQT_H
