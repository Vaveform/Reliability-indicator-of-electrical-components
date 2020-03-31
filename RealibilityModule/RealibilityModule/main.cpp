#include "review.h"
#include <QApplication>
#include "windows.h"
#include <comdef.h>
#include <stdexcept>
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#import "C:\Program Files (x86)\National Instruments\Circuit Design Suite 14.2\MSInterface.dll"

using namespace MultisimInterface;
using namespace std;

static const string path_to_scheme = "E:\\Multisim_connection\\Test_scheme.ms14";
static const string path_to_image = "E:\\Multisim_connection\\Scheme_image.jpg";


string bstr_to_str(BSTR source) {
	//source = L"lol2inside";
	_bstr_t wrapped_bstr = _bstr_t(source);
	int length = wrapped_bstr.length();
	char* char_array = new char[length];
	strcpy_s(char_array, length + 1, wrapped_bstr);
	return char_array;
}



vector<double> GetDoubleOutputs(_variant_t RequestedVariant) {
	vector<double> values;
	SAFEARRAY* arr = RequestedVariant.parray;
	cout << "Num dims of output array: " << arr->cDims << endl;
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
			values.push_back(move(lVal));
		}
		SafeArrayUnaccessData(arr);
	}
	else {
		throw invalid_argument("Unsucceded opening of array with data");
	}
	return values;
}


vector<_bstr_t> GetBstrOutputs(_variant_t RequestedVariant) {
	vector<_bstr_t> values;
	SAFEARRAY* arr = RequestedVariant.parray;
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
			values.push_back(move(_bstr_t(lVal)));
		}
		SafeArrayUnaccessData(arr);
	}
	else {
		throw invalid_argument("Unsucceded opening of array with data");
	}
	return values;
}

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
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
	catch (_com_error& ex) {
		std::cout << ex.Description() << std::endl;
		CoUninitialize();
	}


	Review window;

	window.setWindowTitle("Review");
	window.show();
	CoUninitialize();
	return app.exec();
}