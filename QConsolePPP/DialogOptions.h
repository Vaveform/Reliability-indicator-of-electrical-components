#pragma once

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSplitter>
#include <QVBoxLayout>
#include <QtWidgets/QRadioButton>
#include <QTextEdit>
#include <QLineEdit>
#include <iostream>


class DialogOptions : public QDialog {
	Q_OBJECT
public:
	DialogOptions(QWidget* widget = nullptr);
	~DialogOptions();
	double getPriemka();
	QString getTempreture();
	double getHz();
	void ShowFromMainWindow();
	QDialogButtonBox* getButtonBox();
private slots:
	void accept();
	void reject();
	void InputFrequency();
	void setDCsignal();

private:
	QDialog* dialog;
	QDialogButtonBox *buttonBox;
	QSplitter *splitter;
	QLabel *label;
	QComboBox *comboBox;
	QSplitter *splitter_2;
	QLabel *label_2;
	QComboBox *comboBox_2;
	QVBoxLayout* vertical_layout_1;
	QRadioButton *radioButton;
	QRadioButton *radioButton_2;
	QWidget* widget1;
	QWidget* widget2;
	QLabel *label_3;
	QVBoxLayout* vertical_layout_2;
	QLineEdit *textEdit;
	double Priemka;
	QString Tempreture;
	double Hz;
};