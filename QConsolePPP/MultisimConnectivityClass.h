#pragma once

#include <vector>
#include <string>
#include <map>
#include <QString>
#include <iostream>
#include <comdef.h>
#include "windows.h"
#include "ComponentList.h"
#import "C:\Program Files (x86)\National Instruments\Circuit Design Suite 14.2\MSInterface.dll"

using namespace MultisimInterface;
using namespace std;

string bstr_to_str(BSTR source);

class MultisimConnectivity {
private:
	IMultisimAppPtr M_App_ptr;
	IMultisimCircuitPtr M_Cuircuit_ptr;
	map<string, double> probes_values;
public:
	MultisimConnectivity();
	~MultisimConnectivity();
	void OpenScheme(const QString* scheme_path);
private:
	void CalculateForDC();
	void CalculateForAC(double Hz);
	double getAvgForProbe(_variant_t data_set, int numSamples);
	vector<string> getSchemeResistorsNames();
	vector<string> getSchemeCapacitorsNames();
	vector<string> getSchemeInductorNames();
	vector<string> getStringValues(_variant_t result_of_operation);
	vector<double> getSchemeNominalsFromMask(vector<string> Masks_of_RLC);
	vector<string> getSchemeDiodesNames();
	vector<string> getSchemeTransostorsNames();
	void FillOneTypeComponents(vector<string>& masks, vector<double>& nominals_values, TypeOfComponent t, vector<_component>& c_list);
public:
	map<string, double>& getProbesValues();
	vector<string> getAllProbes();
	void ClearProbes();
	void FillProbes(double Hz);
	void FillProbesForComponents(Component_List& c_list);
	vector<string> getStringValuesOutputs();
	void FillListComponent(Component_List& c_list);
	QString getSchemeImage(QString path);
	IMultisimCircuitPtr getCuircuitPtr();
};