#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <format>
#include <stack>
#include "Validator.h"
#include "Cell.h"

using namespace std;


class Parser
{
	const char BLOCK_CHAR = 'X';
	const char EMPTY_CHAR = ' ';
	const char SEPARATOR_CHAR = ' ';

	const string PATH_STRING = "123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

	vector<string> content;
	vector<vector<Cell>> cells;
	
	Validator *validator;

	bool ProcessChar(char to_process, int i, int j) {
		if (to_process == BLOCK_CHAR)
			return false;

		if (to_process == EMPTY_CHAR)
			return true;

		string error = format("Not recognised char/string in row:{}, col: {} ({})\n", i+1, j+1, to_process);
		validator->AddError(error);
		return false;
	}

	vector<char> SplitLine(string to_split, int i) {
		vector<char> res;
		stringstream line(to_split);
		int j = 0;
		while (true) {
			char symbol = line.get();
			if (line.eof()) break;
			res.push_back(symbol);
			j++;
			char separator = line.get();
			if (line.eof()) break;
			if (separator != SEPARATOR_CHAR) {
				string error = format("Not recognised separator in row:{}, col: {} ({})\n", i+1, j+1, separator);
				validator->AddError(error);
			}
		}
		return res;
	}

public:
	Parser(Validator& _validator) : validator(&_validator) {}
	vector<vector<Cell>> GetCells() { return cells; }


	void ProcessContent(vector<string> _content) {
		
		content = _content;

		validator->ValidateSize(content);
		if (!validator->IsValid()) return;

		for (int i = 0; i < content.size(); i++) {

			vector<char> row_to_process(SplitLine(content[i], i));
			vector<Cell> cells_to_append;

			for (int j = 0; j < row_to_process.size(); j++) {
				bool empty = ProcessChar(row_to_process[j], i, j);
				cells_to_append.push_back(Cell(empty, i, j));
			}

			cells.push_back(cells_to_append);
		}
	}

	vector<string> MakeSolvedMaze(stack<Cell> path) {
	
		int counter=0;
		while (!path.empty()) {
			content[path.top().row][2 * path.top().col] = PATH_STRING[counter++];
			path.pop();
			//if(counter )
		}
		return content;
	}
};




