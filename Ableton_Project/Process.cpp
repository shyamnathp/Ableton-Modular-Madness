/*
Refer to header for description
*/

#include<string>
#include<list>
#include<vector>
#include<algorithm>

#include<Module.h>
#include "Process.h"

namespace{
	/* find the starting modules. There maybe multiple starting modules.*/
	vector<shared_ptr<Module>> FindStartingModules(const vector<shared_ptr<Module>>& createdModules)
	{
		vector<shared_ptr<Module>> startingModules;

		for (const auto& module : createdModules)
		{
			if (module->inputConnections == 0)
				startingModules.emplace_back(module);
		}

		return startingModules;
	}

	/*Finding the outputs recursively starting from the module 'module'.
	The use of recursion is considering that the middle and output modules may be split*/
	void FindOutputs(vector<string>& outputs, shared_ptr<Module> module, string input)
	{
		if ((module->next).size() == 0)
		{
			outputs.emplace_back(module->Process(input));
			return;
		}

		string output = module->Process(input);

		for (const auto& nextModule : module->next)
		{
			FindOutputs(outputs, nextModule, output);
		}
	}

	/*Find the modules with remaining inputs to be processed, in paths from each starting module i.e delay modules*/
	void FindDelayedModules(vector<shared_ptr<Module>>& delayedModules, shared_ptr<Module> module)
	{
		if (module->GetType() == "delay")
		{
			delayedModules.emplace_back(module);
		}

		for (const auto& nextModule : module->next)
		{
			FindDelayedModules(delayedModules, nextModule);
		}
	}
}


Process::Process()
{
}

vector<string> Process::ProcessWords(vector<shared_ptr<Module>>& createdModules, vector<string>& inputs)
{
	vector<string> outputs;
	vector<shared_ptr<Module>> startingModules = FindStartingModules(createdModules);

	for (auto& input : inputs)
	{
		for (auto& startingModule : startingModules)
		{
			FindOutputs(outputs, startingModule, input);
		}
	}	

	return outputs;
}

/*After this step,all the delay modules will now have previous input as "hello"*/
void Process::ProcessRemainingDelayWords(vector<shared_ptr<Module>>& createdModules, vector<string>& outputs)
{
	vector<shared_ptr<Module>> delayedModules;
	vector<shared_ptr<Module>> startingModules = FindStartingModules(createdModules);

	for (auto& startingModule : startingModules)
	{
		FindDelayedModules(delayedModules, startingModule);
	}

	for (const auto& delayedModule : delayedModules)
	{
		FindOutputs(outputs, delayedModule, "hello");
	}
}

Process::~Process()
{
}
