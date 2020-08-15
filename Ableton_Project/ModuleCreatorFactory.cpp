/*Refer to ModuleCreatorFactory.h*/

#include<memory>
#include<list>

#include <Module.h>
#include "ModuleCreatorFactory.h"

using namespace std;

ModuleCreatorFactory::ModuleCreatorFactory()
{
}

std::unique_ptr<Module> ModuleCreatorFactory::CreateModule(const string& name, const string& type)
{
	if (type == "echo")
	{
		return make_unique<EchoModule>(name, type);
	}
	else if (type == "reverse")
	{
		return make_unique<ReverseModule>(name, type);
	}
	else if (type == "noop")
	{
		return make_unique<NoopModule>(name, type);
	}
	else
	{
		return make_unique<DelayModule>(DelayModule::CtorProtector(), name, type);
	}
}

ModuleCreatorFactory::~ModuleCreatorFactory()
{
}
