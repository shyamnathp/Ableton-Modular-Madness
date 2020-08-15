/*
This is the entry point of the class. It is responsible for coordinate the module creation and 
processing the sequence of words.
*/

#include<iostream>
#include<sstream>
#include<string>
#include<vector>
#include<list>
#include<memory>

#include<Connect.h>
#include<Module.h>
#include<Process.h>
#include<ModuleCreatorFactory.h>

using namespace std;

int main()
{
	string line;
	int inputLength = 0;
	vector<string> outputs;
	vector<shared_ptr<Module>> createdModules;
	//list<shared_ptr<Module>> createdModulesList;

	while (getline(cin, line))
	{
		vector<string> words;
		string token;
		istringstream tokenStream(line);

		//this could be done with iterator
		while (std::getline(tokenStream, token, ' '))
		{
			words.push_back(token);
		}

		if (words[0] == "module")
		{
			createdModules.emplace_back(ModuleCreatorFactory::CreateModule(words[1], words[2]));
		}
		else if (words[0] == "connect")
		{
			//error handling to make sure only two names are there
			vector<string> modulesToConnect(words.begin() + 1, words.end());
			Connect::ConnectModules(createdModules, modulesToConnect);
		}
		else if (words[0] == "process")
		{
			vector<string> inputWords(words.begin() + 1, words.end());
			inputLength = inputWords.size();

			//client doesnt need to know this. Abstract in a single function.
			outputs = Process::ProcessWords(createdModules, inputWords);
			Process::ProcessRemainingDelayWords(createdModules, outputs);

			/*printing only top 16 words in the output*/
			int outputLength = 0;
			for (const auto& outputWord : outputs)
			{
				cout << outputWord << " ";
				++outputLength;
				if (outputLength > 16*inputLength)
					break;
			}
			cout << "\n";

		}
	}
}