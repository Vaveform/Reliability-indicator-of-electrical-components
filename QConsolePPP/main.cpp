#include "mainwindow.h"
#include <QApplication>
#include <QtCharts>
#include <stdexcept>
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include "MultisimConnectivityClass.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

using namespace MultisimInterface;
using namespace std;

static const string path_to_scheme = "E:\\Multisim_connection\\Test_scheme.ms14";
static const string path_to_image = "E:\\Multisim_connection\\Scheme_image.jpg";

int main(int argc, char *argv[])
{
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
	QApplication app(argc, argv);
	MainWindow w;
	return app.exec();
}