/*
Refer to Connect.h
*/

#include<string>
#include<list>
#include<vector>
#include<algorithm>
#include<memory>

#include <Module.h>
#include "Connect.h"

using namespace std;


Connect::Connect()
{
}

void Connect::ConnectModules(vector<shared_ptr<Module>>& existingModules, const vector<string>& modulesNames)
{
	//code duplication - maybe use lambda

	//auto iteratorName = [&](const auto& moduleName) {
	//	return std::find_if(existingModules.begin(), existingModules.end(), [&moduleName](shared_ptr<Module>& module)
	//		{
	//		return module->GetName() == moduleName;
	//		});
	//};

	//auto iteratorNameOne = iteratorName(modulesNames[0]);
	auto iteratorNameOne = std::find_if(existingModules.begin(), existingModules.end(), [&modulesNames](shared_ptr<Module>& module)
	{
		return module->GetName() == modulesNames[0];
	});

	auto iteratorNameTwo = std::find_if(existingModules.begin(), existingModules.end(), [&modulesNames](shared_ptr<Module>& module)
	{
		return module->GetName() == modulesNames[1];
	});

	if ((iteratorNameOne != existingModules.end()) && (iteratorNameTwo != existingModules.end()))
	{
		(*iteratorNameOne)->next.emplace_back(*iteratorNameTwo);
		++((*iteratorNameTwo)->inputConnections);
	}
}

Connect::~Connect()
{
}
