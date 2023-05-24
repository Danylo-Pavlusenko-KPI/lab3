#pragma once
#include <vector>
#include <string>
#include <format>
#include "Cell.h"

using namespace std;


class Validator {
	vector<string> errors;

public:
	vector<string> GetErrors() { return errors; }

	void PrintErrors() {
		for (int i = 0; i < errors.size(); i++) {
			cout << errors[i];
		}
	}
	
	void AddError(string error) { errors.push_back(error); }
	
	bool IsValid() { return errors.size() == 0; }

	void ValidateSize(vector<string>& content) {
		if (content.empty()) {
			string error = format("File can not be empty\n");
			errors.push_back(error);
		}

		int cols = (int)content[0].length();

		for (int i = 0; i < (int)content.size(); i++) {
			if (content[i].length() != cols) {
				string error = format("The lenght of {} row must be equal to 1st row\n", i + 1);
				errors.push_back(error);
			}
		}
	}

	void ValidateRequest(vector<vector<Cell>>& cells, pair<int, int> _from, pair<int, int> _to) {
		if (_from.first> cells.size() || _from.first < 0) {
			string error = format("Index of start point's row is out of range\n");
			errors.push_back(error);
		}
		if (_to.first > cells.size() || _to.first < 0) {
			string error = format("Index of final point's row is out of range\n");
			errors.push_back(error);
		}
		if (_from.second > cells[0].size() || _from.second < 0) {
			string error = format("Index of start point's col is out of range\n");
			errors.push_back(error);
		}
		if (_to.second > cells[0].size() || _to.second < 0) {
			string error = format("Index of final point's col is out of range\n");
			errors.push_back(error);
		}
	}
	
};