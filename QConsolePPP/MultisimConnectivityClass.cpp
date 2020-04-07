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

double MultisimConnectivity::getAvgForProbe(_variant_t data_set, int numSamples){
	vector<double> values;
	SAFEARRAY* arr = data_set.parray;
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
		for (int i = 0; i < numSamples; i++) {
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

vector<string> MultisimConnectivity::getStringValuesOutputs() {
	return this->getStringValues(M_Cuircuit_ptr->EnumOutputs(SimulationIOPower));
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

void MultisimConnectivity::FillListComponent(Component_List& c_list) {
	vector<string> masks = this->getSchemeResistorsNames();
	vector<double> nominals_values = this->getSchemeNominalsFromMask(masks);
	// Fill component_list
	this->FillOneTypeComponents(masks, nominals_values, TypeOfComponent::ComponentResistor, c_list.getRefComponentList());
	masks = this->getSchemeCapacitorsNames();
	nominals_values = this->getSchemeNominalsFromMask(masks);
	this->FillOneTypeComponents(masks, nominals_values, TypeOfComponent::ComponentCapacitor, c_list.getRefComponentList());
	masks = this->getSchemeInductorNames();
	nominals_values = this->getSchemeNominalsFromMask(masks);
	this->FillOneTypeComponents(masks, nominals_values, TypeOfComponent::ComponentInductor, c_list.getRefComponentList());
}

QString MultisimConnectivity::getSchemeImage(QString path) {
	_bstr_t bstr_path = (_bstr_t)(path.toStdString() + "\Scheme_image.jpg").c_str();
	QString result = M_Cuircuit_ptr->GetCircuitImage(CircuitImageJPG, bstr_path);
	return result;
}

IMultisimCircuitPtr MultisimConnectivity::getCuircuitPtr() {
	return this->M_Cuircuit_ptr;
}

vector<string> MultisimConnectivity::getAllProbes() {
	return this->getStringValues(M_Cuircuit_ptr->EnumOutputs(SimulationIOAll));
}

void MultisimConnectivity::CalculateForDC() {
	vector<string> probes = this->getAllProbes();
	SimulationInterpolation method = SimulationInterpolationLinear;
	VARIANT_BOOL status_wait = VARIANT_TRUE;
	_variant_t data_set;
	int nums_Samples = 10;
	for (auto it = probes.begin(); it != probes.end(); it++) {
		try {
			M_Cuircuit_ptr->SetOutputRequest((_bstr_t)it->c_str(), method, 1000, nums_Samples, VARIANT_FALSE);
			M_Cuircuit_ptr->RunSimulationUntilNextOutput();
			M_Cuircuit_ptr->WaitForNextOutput(&status_wait, 10000);
			M_Cuircuit_ptr->GetOutputData((_bstr_t)it->c_str(), &data_set, &method);
			probes_values[*it] = this->getAvgForProbe(data_set, nums_Samples);
		}
		catch (_com_error& exeption) {
			cout << exeption.Description() << endl;
		}
	}
}


void MultisimConnectivity::CalculateForAC(double Hz) {
	vector<string> probes = this->getAllProbes();
	SimulationInterpolation method = SimulationInterpolationLinear;
	VARIANT_BOOL status_wait = VARIANT_TRUE;
	_variant_t data_set;
	int num_Samples = 1000;
	for (auto it = probes.begin(); it != probes.end(); it++) {
		try {
			M_Cuircuit_ptr->SetOutputRequest((_bstr_t)it->c_str(), method, 1000 * Hz, num_Samples, VARIANT_FALSE);
			M_Cuircuit_ptr->RunSimulationUntilNextOutput();
			M_Cuircuit_ptr->WaitForNextOutput(&status_wait, 100000);
			M_Cuircuit_ptr->GetOutputData((_bstr_t)it->c_str(), &data_set, &method);
			probes_values[*it] = this->getAvgForProbe(data_set, num_Samples);
		}
		catch (_com_error& exeption) {
			cout << exeption.Description() << endl;
		}
	}
}


void MultisimConnectivity::FillProbes(double Hz) {
	if (Hz == 0) {
		this->CalculateForDC();
	}
	else {
		this->CalculateForAC(Hz);
	}
}


void MultisimConnectivity::ClearProbes() {
	probes_values.clear();
}

void MultisimConnectivity::FillProbesForComponents(Component_List& c_list) {
	for (auto it = c_list.getRefComponentList().begin(); it != c_list.getRefComponentList().end(); it++) {
		if (it->type_component == TypeOfComponent::ComponentResistor) {
			auto finded_it = probes_values.find("P(" + it->scheme_mark + "P)");
			if (finded_it == probes_values.end()) {
				throw(invalid_argument("Have not probe"));
			}
			it->probe_value = finded_it->second;
		}
		else if (it->type_component == TypeOfComponent::ComponentCapacitor) {
			auto finded_it_A = probes_values.find("V(" + it->scheme_mark + "VA)");
			auto finded_it_B = probes_values.find("V(" + it->scheme_mark + "VB)");
			if (finded_it_A == probes_values.end() || finded_it_B == probes_values.end()) {
				throw(invalid_argument("Have not probe"));
			}
			it->probe_value = abs(abs(finded_it_A->second) - abs(finded_it_B->second));
		}
		else if (it->type_component == TypeOfComponent::ComponentInductor) {
			auto finded_it = probes_values.find("I(" + it->scheme_mark + "I)");
			if (finded_it == probes_values.end()) {
				throw(invalid_argument("Have not probe"));
			}
			it->probe_value = abs(finded_it->second);
		}
	}
}

map<string, double>& MultisimConnectivity::getProbesValues() {
	return probes_values;
}