/*
This class manages all the processing operations.
*/

#pragma once
#include<string>
#include<list>
#include<vector>

class Module;

class Process
{
public:
	Process();
	/*Process the inputs sequentially by passing through modules.*/
	static std::vector<std::string> ProcessWords(std::vector<std::shared_ptr<Module>>& createdModules, std::vector<std::string>& inputs);
	/*Process the remaining previous inputs in the delay modules*/
	static void ProcessRemainingDelayWords(std::vector<std::shared_ptr<Module>>& createdModules, std::vector<std::string>& outputs);
	~Process();
};

