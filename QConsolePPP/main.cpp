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


using namespace MultisimInterface;
using namespace std;

static const QString path_to_scheme = "E:\\Multisim_connection\\Test_scheme.ms14";
static const QString path_to_image = "E:\\Multisim_connection\\Scheme_image.jpg";

#ifdef Q_OS_WIN32
QString env = getenv("SYSTEMROOT");
#endif

vector<string> getStringValues(_variant_t result_of_operation) {
	vector<string> values;
	SAFEARRAY* arr = result_of_operation.parray;
	BSTR* pVals = nullptr;
	HRESULT hr = SafeArrayAccessData(arr, (void**)&pVals);
	if (SUCCEEDED(hr)) {
		long lowerBound, upperBound;
		SafeArrayGetLBound(arr, 1, &lowerBound);
		SafeArrayGetUBound(arr, 1, &upperBound);

		long cnt_elements = upperBound - lowerBound + 1;
		for (int i = 0; i < cnt_elements; ++i)  // iterate through returned values
		{
			BSTR lVal = pVals[i];
			values.push_back(bstr_to_str(lVal));
			cout << values[i] << endl;
		}
		SafeArrayUnaccessData(arr);
	}
	else {
		return values;
	}
	return values;
}

double getDoubleValues(_variant_t result_of_operation) {
	vector<double> values;
	SAFEARRAY* arr = result_of_operation.parray;
	//cout << "Num dims of output array: " << arr->cDims << endl;
	double* pVals = nullptr;
	HRESULT hr = SafeArrayAccessData(arr, (void**)&pVals);
	double Avg = 0;
	double nums = 0;
	if (SUCCEEDED(hr)) {
		long lowerBound, upperBound;
		SafeArrayGetLBound(arr, 1, &lowerBound);
		SafeArrayGetUBound(arr, 1, &upperBound);

		long cnt_elements = upperBound - lowerBound + 1;
		double* lVal = &pVals[0];
		for (int i = 0; i < 1000; i++) {
			if (i % 2 == 1) {
				Avg += lVal[i];
				nums += 1;
			}
		}
		Avg /= nums;
	}
	else {
		return Avg;
	}
	return Avg;
}



int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	//setlocale(LC_CTYPE, "rus");
	/*ifstream fin("E:\\Zaebalo\\QConsolePPP\\QConsolePPP\\testing.csv");
	string line;
	while (getline(fin, line)) {
		cout << line << endl;
	}*/
	
	/*QApplication app(argc, argv);*/
	/*::CoInitialize(NULL);
	IMultisimAppPtr M_App_ptr = IMultisimAppPtr(L"MultisimInterface.MultisimApp");
	M_App_ptr->Connect();
	IMultisimCircuitPtr M_Cuircuit_ptr = M_App_ptr->OpenFile(path_to_scheme.toStdString().c_str());
	vector<string> outputname = getStringValues(M_Cuircuit_ptr->EnumOutputs(SimulationIOAll));*/
	/*_variant_t data_set;
	SimulationInterpolation method = SimulationInterpolationLinear;
	VARIANT_BOOL status_wait = VARIANT_TRUE;
	try {
		M_Cuircuit_ptr->SetOutputRequest((_bstr_t)outputname[0].c_str(), method, 1000000, 1000, VARIANT_FALSE);
		M_Cuircuit_ptr->RunSimulationUntilNextOutput();
		M_Cuircuit_ptr->WaitForNextOutput(&status_wait, 10000);
		M_Cuircuit_ptr->GetOutputData((_bstr_t)outputname[0].c_str(), &data_set, &method);
	}
	catch (_com_error& ex) {
		cout << ex.Description() << endl;
	}
	vector<double> res = getDoubleValues(data_set);*/
	/*MainWindow w;
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
	/*::CoUninitialize();*/
	return app.exec();

}