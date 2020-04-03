#pragma once

#include <QMainWindow>
#include <QVariant>
#include <QApplication>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QMainWindow>
#include <QMenuBar>
#include <QPushButton>
#include <QStatusBar>
#include <QVBoxLayout>
#include <QWidget>
#include <QFileDialog>
#include <QTableView>
#include <QtCharts>
#include <QtSql\QSqlTableModel>
#include "BarChart.h"
#include "MultisimConnectivityClass.h"

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow {
	Q_OBJECT
private:
	MultisimConnectivity* MultisimApp;
	QMainWindow mainwindow;
	QWidget *centralwidget;
	QVBoxLayout *verticalLayout_2;
	QHBoxLayout *horizontalLayout;
	QLineEdit *lineEdit;
	QPushButton *pushButton;
	QVBoxLayout *verticalLayout;
	QTabWidget *tabWidget;
	QWidget *tab;
	QWidget *tab_2;
	QPushButton *pushButton_2;
	QPushButton *pushButton_3;
	QMenuBar *menubar;
	QStatusBar *statusbar;
	QString* scheme_path;
	QVBoxLayout *verticalLayout_3;
	QVBoxLayout *verticalLayout_4;
	QTableView *tableView;
	QChartView *chartView;
	MyChart *chart;
	QTableWidgetItem* first;
	QTableWidgetItem* second;
	QTableWidgetItem* third;
	QTableWidget* table;
public:
	explicit MainWindow();
	virtual ~MainWindow();
private slots:
	void OpenFile();
	void CompleteWork();
	void Calculate();
};