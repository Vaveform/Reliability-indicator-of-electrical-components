#pragma once

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSplitter>
#include <iostream>


class DialogOptions : public QDialog {
	Q_OBJECT
public:
	DialogOptions(QWidget* widget = nullptr);
	~DialogOptions();
	double getPriemka();
	double getTempreture();
	void ShowFromMainWindow();
private slots:
	void accept();
	void reject();
private:
	QDialog* dialog;
	QDialogButtonBox *buttonBox;
	QSplitter *splitter;
	QLabel *label;
	QComboBox *comboBox;
	QSplitter *splitter_2;
	QLabel *label_2;
	QComboBox *comboBox_2;
	double Priemka;
	double Tempreture;
};