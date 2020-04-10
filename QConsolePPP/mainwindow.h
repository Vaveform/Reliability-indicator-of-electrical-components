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
#include <QMenuBar>
#include <QMenu>
#include <QDir>
#include <QStringLiteral>
#include "QtWorkingWithDatabase.h"
#include "BarChart.h"
#include "MultisimConnectivityClass.h"
#include "DialogOptions.h"
#include "DisplayOfModels.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <limits>

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
	QStatusBar *statusbar;
    QString scheme_path;
	QVBoxLayout *verticalLayout_3;
	QVBoxLayout *verticalLayout_4;
	QTableView *tableView;
	QChartView *chartView;
	Chart *chart;
	QTableWidget* table;
	DialogOptions* dialogOptions;
	DisplayOfModels* models;
	QWidget* tab_3;
	QVBoxLayout* verticalLayout_5;
	QSplitter* splitter;
	QTableWidget* table2;
	QGraphicsView* graphics_View;
	QGraphicsScene* scene;
	QImage* image_object;
	QLabel* image_label;
	Component_List components;
	QTableWidgetItem* Row_of_models;
	QTableWidgetItem* Column_of_models_names;
	QTableWidgetItem* Column_of_idx;
	QTableWidgetItem* Column_of_marks;
public:
	MainWindow();
	~MainWindow();
private slots:
	void OpenFile();
	void CompleteWork();
	void Calculate();
	void OpenOptions();
	void ModelSelection();
};