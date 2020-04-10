#pragma once

#include <QtCharts>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <string>

class Chart : public QWidget {
private:
	QBarSet *set;
	QChart *chart;
	QBarSeries *series;
	QBarCategoryAxis *axisX;
	QValueAxis *axisY;
public:
	Chart();
	~Chart();
	void SetValues(std::vector<std::string> names, std::vector<double> values);
	QChart* getChart();
};