/*
This file contains the unit tests.
Unit Test Included
1. Simple Workflow (as given in sheet)
2. Multiple_Starting_Modules -> For representation, refer to Unit_Test_Cases.png inside UML Diagrams folder
3. Multiple_Middle_Modules -> For representation, refer to Unit_Test_Cases.png inside UML Diagrams folder
4. Multiple_Middle_Modules -> For representation, refer to Unit_Test_Cases.png inside UML Diagrams folder

Please compare against the actual corresponding outputs (with the same test name) in the Outputs folder.
*/


#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <iostream>
#include <memory>
#include <numeric>

#include "Process.h"
#include "Module.h"
#include "Connect.h"

using ::testing::AtLeast;
using ::testing::Return;
using ::testing::_;
using namespace std;

class MockModule : public Module {
public:
	MOCK_METHOD(string, GetType, (), (const));
	MOCK_METHOD(string, GetName, (), (const));
	MOCK_METHOD(string, Process, (string input), (final));
};

/*This is the simple workflow as given in the sheet*/
TEST(ProcessTest, Workflow_In_Sheet)
{
	vector<shared_ptr<Module>> createdModules;
	vector<string> outputs;

	shared_ptr<MockModule> reverseModuleMock = make_shared<MockModule>();
	EXPECT_CALL(*reverseModuleMock, GetType())
		.Times(1)
		.WillOnce(Return("reverse"));
	EXPECT_CALL(*reverseModuleMock, GetName())
		.Times(2)
		.WillRepeatedly(Return("alpha"));
	EXPECT_CALL(*reverseModuleMock, Process(_))
		.Times(2)
		.WillOnce(Return("olleh"))
		.WillOnce(Return("dlrow"));

	shared_ptr<MockModule> delayModuleMock = make_shared<MockModule>();
	EXPECT_CALL(*delayModuleMock, GetType())
		.Times(1)
		.WillOnce(Return("delay"));
	EXPECT_CALL(*delayModuleMock, GetName())
		.Times(1)
		.WillOnce(Return("beta"));
	EXPECT_CALL(*delayModuleMock, Process(_))
		.Times(3)
		.WillOnce(Return("hello"))
		.WillOnce(Return("olleh"))
		.WillOnce(Return("dlrow"));

	createdModules.emplace_back(reverseModuleMock);
	createdModules.emplace_back(delayModuleMock);

	Connect::ConnectModules(createdModules, vector<string>{ "alpha", "beta" });

	outputs = Process::ProcessWords(createdModules, vector<string>{"hello", "world"});
	Process::ProcessRemainingDelayWords(createdModules, outputs);

	EXPECT_EQ(outputs.size(), 3);

	string output;
	for (const auto &word : outputs)
	{
		output += word;
		output += " ";
	}

	EXPECT_EQ(output, "hello olleh dlrow ");
}

/* This is the workflow with two starting modules. In this case,
each input goes to both the starting modules*/

TEST(ProcessTest, Starting_Modules_Split)
{
	vector<shared_ptr<Module>> createdModules;
	vector<string> outputs;

	shared_ptr<MockModule> echoModuleMock = make_shared<MockModule>();
	EXPECT_CALL(*echoModuleMock, GetType())
		.Times(AtLeast(1))
		.WillRepeatedly(Return("echo"));
	EXPECT_CALL(*echoModuleMock, GetName())
		.Times(AtLeast(1))
		.WillRepeatedly(Return("alpha"));
	EXPECT_CALL(*echoModuleMock, Process(_))
		.Times(2)
		.WillOnce(Return("hellohello"))
		.WillOnce(Return("worldworld"));

	shared_ptr<MockModule> delayModuleMock = make_shared<MockModule>();
	EXPECT_CALL(*delayModuleMock, GetType())
		.Times(AtLeast(1))
		.WillOnce(Return("delay"));
	EXPECT_CALL(*delayModuleMock, GetName())
		.Times(AtLeast(1))
		.WillRepeatedly(Return("beta"));
	EXPECT_CALL(*delayModuleMock, Process(_))
		.Times(3)
		.WillOnce(Return("hello"))
		.WillOnce(Return("hello"))
		.WillOnce(Return("world"));

	shared_ptr<MockModule> noopModuleMock = make_shared<MockModule>();
	EXPECT_CALL(*noopModuleMock, GetType())
		.Times(AtLeast(1))
		.WillRepeatedly(Return("noop"));
	EXPECT_CALL(*noopModuleMock, GetName())
		.Times(AtLeast(1))
		.WillRepeatedly(Return("gama"));
	EXPECT_CALL(*noopModuleMock, Process(_))
		.Times(AtLeast(2))
		.WillOnce(Return("hellohello"))
		.WillOnce(Return("hello"))
		.WillOnce(Return("worldworld"))
		.WillOnce(Return("hello"))
		.WillOnce(Return("world"));

	shared_ptr<MockModule> reverseModuleMock = make_shared<MockModule>();
	EXPECT_CALL(*reverseModuleMock, GetType())
		.Times(AtLeast(1))
		.WillRepeatedly(Return("reverse"));
	EXPECT_CALL(*reverseModuleMock, GetName())
		.Times(AtLeast(1))
		.WillOnce(Return("eps"));
	EXPECT_CALL(*reverseModuleMock, Process(_))
		.Times(AtLeast(1))
		.WillOnce(Return("olleholleh"))
		.WillOnce(Return("olleh"))
		.WillOnce(Return("dlrowdlrow"))
		.WillOnce(Return("olleh"))
		.WillOnce(Return("dlrow"));

	createdModules.emplace_back(echoModuleMock);
	createdModules.emplace_back(delayModuleMock);
	createdModules.emplace_back(noopModuleMock);
	createdModules.emplace_back(reverseModuleMock);

	Connect::ConnectModules(createdModules, vector<string>{ "alpha", "gama" });
	Connect::ConnectModules(createdModules, vector<string>{ "beta", "gama" });
	Connect::ConnectModules(createdModules, vector<string>{ "gama", "eps" });

	outputs = Process::ProcessWords(createdModules, vector<string>{"hello", "world"});
	Process::ProcessRemainingDelayWords(createdModules, outputs);

	EXPECT_EQ(outputs.size(), 5);

	string output;
	for (const auto &word : outputs)
	{
		output += word;
		output += " ";
	}

	EXPECT_EQ(output, "olleholleh olleh dlrowdlrow olleh dlrow ");
}

/* This is the workflow with two parallel middle modules i.e; one module is split into
two and then later combined as input into another module*/

TEST(ProcessTest, Middle_Modules_Split)
{
	vector<shared_ptr<Module>> createdModules;
	vector<string> outputs;

	shared_ptr<MockModule> echoModuleMock = make_shared<MockModule>();
	EXPECT_CALL(*echoModuleMock, GetType())
		.Times(AtLeast(1))
		.WillRepeatedly(Return("echo"));
	EXPECT_CALL(*echoModuleMock, GetName())
		.Times(AtLeast(1))
		.WillRepeatedly(Return("alpha"));
	EXPECT_CALL(*echoModuleMock, Process(_))
		.Times(AtLeast(1))
		.WillOnce(Return("hellohello"))
		.WillOnce(Return("hellohello"))
		.WillOnce(Return("worldworld"))
		.WillOnce(Return("worldworld"));

	shared_ptr<MockModule> delayModuleMockOne = make_shared<MockModule>();
	EXPECT_CALL(*delayModuleMockOne, GetType())
		.Times(AtLeast(1))
		.WillRepeatedly(Return("delay"));
	EXPECT_CALL(*delayModuleMockOne, GetName())
		.Times(AtLeast(1))
		.WillRepeatedly(Return("beta"));
	EXPECT_CALL(*delayModuleMockOne, Process(_))
		.Times(AtLeast(1))
		.WillOnce(Return("hello"))
		.WillOnce(Return("hellohello"))
		.WillOnce(Return("worldworld"));


	shared_ptr<MockModule> delayModuleMockTwo = make_shared<MockModule>();
	EXPECT_CALL(*delayModuleMockTwo, GetType())
		.Times(AtLeast(1))
		.WillRepeatedly(Return("delay"));
	EXPECT_CALL(*delayModuleMockTwo, GetName())
		.Times(AtLeast(1))
		.WillRepeatedly(Return("gama"));
	EXPECT_CALL(*delayModuleMockTwo, Process(_))
		.Times(AtLeast(1))
		.WillOnce(Return("hello"))
		.WillOnce(Return("hellohello"))
		.WillOnce(Return("worldworld"));


	shared_ptr<MockModule> noopModuleMock = make_shared<MockModule>();
	EXPECT_CALL(*noopModuleMock, GetType())
		.Times(AtLeast(1))
		.WillRepeatedly(Return("noop"));
	EXPECT_CALL(*noopModuleMock, GetName())
		.Times(AtLeast(1))
		.WillRepeatedly(Return("eps"));
	EXPECT_CALL(*noopModuleMock, Process(_))
		.Times(AtLeast(2))
		.WillOnce(Return("hello"))
		.WillOnce(Return("hello"))
		.WillOnce(Return("hellohello"))
		.WillOnce(Return("hellohello"))
		.WillOnce(Return("worldworld"))
		.WillOnce(Return("worldworld"));

	shared_ptr<MockModule> reverseModuleMock = make_shared<MockModule>();
	EXPECT_CALL(*reverseModuleMock, GetType())
		.Times(AtLeast(1))
		.WillRepeatedly(Return("reverse"));
	EXPECT_CALL(*reverseModuleMock, GetName())
		.Times(AtLeast(1))
		.WillRepeatedly(Return("sigma"));
	EXPECT_CALL(*reverseModuleMock, Process(_))
		.Times(AtLeast(1))
		.WillOnce(Return("olleh"))
		.WillOnce(Return("olleh"))
		.WillOnce(Return("olleholleh"))
		.WillOnce(Return("olleholleh"))
		.WillOnce(Return("dlrowdlrow")).WillOnce(Return("dlrowdlrow"));

	createdModules.emplace_back(echoModuleMock);
	createdModules.emplace_back(delayModuleMockOne);
	createdModules.emplace_back(delayModuleMockTwo);
	createdModules.emplace_back(noopModuleMock);
	createdModules.emplace_back(reverseModuleMock);

	Connect::ConnectModules(createdModules, vector<string>{ "alpha", "beta" });
	Connect::ConnectModules(createdModules, vector<string>{ "alpha", "gama" });
	Connect::ConnectModules(createdModules, vector<string>{ "beta", "eps" });
	Connect::ConnectModules(createdModules, vector<string>{ "gama", "eps" });
	Connect::ConnectModules(createdModules, vector<string>{ "eps", "sigma" });

	outputs = Process::ProcessWords(createdModules, vector<string>{"hello", "world"});
	Process::ProcessRemainingDelayWords(createdModules, outputs);

	EXPECT_EQ(outputs.size(), 6);

	string output;
	for (const auto &word : outputs)
	{
		output += word;
		output += " ";
	}

	EXPECT_EQ(output, "olleh olleh olleholleh olleholleh dlrowdlrow dlrowdlrow ");
}

/*This is the workflow with multiple output module i.e The output of module behind final output is
split as input into two modules*/
TEST(ProcessTest, Output_Modules_Split)
{
	vector<shared_ptr<Module>> createdModules;
	vector<string> outputs;

	shared_ptr<MockModule> echoModuleMock = make_shared<MockModule>();
	EXPECT_CALL(*echoModuleMock, GetType())
		.Times(AtLeast(1))
		.WillRepeatedly(Return("echo"));
	EXPECT_CALL(*echoModuleMock, GetName())
		.Times(AtLeast(1))
		.WillRepeatedly(Return("alpha"));
	EXPECT_CALL(*echoModuleMock, Process(_))
		.Times(2)
		.WillOnce(Return("hellohello"))
		.WillOnce(Return("worldworld"));

	shared_ptr<MockModule> delayModuleMock = make_shared<MockModule>();
	EXPECT_CALL(*delayModuleMock, GetType())
		.Times(AtLeast(1))
		.WillRepeatedly(Return("delay"));
	EXPECT_CALL(*delayModuleMock, GetName())
		.Times(AtLeast(1))
		.WillRepeatedly(Return("beta"));
	EXPECT_CALL(*delayModuleMock, Process(_))
		.Times(AtLeast(1))
		.WillOnce(Return("hello"))
		.WillOnce(Return("hello"))
		.WillOnce(Return("hellohello"))
		.WillOnce(Return("hellohello"))
		.WillOnce(Return("worldworld"))
		.WillOnce(Return("worldworld"));

	shared_ptr<MockModule> noopModuleMock = make_shared<MockModule>();
	EXPECT_CALL(*noopModuleMock, GetType())
		.Times(AtLeast(1))
		.WillRepeatedly(Return("noop"));
	EXPECT_CALL(*noopModuleMock, GetName())
		.Times(AtLeast(1))
		.WillRepeatedly(Return("gama"));
	EXPECT_CALL(*noopModuleMock, Process(_))
		.Times(AtLeast(2))
		.WillOnce(Return("hello"))
		.WillOnce(Return("hellohello"))
		.WillOnce(Return("worldworld"));

	shared_ptr<MockModule> reverseModuleMock = make_shared<MockModule>();
	EXPECT_CALL(*reverseModuleMock, GetType())
		.Times(AtLeast(1))
		.WillRepeatedly(Return("reverse"));
	EXPECT_CALL(*reverseModuleMock, GetName())
		.Times(AtLeast(1))
		.WillRepeatedly(Return("eps"));
	EXPECT_CALL(*reverseModuleMock, Process(_))
		.Times(AtLeast(1))
		.WillOnce(Return("olleh"))
		.WillOnce(Return("olleholleh"))
		.WillOnce(Return("dlrowdlrow"));

	createdModules.emplace_back(echoModuleMock);
	createdModules.emplace_back(delayModuleMock);
	createdModules.emplace_back(noopModuleMock);
	createdModules.emplace_back(reverseModuleMock);

	Connect::ConnectModules(createdModules, vector<string>{ "alpha", "beta" });
	Connect::ConnectModules(createdModules, vector<string>{ "beta", "gama" });
	Connect::ConnectModules(createdModules, vector<string>{ "beta", "eps" });

	outputs = Process::ProcessWords(createdModules, vector<string>{"hello", "world"});
	Process::ProcessRemainingDelayWords(createdModules, outputs);

	EXPECT_EQ(outputs.size(), 6);

	string output;
	for (const auto &word : outputs)
	{
		output += word;
		output += " ";
	}

	EXPECT_EQ(output, "hello olleh hellohello olleholleh worldworld dlrowdlrow ");
}

int main(int argc, char** argv) {
	::testing::InitGoogleMock(&argc, argv);
	RUN_ALL_TESTS();
	system("pause");
	return 0;
}