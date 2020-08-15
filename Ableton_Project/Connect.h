/*
The class does the connection between two modules.
*/
#pragma once
#include<string>
#include<vector>
#include<list>
#include<memory>

class Module;

class Connect
{
public:
	Connect();
	static void ConnectModules(std::vector<std::shared_ptr<Module>>& existingModules, const std::vector<std::string>& modulesNames);
	~Connect();
};

