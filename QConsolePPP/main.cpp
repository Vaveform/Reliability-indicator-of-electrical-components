#include "mainwindow.h"
#include <QApplication>
#include <QtCharts>
#include <stdexcept>
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <clocale>
#include <comutil.h>
#include <QtSql/qtsqlglobal.h>
#include <QtSql/qsqlerror.h>
#include <QtSql/qsqlquery.h>
#include <qimage.h>
#include <qimagereader.h>
#include "MultisimConnectivityClass.h"
#include <windows.h>
#include <locale.h>
#include "DisplayOfModels.h"
#include "ComponentList.h"



int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
    MainWindow w;
	return app.exec();
}