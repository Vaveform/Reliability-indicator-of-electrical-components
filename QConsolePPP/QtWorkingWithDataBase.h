#pragma once

#include "DisplayOfModels.h"
#include "ComponentList.h"
#include <string>


using namespace std;


void SelectionOfModelInTableView(QSqlDatabase* db, QString* sql_request, QSqlQuery* query, QSqlQueryModel* QueryModel, QTableView* table);

void FillComponent(QSqlDatabase* db, _component* c, double priemka, QString tempreture);