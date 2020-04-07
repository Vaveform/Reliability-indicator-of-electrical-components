#include "QtWorkingWithDataBase.h"


// Show database table produced by query and sql_request in QTableView
void SelectionOfModelInTableView(QSqlDatabase* db, QString* sql_request, QSqlQuery* query, QSqlQueryModel* QueryModel, QTableView* table) {
	db->open();
	query->exec(*sql_request);
	QueryModel->setQuery(*query);
	table->setModel(QueryModel);
	table->resizeRowsToContents();
	table->resizeColumnsToContents();
	db->close();
}

// Comparison parser for working with tables
bool ComparisonParser(QString& comp, double lhd_val, double rhd_val) {
	if (comp == "<") {
		return lhd_val < rhd_val;
	}
	else if (comp == "<=") {
		return lhd_val <= rhd_val;
	}
	else if (comp == ">") {
		return lhd_val > rhd_val;
	}
	else if (comp == ">=") {
		return lhd_val >= rhd_val;
	}
	else if (comp == "==") {
		return lhd_val == rhd_val;
	}
	else if (comp == "!=") {
		return lhd_val != rhd_val;
	}
	else {
		return true;
	}
}


// This function work only, if database opened. To use this function you should before calling this function use method of db open()
double getValueFromKpTables(QSqlQuery* query, QString Name_of_Kp_table, QString tempreture, double nominal_ratio) {
	QString column_value = QString::fromStdString(std::to_string(nominal_ratio));
	column_value.resize(3);
	query->exec("SELECT \"" + column_value + "\" FROM " + Name_of_Kp_table + " WHERE Tempreture = " + "'" + tempreture + "'");
	query->next();
	return query->value(0).toDouble();
}

// This function work only, if database opened. To use this function you should before calling this function use method of db open()
double getValueFromNominalSelectiveTables(QSqlQuery* query, QString Name_of_table, double nominal) {
	query->exec("SELECT * FROM " + Name_of_table);
	QStringList list_of_tokens;
	while (query->next()) {
		list_of_tokens = query->value(0).toString().split(' ');
		if (list_of_tokens.size() == 2) {
			if (ComparisonParser(list_of_tokens[0], nominal, list_of_tokens[1].toDouble())) {
				return query->value(1).toDouble();
			}
		}
		else {
			if (ComparisonParser(list_of_tokens[0], nominal, list_of_tokens[1].toDouble()) &&
				ComparisonParser(list_of_tokens[2], nominal, list_of_tokens[3].toDouble())) {
				return query->value(1).toDouble();
			}
		}
	}
}

void CalculateForResistors(QSqlDatabase* db, _component* c, double priemka, QString tempreture) {
	db->open();
	c->realibility_idx = -1;
	QSqlQuery query;
	QString sql_request = "SELECT * FROM Resistors WHERE Model = ";
	sql_request = sql_request + "'" + c->model_name + "'";
	query.exec(sql_request);
	query.next();
	double lambda = query.value(4).toDouble() / 1000000.0;
	c->realibility_idx = lambda;
	// Kp - nominal_ratio
	double nominal_ratio = int(c->probe_value / query.value(5).toDouble() * 10) / 10.0;
	nominal_ratio = nominal_ratio < 0.1 ? 0.1 : nominal_ratio;
	if (nominal_ratio > 1) {
		throw(invalid_argument("Please, reduce voltage"));
	}
	QString Kp_table = query.value(8).toString();
	QString Kr_table = query.value(7).toString();
	// Kpr value
	c->realibility_idx *= priemka == 5 ? 1 : 0.3;
	// Kp value
	c->realibility_idx *= getValueFromKpTables(&query, Kp_table, tempreture, nominal_ratio);
	// Kr value
	c->realibility_idx *= getValueFromNominalSelectiveTables(&query, Kr_table, c->nominal);
}

void CalculateForCapacitors(QSqlDatabase* db, _component* c, double priemka, QString tempreture) {
	db->open();
	c->realibility_idx = -1;
	QSqlQuery query;
	QString sql_request = "SELECT * FROM Condensatory WHERE Model = ";
	sql_request = sql_request + "'" + c->model_name + "'";
	query.exec(sql_request);
	query.next();
	double lambda = query.value(4).toDouble()/ 1000000.0;
	c->realibility_idx = lambda;
	// Kp - nominal_ratio
	double nominal_ratio = int(c->probe_value / query.value(11).toDouble() * 10) / 10.0;
	nominal_ratio = nominal_ratio < 0.1 ? 0.1 : nominal_ratio;
	if (nominal_ratio > 1) {
		throw(invalid_argument("Please, reduce voltage"));
	}
	QString Kp_table = query.value(5).toString();
	QString Kc = query.value(6).toString();
	QString Kt = query.value(9).toString();
	// Kp value
	c->realibility_idx *= getValueFromKpTables(&query, Kp_table, tempreture, nominal_ratio);
	// Kpr value
	c->realibility_idx *= priemka == 5 ? 1 : 0.3;
	// Kt
	if (Kt != "1") {
		sql_request = "SELECT Kt FROM " + Kt + " WHERE Tempreture = \'" + tempreture + "\'";
		query.exec(sql_request);
		query.next();
		c->realibility_idx *= query.value(0).toDouble();
	}
	// Kc
	if (Kc.size() == 1) {
		c->realibility_idx *= 1;
	}
	else if (Kc.split('^').size() == 2) {
		c->realibility_idx *=  Kc.split('*')[0].toDouble() * pow(c->nominal, Kc.split('^')[1].toDouble());
	}
	else {
		c->realibility_idx *= getValueFromNominalSelectiveTables(&query, Kc, c->nominal);
	}
	db->close();
}

void CalculateForInductors(QSqlDatabase* db, _component* c, double priemka, QString tempreture) {
	db->open();
	c->realibility_idx = -1;
	QSqlQuery query;
	QString sql_request = "SELECT * FROM Drosseli WHERE Model = ";
	sql_request = sql_request + "'" + c->model_name + "'";
	query.exec(sql_request);
	query.next();
	double lambda = query.value(3).toDouble() / 1000000.0;
	c->realibility_idx = lambda;
	// Kp - nominal ratio
	double nominal_ratio = int(c->probe_value / query.value(7).toDouble() * 10) / 10.0;
	nominal_ratio = nominal_ratio < 0.1 ? 0.1 : nominal_ratio;
	if (nominal_ratio > 1) {
		throw(invalid_argument("Please, reduce voltage"));
	}
	QString Kp_table = query.value(4).toString();
	// Kp value
	c->realibility_idx *= getValueFromKpTables(&query, Kp_table, tempreture, nominal_ratio);
	// Kpr value
	c->realibility_idx *= priemka == 5 ? 1 : 0.2;
	db->close();
}

void FillComponent(QSqlDatabase* db, _component* c, double priemka, QString tempreture) {
	if (c->type_component == TypeOfComponent::ComponentCapacitor) {
		CalculateForCapacitors(db, c, priemka, tempreture);
	}
	else if (c->type_component == TypeOfComponent::ComponentResistor) {
		CalculateForResistors(db, c, priemka, tempreture);
	}
	else if (c->type_component == TypeOfComponent::ComponentInductor) {
		CalculateForInductors(db, c, priemka, tempreture);
	}

}

