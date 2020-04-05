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


using namespace MultisimInterface;
using namespace std;

static const string path_to_scheme = "E:\\Multisim_connection\\Test_scheme.ms14";
static const string path_to_image = "E:\\Multisim_connection\\Scheme_image.jpg";

#ifdef Q_OS_WIN32
QString env = getenv("SYSTEMROOT");
#endif


int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	setlocale(LC_CTYPE, "rus");
	/*ifstream fin("E:\\Zaebalo\\QConsolePPP\\QConsolePPP\\testing.csv");
	string line;
	while (getline(fin, line)) {
		cout << line << endl;
	}*/
	
	/*QApplication app(argc, argv);
	CoInitialize(NULL);
	try {
		IMultisimAppPtr application(L"MultisimInterface.MultisimApp");
		application->Connect();
		IMultisimCircuitPtr scheme = application->OpenFile(_bstr_t(path_to_scheme.c_str()));
		auto Outputs = GetBstrOutputs(scheme->EnumOutputs(SimulationIOPower));
		auto Components = GetBstrOutputs(scheme->EnumComponents(ComponentAll));
		for (auto it = Outputs.begin(); it != Outputs.end(); it++) {
			cout << *it << endl;
		}
	}
	catch (_com_error& ex ) {
		std::cout << ex.Description() << std::endl;
		CoUninitialize();
	}

	MainWindow w;
	w.show();

	CoUninitialize();
	return app.exec();*/
	//QApplication app(argc, argv);
	/*QSqlDatabase mydb;
	mydb = QSqlDatabase::addDatabase("QSQLITE");
	mydb.setDatabaseName("E:\\Zaebalo\\mydb.db");
	if (!mydb.open()) {
		cout << "Cannot open" << endl;
	}
	mydb.open();
	QSqlQuery q;
	q.exec("SELECT Model, Class, Group_Model from Resistors");
	while (q.next()) {
		QString Class = q.value(0).toString();
		QString Group_Model = q.value(1).toString();
		QString Model = q.value(2).toString();
		cout << Class.toStdString() << " " << Group_Model.toStdString() << " " << Model.toStdString() << endl;
	}
	mydb.close();*/
	MainWindow w;
	return app.exec();

}