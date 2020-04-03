#include "BarChart.h"

MyChart::MyChart() {
	set = new QBarSet(NULL);
	series = new QBarSeries();
	series->append(set);
	chart = new QChart();
	chart->addSeries(series);
	chart->setTitle("Reliability indexies");
	chart->setAnimationOptions(QChart::AnimationOption::AllAnimations);
	axisX = new QBarCategoryAxis();
	chart->addAxis(axisX, Qt::AlignBottom);
	series->attachAxis(axisX);
	axisY = new QValueAxis();
	axisY->setRange(0, 1);
	chart->addAxis(axisY, Qt::AlignLeft);
	series->attachAxis(axisY);
}


MyChart::~MyChart() {
	delete axisY;
	delete axisX;
	delete set;
	delete series;
	delete chart;
}


void MyChart::SetValues(std::vector<std::string> names, std::vector<double> values) {
	if (names.size() != values.size()) {
		throw std::invalid_argument("Sizes not equal");
	}
	axisX->clear();
	set->remove(0, set->count());
	double tmp = *values.begin();
	for (size_t i = 0; i < names.size(); i++) {
		//QString tmp(names[i].c_str());
		axisX->append(names[i].c_str());
		*set << values[i];
		if (tmp < values[i]) {
			tmp = values[i];
		}
	}
	axisY->setRange(0, 1.1 * tmp);
}


QChart* MyChart::getChart() {
	return chart;
}