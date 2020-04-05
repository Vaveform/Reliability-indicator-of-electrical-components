#include "DialogOptions.h"


DialogOptions::DialogOptions(QWidget* widget) {
	dialog = new QDialog(widget);
	dialog->setObjectName(QString::fromUtf8("dialog"));
	dialog->setEnabled(true);
	dialog->resize(506, 303);
	dialog->setFixedSize(dialog->size());
	buttonBox = new QDialogButtonBox(dialog);
	buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
	buttonBox->setGeometry(QRect(340, 270, 156, 23));
	buttonBox->setOrientation(Qt::Horizontal);
	buttonBox->setStandardButtons(QDialogButtonBox::Cancel | QDialogButtonBox::Ok);
	splitter = new QSplitter(dialog);
	splitter->setObjectName(QString::fromUtf8("splitter"));
	splitter->setGeometry(QRect(10, 20, 491, 21));
	splitter->setOrientation(Qt::Horizontal);
	label = new QLabel(splitter);
	label->setObjectName(QString::fromUtf8("label"));
	splitter->addWidget(label);
	comboBox = new QComboBox(splitter);
	comboBox->addItem(QString());
	comboBox->addItem(QString());
	comboBox->addItem(QString());
	comboBox->addItem(QString());
	comboBox->addItem(QString());
	comboBox->addItem(QString());
	comboBox->addItem(QString());
	comboBox->setObjectName(QString::fromUtf8("comboBox"));
	splitter->addWidget(comboBox);
	splitter_2 = new QSplitter(dialog);
	splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
	splitter_2->setGeometry(QRect(10, 50, 491, 21));
	splitter_2->setOrientation(Qt::Horizontal);
	label_2 = new QLabel(splitter_2);
	label_2->setObjectName(QString::fromUtf8("label_2"));
	splitter_2->addWidget(label_2);
	comboBox_2 = new QComboBox(splitter_2);
	comboBox_2->addItem(QString());
	comboBox_2->addItem(QString());
	comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));
	splitter_2->addWidget(comboBox_2);
	dialog->setWindowTitle(QCoreApplication::translate("dialog", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213 \321\200\320\260\321\201\321\207\321\221\321\202\320\260", nullptr));
	label->setText(QCoreApplication::translate("dialog", "\320\236\320\272\321\200\321\203\320\266\320\260\321\216\321\211\320\260\321\217 \321\202\320\265\320\274\320\277\320\265\321\200\320\260\321\202\321\203\321\200\320\260, C", nullptr));
	comboBox->setItemText(0, QCoreApplication::translate("dialog", "25", nullptr));
	comboBox->setItemText(1, QCoreApplication::translate("dialog", "30", nullptr));
	comboBox->setItemText(2, QCoreApplication::translate("dialog", "35", nullptr));
	comboBox->setItemText(3, QCoreApplication::translate("dialog", "40", nullptr));
	comboBox->setItemText(4, QCoreApplication::translate("dialog", "45", nullptr));
	comboBox->setItemText(5, QCoreApplication::translate("dialog", "50", nullptr));
	comboBox->setItemText(6, QCoreApplication::translate("dialog", "55", nullptr));

	label_2->setText(QCoreApplication::translate("dialog", "\320\237\321\200\320\270\321\221\320\274\320\272\320\260, %", nullptr));
	comboBox_2->setItemText(0, QCoreApplication::translate("dialog", "5", nullptr));
	comboBox_2->setItemText(1, QCoreApplication::translate("dialog", "9", nullptr));

	Tempreture = comboBox->itemText(0).toDouble();
	Priemka = comboBox_2->itemText(0).toDouble();

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
	connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

}


DialogOptions::~DialogOptions() {
	delete comboBox_2;
	delete label_2;
	delete splitter_2;
	delete comboBox;
	delete label;
	delete splitter;
	delete buttonBox;
	delete dialog;
}

double DialogOptions::getPriemka() {
	return Priemka;
}

double DialogOptions::getTempreture() {
	return Tempreture;
}

void DialogOptions::ShowFromMainWindow() {
	dialog->show();
}

void DialogOptions::reject() {
	dialog->close();
}

void DialogOptions::accept() {
	Tempreture = comboBox->currentText().toDouble();
	Priemka = comboBox_2->currentText().toDouble();
	std::cout << this->getPriemka() << " " << this->getTempreture() << std::endl;
	dialog->close();
}