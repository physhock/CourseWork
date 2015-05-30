#include <QtWidgets/QApplication>
#include <iostream>

#include "helloqt.h"





int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	HelloQT w;
	w.show();
	return a.exec();
}



