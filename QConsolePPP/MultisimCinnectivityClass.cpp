#include "MultisimConnectivityClass.h"



string bstr_to_str(BSTR source) {
	//source = L"lol2inside";
	_bstr_t wrapped_bstr = _bstr_t(source);
	int length = wrapped_bstr.length();
	char* char_array = new char[length];
	strcpy_s(char_array, length + 1, wrapped_bstr);
	return char_array;
}



MultisimConnectivity::MultisimConnectivity() {
	cout << "Multisim constructing" << endl;
	::CoInitialize(NULL);
	M_App_ptr = IMultisimAppPtr(L"MultisimInterface.MultisimApp");
	M_App_ptr->Connect();
}




MultisimConnectivity::~MultisimConnectivity() {
	cout << "Multisim closed" << endl;
	::CoUninitialize();
}




void MultisimConnectivity::OpenScheme(const QString* scheme_path) {
	M_Cuircuit_ptr = nullptr;
	M_Cuircuit_ptr = M_App_ptr->OpenFile(_bstr_t(scheme_path->toStdString().c_str()));
}




vector<string> MultisimConnectivity::getStringValues(_variant_t result_of_operation) {
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




vector<double> MultisimConnectivity::getDoubleValues(_variant_t result_of_operation) {
	vector<double> values;
	SAFEARRAY* arr = result_of_operation.parray;
	//cout << "Num dims of output array: " << arr->cDims << endl;
	double* pVals = nullptr;
	HRESULT hr = SafeArrayAccessData(arr, (void**)&pVals);
	if (SUCCEEDED(hr)) {
		long lowerBound, upperBound;
		SafeArrayGetLBound(arr, 1, &lowerBound);
		SafeArrayGetUBound(arr, 1, &upperBound);

		long cnt_elements = upperBound - lowerBound + 1;
		cout << "cnt_elements " << cnt_elements << endl;
		for (int i = 0; i < cnt_elements; ++i)  // iterate through returned values
		{
			double lVal = pVals[i];
			cout << lVal << endl;
			values.push_back(lVal);
		}
		SafeArrayUnaccessData(arr);
	}
	else {
		return values;
	}
	return values;
}



vector<string> MultisimConnectivity::getStringValuesOutputs() {
	return this->getStringValues(M_Cuircuit_ptr->EnumOutputs(SimulationIOPower));
}

vector<double> MultisimConnectivity::getDoubleValuesOutputs() {
	SimulationInterpolation method = SimulationInterpolationLinear;
	vector<string> outputs = getStringValuesOutputs();
	vector<double> outputs_values;
	for (auto it = outputs.begin(); it != outputs.end(); it++) {
		_variant_t data_set;
		M_Cuircuit_ptr->SetOutputRequest((_bstr_t)it->c_str(), method, 10000, 1, VARIANT_FALSE);
		M_Cuircuit_ptr->RunSimulationUntilNextOutput();
		VARIANT_BOOL status_wait = VARIANT_TRUE;
		M_Cuircuit_ptr->WaitForNextOutput(&status_wait, 10000);
		M_Cuircuit_ptr->GetOutputData((_bstr_t)it->c_str(), &data_set, &method);
		outputs_values.push_back(getDoubleValues(data_set)[1]);
	}
	if (M_Cuircuit_ptr->GetSimulationState() == SimulationRunning) {
		M_Cuircuit_ptr->StopSimulation();
	}
	return outputs_values;
}


vector<string> MultisimConnectivity::getSchemeResistorsNames() {
	return this->getStringValues(M_Cuircuit_ptr->EnumComponents(ComponentResistor));
}

vector<string> MultisimConnectivity::getSchemeCapacitorsNames() {
	return this->getStringValues(M_Cuircuit_ptr->EnumComponents(ComponentCapacitor));
}

vector<string> MultisimConnectivity::getSchemeInductorNames() {
	return this->getStringValues(M_Cuircuit_ptr->EnumComponents(ComponentInductor));
}

vector<double> MultisimConnectivity::getSchemeNominalsFromMask(vector<string> Masks_of_resistors) {
	vector<double> array_of_nominals;
	for (auto it = Masks_of_resistors.begin(); it != Masks_of_resistors.end(); it++) {
		double tmp;
		M_Cuircuit_ptr->get_RLCValue((_bstr_t)it->c_str(), &tmp);
		array_of_nominals.push_back(tmp);
	}
	return array_of_nominals;
}

void MultisimConnectivity::FillOneTypeComponents(vector<string>& masks, vector<double>& nominals_values, TypeOfComponent t, vector<_component>& c_list) {
	for (size_t i = 0; i < masks.size(); i++) {
		_component tmp;
		tmp.scheme_mark = masks[i];
		tmp.nominal = nominals_values[i];
		tmp.type_component = t;
		tmp.model_name = "";
		c_list.push_back(tmp);
	}
}

void MultisimConnectivity::FillListComponent(vector<_component>& c_list) {
	vector<string> masks = this->getSchemeResistorsNames();
	vector<double> nominals_values = this->getSchemeNominalsFromMask(masks);
	// Fill component_list
	this->FillOneTypeComponents(masks, nominals_values, TypeOfComponent::ComponentResistor, c_list);
	masks = this->getSchemeCapacitorsNames();
	nominals_values = this->getSchemeNominalsFromMask(masks);
	this->FillOneTypeComponents(masks, nominals_values, TypeOfComponent::ComponentCapacitor, c_list);
	masks = this->getSchemeInductorNames();
	nominals_values = this->getSchemeNominalsFromMask(masks);
	this->FillOneTypeComponents(masks, nominals_values, TypeOfComponent::ComponentInductor, c_list);
}

QString MultisimConnectivity::getSchemeImage(QString path) {
	_bstr_t bstr_path = (_bstr_t)(path.toStdString() + "\Scheme_image.jpg").c_str();
	QString result = M_Cuircuit_ptr->GetCircuitImage(CircuitImageJPG, bstr_path);
	return result;
}