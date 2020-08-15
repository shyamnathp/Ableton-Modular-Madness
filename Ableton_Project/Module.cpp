/*
Refere to Module.h
*/
#include<string>
#include<algorithm>

#include "Module.h"

using namespace std;

Module::Module()
{
}

Module::~Module()
{
}

string Module::GetName() const
{
	return this->name;
}

string Module::GetType() const
{
	return this->type;
}

/* Definitions for EchoModule*/

string EchoModule::Process(string input)
{
	string output = input + input;
	return output;
}

/* Definitions for ReverseModule*/

string ReverseModule::Process(string input)
{
	string output = input;
	std::reverse(output.begin(), output.end());
	return output;
}

/* Definitions for NoopModule*/

string NoopModule::Process(string input)
{
	string output = input;
	return output;
}

/* Definitions for DelayModule*/

string DelayModule::Process(string input)
{
	/* Check for error here*/
	string output = previousInput;
	previousInput = input;
	return output;
}


