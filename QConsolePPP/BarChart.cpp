#include "BarChart.h"

Chart::Chart() {
	set = new QBarSet(NULL);
	series = new QBarSeries();
	series->append(set);
	chart = new QChart();
	chart->addSeries(series);
	QFont font;
	font.setPointSize(24);
	chart->setTitle("\320\255\320\272\321\201\320\277\320\273\321\203\320\260\321\202\320\260\321\206\320\270\320\276\320\275\320\275\320\260\321\217 \320\270\320\275\321\202\320\265\320\275\321\201\320\270\320\262\320\275\320\276\321\201\321\202\321\214 \320\276\321\202\320\272\320\260\320\267\320\276\320\262");
	chart->setTitleFont(font);
	chart->setAnimationOptions(QChart::AnimationOption::AllAnimations);
	axisX = new QBarCategoryAxis();
	chart->addAxis(axisX, Qt::AlignBottom);
	series->attachAxis(axisX);
	axisY = new QValueAxis();
	axisY->setRange(0, 1);
	chart->addAxis(axisY, Qt::AlignLeft);
	series->attachAxis(axisY);
}


Chart::~Chart() {
	delete axisY;
	delete axisX;
	delete set;
	delete series;
	delete chart;
}


void Chart::SetValues(std::vector<std::string> names, std::vector<double> values) {
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


QChart* Chart::getChart() {
	return chart;
}