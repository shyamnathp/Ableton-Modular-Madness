/*
Factory Class to create different types of Module
*/

#pragma once
#include<memory>
#include<list>

class Module;

class ModuleCreatorFactory
{
public:
	ModuleCreatorFactory();
	//this function created the module based on type
	static std::unique_ptr<Module> CreateModule(const string& name, const string& type);
	~ModuleCreatorFactory();
};

