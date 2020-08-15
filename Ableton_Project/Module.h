/*
The declaration class for Module and its different inherited versions.
*/

#pragma once

/*
This file contained the Module class and its derived classes: Echo, Reverse, Noop, Delay
*/

#include<string>
#include<list>
using namespace std;

class ModuleCreatorFactory;

class Module
{
public:
	Module();
	Module(string passedName, string passedType) : name(passedName), type(passedType)
	{}
	int inputConnections = 0;
	list<shared_ptr<Module>> next;
	virtual string GetName() const;
	virtual string GetType() const;
	virtual string Process(string input) = 0;
	virtual ~Module();
private:
	string name;
	string type;
};

class EchoModule :public Module
{
public:
	EchoModule(string passedName, string passedType) :Module(passedName, passedType) 
	{}
	virtual string Process(string input) final;
private:
	friend class ModuleCreatorFactory;
};

class ReverseModule :public Module
{
public:
	ReverseModule(string passedName, string passedType) :Module(passedName, passedType) 
	{}
	virtual string Process(string input) final;
private:
	friend class ModuleCreatorFactory;
};

class NoopModule :public Module
{
public:
	NoopModule(string passedName, string passedType) :Module(passedName, passedType) 
	{}
	virtual string Process(string input) final;
private:
	friend class ModuleCreatorFactory;
};

class DelayModule :public Module
{
private:
	struct CtorProtector
	{
	};
	friend class ModuleCreatorFactory;
	string previousInput;
public:
	DelayModule(CtorProtector, string passedName, string passedType) :Module(passedName, passedType), previousInput("hello")
	{}
	virtual string Process(string input) final;
};





