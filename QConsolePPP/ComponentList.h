#pragma once

#include <vector>
#include <map>
#include <QString>
#include <string>
#include <QStringList>
#include <algorithm>

enum class TypeOfComponent {
	ComponentResistor = 2,
	ComponentCapacitor = 3,
	ComponentInductor = 4
};

struct _component {
	std::string scheme_mark;
	double nominal;
	TypeOfComponent type_component;
	QString model_name;
	double probe_value;
	double realibility_idx;
};


class Component_List {
private:
	std::vector<_component> component_list;
public:
	void ClearListComponent();
	void AddComponent(_component c);
	std::vector<_component>& getRefComponentList();
	QStringList getListOfSchemeMarks();
	_component& FindByMark(const std::string& mark);
	_component& FindByModelName(const QString& model_name);
};