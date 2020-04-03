#pragma once

#include <QtCharts>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <string>

class MyChart : public QWidget {
private:
	QBarSet *set;
	QChart *chart;
	QBarSeries *series;
	QBarCategoryAxis *axisX;
	QValueAxis *axisY;
public:
	MyChart();
	~MyChart();
	void SetValues(std::vector<std::string> names, std::vector<double> values);
	QChart* getChart();
};