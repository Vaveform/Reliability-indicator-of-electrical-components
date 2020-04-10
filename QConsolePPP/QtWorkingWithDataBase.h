#pragma once

#include "DisplayOfModels.h"
#include "ComponentList.h"
#include <string>


void SelectionOfModelInTableView(QSqlDatabase* db, QString* sql_request, QSqlQuery* query, QSqlQueryModel* QueryModel, QTableView* table);

void FillComponent(_component* c, double priemka, QString tempreture);

bool ComparisonParser(QString& comp, double lhd_val, double rhd_val);

double getValueFromKpTables(QSqlQuery* query, QString Name_of_Kp_table, QString tempreture, double nominal_ratio);

double getValueFromNominalSelectiveTables(QSqlQuery* query, QString Name_of_table, double nominal);

void CalculateForResistors(_component* c, double priemka, QString tempreture);

void CalculateForCapacitors(_component* c, double priemka, QString tempreture);

void CalculateForInductors(_component* c, double priemka, QString tempreture);

void CalculateForDiodes(_component* c, double priemka, QString tempreture);

void CalculateForTransistors(_component* c, double priemka, QString tempreture);