#include "DisplayOfModels.h"

DisplayOfModels::DisplayOfModels(QWidget* widget) {
	dialog = new QDialog(widget);
	dialog->setObjectName(QString::fromUtf8("dialog"));
	dialog->setEnabled(true);
	dialog->resize(701, 461);
	dialog->setFixedSize(dialog->size());
	verticalLayout = new QVBoxLayout(dialog);
	verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
	splitter = new QSplitter(dialog);
	splitter->setObjectName(QString::fromUtf8("splitter"));
	splitter->setOrientation(Qt::Horizontal);
	lineEdit = new QLineEdit(splitter);
	lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
	lineEdit->setReadOnly(true);
	splitter->addWidget(lineEdit);
	pushButton = new QPushButton(splitter);
	pushButton->setObjectName(QString::fromUtf8("pushButton"));
	splitter->addWidget(pushButton);

	verticalLayout->addWidget(splitter);

	tableWidget = new QTableView(dialog);
	tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
	tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);


	verticalLayout->addWidget(tableWidget);

	buttonBox = new QDialogButtonBox(dialog);
	buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
	buttonBox->setOrientation(Qt::Horizontal);
	buttonBox->setStandardButtons(QDialogButtonBox::Cancel | QDialogButtonBox::Ok);

	verticalLayout->addWidget(buttonBox);

	path_to_db = new QString();

	dialog->setWindowTitle(QCoreApplication::translate("dialog", "dialog", nullptr));
	pushButton->setText(QCoreApplication::translate("Dialog", 
		"\320\222\321\213\320\261\321\200\320\260\321\202\321\214 \320\261\320\260\320\267\321\203 \320\264\320\260\320\275\320\275\321\213\321\205 \321\200\320\260\320\264\320\270\320\276\321\215\320\273\320\265\320\274\320\265\320\275\321\202\320\276\320\262",
		nullptr));

	db = new QSqlDatabase();
	*db = QSqlDatabase::addDatabase("QSQLITE");
	QueryModel = new QSqlQueryModel();
	qry = new QSqlQuery();
	sql_request = new QString();

	connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
	connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
	connect(pushButton, SIGNAL(released()), this, SLOT(OpenDB()));
	connect(tableWidget, &QTableView::pressed, this, &DisplayOfModels::SetSelectedModel);

}


void DisplayOfModels::accept() {
	if (selected_component->model_name.isEmpty()) {
		QMessageBox::warning(this ,"\320\237\321\200\320\265\320\264\321\203\320\277\321\200\320\265\320\266\320\264\320\265\320\275\320\270\320\265",
			"\320\222\321\213 \320\275\320\265 \320\262\321\213\320\261\321\200\320\260\320\273\320\270 \320\274\320\276\320\264\320\265\320\273\321\214");
	}
	else {
		dialog->close();
	}
}

void DisplayOfModels::reject() {
	dialog->close();
}

void DisplayOfModels::setSchemeComponent(_component* c) {
	selected_component = c;
}

void DisplayOfModels::FindAvailableComponents() {
	if (selected_component->type_component == TypeOfComponent::ComponentResistor) {
		db->open();
		*sql_request = "SELECT Model, Class, Group_Model FROM Resistors";
		qry->exec(*sql_request);
		QueryModel->setQuery(*qry);
		tableWidget->setModel(QueryModel);
		tableWidget->resizeRowsToContents();
		tableWidget->resizeColumnsToContents();
		db->close();
	}
	else if (selected_component->type_component == TypeOfComponent::ComponentCapacitor) {
		db->open();
		*sql_request = "SELECT Model, Class, Group_Model FROM Condensatory";
		qry->exec(*sql_request);
		QueryModel->setQuery(*qry);
		tableWidget->setModel(QueryModel);
		tableWidget->resizeRowsToContents();
		tableWidget->resizeColumnsToContents();
		db->close();
	}
	else if (selected_component->type_component == TypeOfComponent::ComponentInductor) {
	    db->open();
		*sql_request = "SELECT Model, Class, Group_Model FROM Drosseli";
		qry->exec(*sql_request);
		QueryModel->setQuery(*qry);
		tableWidget->setModel(QueryModel);
		tableWidget->resizeRowsToContents();
		tableWidget->resizeColumnsToContents();
		db->close();
	}
}

void DisplayOfModels::OpenDB() {
	*path_to_db = QFileDialog::getOpenFileName(
		this,
		"Select Database File",
		QDir::currentPath(),
		"Database files (*.db*)");
	lineEdit->setText(*path_to_db);	
	db->setDatabaseName(*path_to_db);
	this->FindAvailableComponents();
}

void DisplayOfModels::ShowFromMainWindow() {
	this->FindAvailableComponents();
	dialog->exec();
	//dialog->show();
}

void DisplayOfModels::SetSelectedModel() {
	selected_component->model_name = tableWidget->selectionModel()->selectedRows(0).value(0).data().toString();
}

_component* DisplayOfModels::getCurrentcomponent() {
	return selected_component;
}

DisplayOfModels::~DisplayOfModels() {
	delete path_to_db;
	delete buttonBox;
	delete tableWidget;
	delete pushButton;
	delete splitter;
	delete verticalLayout;
	delete dialog;
	delete db;
	delete QueryModel;
	delete qry;
	delete sql_request;
}