#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QChartView>
#include "mainwindow.h"
#include <iostream>

MainWindow::MainWindow() {
	scheme_path = new QString();
	centralwidget = new QWidget(&mainwindow);
	centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
	verticalLayout_2 = new QVBoxLayout(centralwidget);
	verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
	horizontalLayout = new QHBoxLayout();
	horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
	lineEdit = new QLineEdit(centralwidget);
	lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

	horizontalLayout->addWidget(lineEdit);

	pushButton = new QPushButton(centralwidget);
	pushButton->setObjectName(QString::fromUtf8("pushButton"));

	horizontalLayout->addWidget(pushButton);


	verticalLayout_2->addLayout(horizontalLayout);

	verticalLayout = new QVBoxLayout();
	verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
	tabWidget = new QTabWidget(centralwidget);
	tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
	tab = new QWidget();
	tab->setObjectName(QString::fromUtf8("tab"));
	tabWidget->addTab(tab, QString());
	tab_2 = new QWidget();
	tab_2->setObjectName(QString::fromUtf8("tab_2"));
	tabWidget->addTab(tab_2, QString());
	

	verticalLayout->addWidget(tabWidget);

	pushButton_2 = new QPushButton(centralwidget);
	pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

	verticalLayout->addWidget(pushButton_2);

	pushButton_3 = new QPushButton(centralwidget);
	pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

	verticalLayout->addWidget(pushButton_3);


	verticalLayout_2->addLayout(verticalLayout);

	mainwindow.setCentralWidget(centralwidget);
	menubar = new QMenuBar(&mainwindow);
	menubar->setObjectName(QString::fromUtf8("menubar"));
	menubar->setGeometry(QRect(0, 0, 1030, 21));
	mainwindow.setMenuBar(menubar);
	statusbar = new QStatusBar(&mainwindow);
	statusbar->setObjectName(QString::fromUtf8("statusbar"));
	mainwindow.setStatusBar(statusbar);

	verticalLayout_3 = new QVBoxLayout(tab);
	verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
	chartView = new QChartView(tab);
	chartView->setObjectName(QString::fromUtf8("chart_view"));
	verticalLayout_3->addWidget(chartView);
	chart = new MyChart();
	chartView->setChart(chart->getChart());
	chartView->setRenderHint(QPainter::HighQualityAntialiasing);

	verticalLayout_4 = new QVBoxLayout(tab_2);
	verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
	table = new QTableWidget(tab_2);
	table->setObjectName(QString::fromUtf8("table_widget"));
	table->setColumnCount(3);
	table->setHorizontalHeaderLabels({ "\320\236\320\261\320\276\320\267\320\275\320\260\321\207\320\265\320\275\320\270\320\265 \321\215\320\273\320\265\320\274\320\265\320\275\321\202\320\260  \320\275\320\260 \321\201\321\205\320\265\320\274\320\265",
		 "\320\230\320\274\321\217 \320\274\320\276\320\264\320\265\320\273\320\270",
		 "\320\255\320\272\321\201\320\277\320\273\321\203\320\260\321\202\320\260\321\206\320\270\320\276\320\275\320\275\320\276\320\271 \320\270\320\275\321\202\320\265\320\275\321\201\320\270\320\262\320\275\320\276\321\201\321\202\321\214 \320\276\321\202\320\272\320\260\320\267\320\276\320\262, (lambda)" });
	verticalLayout_4->addWidget(table);

	tab_3 = new QWidget();
	tab_3->setObjectName(QString::fromUtf8("tab_3"));
	tabWidget->addTab(tab_3, QString());
	verticalLayout_5 = new QVBoxLayout(tab_3);
	verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
	splitter = new QSplitter(tab_3);
	splitter->setObjectName(QString::fromUtf8("splitter"));
	splitter->setOrientation(Qt::Vertical);
	image_label = new QLabel(splitter);
	image_label->setObjectName(QString::fromUtf8("image_label"));
	image_object = new QImage();
	image_label->setPixmap(QPixmap::fromImage(*image_object));
	image_label->setScaledContents(TRUE);
	table2 = new QTableWidget(splitter);
	table2->setObjectName(QString::fromUtf8("table2"));
	splitter->addWidget(table2);
	tabWidget->addTab(tab_3, QString());
	verticalLayout_5->addWidget(splitter);
	table2->setRowCount(1);
	table2->setVerticalHeaderLabels({ "\320\230\320\274\321\217 \320\274\320\276\320\264\320\265\320\273\320\270" });
	table2->setAcceptDrops(false);




	mainwindow.setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
	lineEdit->setText(QString());
	pushButton->setText(QCoreApplication::translate("MainWindow",
		"\320\236\321\202\320\272\321\200\321\213\321\202\321\214 \321\204\320\260\320\271\320\273 \321\201\320\276 \321\201\321\205\320\265\320\274\320\276\320\271 (.ms14)", 
		nullptr));
	tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", 
		"\320\223\321\200\320\260\321\204\320\270\321\207\320\265\321\201\320\272\320\276\320\265 \320\277\321\200\320\265\320\264\321\201\321\202\320\260\320\262\320\273\320\265\320\275\320\270\320\265",
		nullptr));
	tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow",
		"\320\242\320\265\320\272\321\201\321\202\320\276\320\262\320\276\320\265 \320\277\321\200\320\265\320\264\321\201\321\202\320\260\320\262\320\273\320\265\320\275\320\270\320\265",
		nullptr));
	tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("MainWindow", "\320\232\320\276\320\274\320\277\320\276\320\275\320\265\320\275\321\202\321\213 \321\201\321\205\320\265\320\274\321\213", nullptr));
	pushButton_2->setText(QCoreApplication::translate("MainWindow",
		"\320\240\320\260\321\201\321\207\321\221\321\202 \320\277\320\276\320\272\320\260\320\267\320\260\321\202\320\265\320\273\320\265\320\271 \320\275\320\260\320\264\321\221\320\266\320\275\320\276\321\201\321\202\320\270",
		nullptr));
	pushButton_3->setText(QCoreApplication::translate("MainWindow",
		"\320\227\320\260\320\262\320\265\321\200\321\210\320\270\321\202\321\214 \321\200\320\260\320\261\320\276\321\202\321\203",
		nullptr));


	tabWidget->setCurrentIndex(0);
	lineEdit->setReadOnly(TRUE);


	MultisimApp = new MultisimConnectivity();
	dialogOptions = new DialogOptions(centralwidget);
	menu = new QMenu(menubar);
	menu->setObjectName(QString::fromUtf8("menu"));
	menu_1 = new QMenu(menubar);
	menu_1->setObjectName(QString::fromUtf8("menu_1"));
	menu_2 = new QMenu(menubar);
	menu_2->setObjectName(QString::fromUtf8("menu_1"));
	mainwindow.setMenuBar(menubar);
	menu->setTitle(QCoreApplication::translate("MainWindow", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270", nullptr));
	menu_1->setTitle(QCoreApplication::translate("MainWindow", "\320\222\321\213\321\205\320\276\320\264", nullptr));
	menu_2->setTitle(QCoreApplication::translate("MainWindow", "\320\236 \320\277\321\200\320\276\320\263\321\200\320\260\320\274\320\274\320\265", nullptr));

	menu->addAction("\320\235\320\260\320\271\321\201\321\202\321\200\320\276\320\271\320\272\320\260 \321\200\320\265\320\266\320\270\320\274\320\260 \321\200\320\260\320\261\320\276\321\202\321\213" ,
		this,
		SLOT(OpenOptions()));

	menubar->addAction(menu->menuAction());
	menubar->addAction(menu_1->menuAction());
	menubar->addAction(menu_2->menuAction());

	models = new DisplayOfModels(centralwidget);

	connect(pushButton, SIGNAL(released()), this, SLOT(OpenFile()));
	connect(pushButton_3, SIGNAL(released()), this, SLOT(CompleteWork()));
	connect(pushButton_2, SIGNAL(released()), this, SLOT(Calculate()));
	connect(table2, &QTableWidget::cellPressed, this, &MainWindow::ModelSelection);

	table->resizeColumnsToContents();
	table->resizeRowsToContents();

	mainwindow.showMaximized();
}


void MainWindow::OpenFile() {
	if (!scheme_path->isEmpty()) {
		delete[] Row_of_models;
	}
	*scheme_path = QFileDialog::getOpenFileName(
		this,
		"Open Multisim File",
		QDir::currentPath(),
		"Multisim files (*.ms14*)");
	lineEdit->setText(*scheme_path);
	std::cout << scheme_path << std::endl;
	try {
		MultisimApp->ClearProbes();
		components.ClearListComponent();
		MultisimApp->OpenScheme(scheme_path);
		image_object->load(MultisimApp->getSchemeImage(QDir::currentPath()));
		image_label->setPixmap(QPixmap::fromImage(*image_object));
		image_label->adjustSize();
		MultisimApp->FillListComponent(components);
		table2->setColumnCount(components.getRefComponentList().size());
		table2->setHorizontalHeaderLabels(components.getListOfSchemeMarks());
		Row_of_models = new QTableWidgetItem[components.getRefComponentList().size()];
		for (size_t i = 0; i < components.getRefComponentList().size(); i++) {
			table2->setItem(0, i, &Row_of_models[i]);
		}
		MultisimApp->FillProbes(6000);
		map<string, double> test = MultisimApp->getProbesValues();
		MultisimApp->FillProbesForComponents(components);
		for (auto it = components.getRefComponentList().begin(); it != components.getRefComponentList().end(); it++) {
			cout << "Mark " << it->scheme_mark << " Nominal " << it->nominal << " Model name " << it->model_name.toStdString() << " Probe value " << it->probe_value << endl;
		}
	}
	catch (...) {
		QMessageBox::warning(this, "\320\237\321\200\320\265\320\264\321\203\320\277\321\200\320\265\320\266\320\264\320\265\320\275\320\270\320\265",
			"\320\241\320\273\321\203\321\207\320\270\320\273\320\260\321\201\321\214 \320\276\321\210\320\270\320\261\320\272\320\260. \320\237\320\276\320\266\320\260\320\273\321\203\320\271\321\201\321\202\320\260 \320\277\321\200\320\276\320\262\320\265\321\200\321\202\320\265 \321\201\321\205\320\265\320\274\321\203 \320\270 \320\277\320\276\320\262\321\202\320\276\321\200\320\270\321\202\320\265 \321\200\320\260\321\201\321\207\321\221\321\202.");
	}
}

void MainWindow::CompleteWork() {
	mainwindow.close();
}

void MainWindow::Calculate() {
	if (scheme_path->isEmpty()) {
		QMessageBox::warning(this, "\320\237\321\200\320\265\320\264\321\203\320\277\321\200\320\265\320\266\320\264\320\265\320\275\320\270\320\265",
			"\320\222\321\213 \320\275\320\265 \320\262\321\213\320\261\321\200\320\260\320\273\320\270 \321\201\321\205\320\265\320\274\321\203 \320\264\320\273\321\217 \321\200\320\260\321\201\321\207\321\221\321\202\320\260");
	}
}

void MainWindow::OpenOptions() {
	dialogOptions->ShowFromMainWindow();
}

void MainWindow::ModelSelection() {
	models->setSchemeComponent(&components.FindByMark(table2->horizontalHeaderItem(table2->currentColumn())->text().toStdString()));
	models->ShowFromMainWindow(dialogOptions->getPriemka(), dialogOptions->getTempreture());
	table2->item(table2->currentRow(), table2->currentColumn())->setText(models->getCurrentcomponent()->model_name);
}


MainWindow::~MainWindow()
{
	delete image_object;
	delete image_label;
	components.ClearListComponent();
	if (!scheme_path->isEmpty()) {
		delete[] Row_of_models;
	}
	delete table2;
	delete splitter;
	delete verticalLayout_5;
	delete chart;
	delete scheme_path;
	delete table;
	delete verticalLayout_4;
	delete chartView;
	delete verticalLayout_3;
	delete pushButton_3;
	delete pushButton_2;
	delete tab_3;
	delete tab_2;
	delete tab;
	delete tabWidget;
	delete verticalLayout;
	delete pushButton;
	delete lineEdit;
	delete horizontalLayout;
	delete verticalLayout_2;
	delete dialogOptions;
	delete centralwidget;
	delete MultisimApp;
}