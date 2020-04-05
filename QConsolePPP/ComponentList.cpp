#include "ComponentList.h"

void Component_List::ClearListComponent() {
	component_list.clear();
}

void Component_List::AddComponent(_component c) {
	component_list.push_back(c);
}

std::vector<_component>& Component_List::getRefComponentList() {
	return component_list;
}


QStringList Component_List::getListOfSchemeMarks() {
	QStringList list_names;
	for (size_t i = 0; i < component_list.size(); i++) {
		list_names.push_back(QString::fromStdString(component_list[i].scheme_mark));
	}
	return list_names;
}

_component& Component_List::FindByMark(const std::string& mark) {
	return *find_if(component_list.begin(), component_list.end(), [&mark] (_component& elem) {
		return elem.scheme_mark == mark;
	});
}

_component& Component_List::FindByModelName(const QString& model_name) {
	return *find_if(component_list.begin(), component_list.end(), [&model_name](_component& elem) {
		return elem.model_name == model_name;
	});
}