#pragma once
#include <string>
#include <fstream>
#include <vector>
#include "Validator.h"

using namespace std;

class Reader
{
	Validator* validator;
public:
	Reader(Validator& _validator) : validator(&_validator) {}
	vector<string> ReadFile(string filename){
		vector<string> content;
		ifstream file(filename);
		if (!file.is_open()) {
			validator->AddError("Error while openning file\n");
			return content;
		}
		while (!file.eof())
		{
			string buffer;
			getline(file, buffer);
			content.push_back(buffer);
		}
		return content;
	}
};


