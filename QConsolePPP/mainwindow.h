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
#include "BarChart.h"
#include "MultisimConnectivityClass.h"
#include "DialogOptions.h"
#include "DisplayOfModels.h"

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
	QTableWidget* table;
	DialogOptions* dialogOptions;
	QAction* action_1;
	QMenu* menu;
	QMenu* menu_1;
	QMenu* menu_2;
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
public:
	explicit MainWindow();
	virtual ~MainWindow();
private slots:
	void OpenFile();
	void CompleteWork();
	void Calculate();
	void OpenOptions();
	void ModelSelection();
};