#pragma once

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QFileDialog>
#include <QtSql/qtsqlglobal.h>
#include <QtSql/qsqlerror.h>
#include <QtSql/qsqlquery.h>
#include <QtSql/qsqlquerymodel.h>
#include <QAbstractItemView>
#include <map>
#include <string>
#include <iostream>
#include "QtWorkingWithDataBase.h"
#include "MultisimConnectivityClass.h"
#include <QMessageBox>

class DisplayOfModels : public QDialog {
	Q_OBJECT
public:
	DisplayOfModels(QWidget* widget = nullptr);
	~DisplayOfModels();
private:
	QVBoxLayout *verticalLayout;
	QSplitter *splitter;
	QLineEdit *lineEdit;
	QPushButton *pushButton;
	QTableView *tableWidget;
	QDialogButtonBox *buttonBox;
	QDialog* dialog;
	QString* path_to_db;
	QString* sql_request;
	_component* selected_component = nullptr;
	QSqlQueryModel* QueryModel;
	QSqlQuery* qry;
	QSqlDatabase* db;
	QString* selected_model_name;
	double selected_priemka;
	QString selected_tempreture;
private slots:
	void accept();
	void reject();
	void OpenDB();
	void SetSelectedModel();
private:
	void FindAvailableComponents();
public:
	void setSchemeComponent(_component* c);
	void ShowFromMainWindow(double priemka, QString tempreture);
	_component* getCurrentcomponent();
};
