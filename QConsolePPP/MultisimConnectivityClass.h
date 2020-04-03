#pragma once

#include <vector>
#include <string>
#include <map>
#include <QString>
#include <iostream>
#include <comdef.h>
#include "windows.h"
#import "C:\Program Files (x86)\National Instruments\Circuit Design Suite 14.2\MSInterface.dll"

using namespace MultisimInterface;
using namespace std;


class MultisimConnectivity {
private:
	IMultisimAppPtr M_App_ptr;
	IMultisimCircuitPtr M_Cuircuit_ptr;
public:
	MultisimConnectivity();
	~MultisimConnectivity();
	void OpenScheme(const QString* scheme_path);
private:
	vector<string> getStringValues(_variant_t result_of_operation);
	vector<double> getDoubleValues(_variant_t result_of_operation);
public:
	vector<string> getStringValuesOutputs();
	vector<double> getDoubleValuesOutputs();
};