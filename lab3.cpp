#include <iostream>
#include "Reader.h"
#include "Parser.h"
#include "Queue.h"
#include "Maze.h"

using namespace std;

void Check(Validator& validator) {
    if (!validator.IsValid()) {
        validator.PrintErrors();
        exit(3);
    }
}


int main()
{
    string filename = "C:\\labs\\lab3\\example1.txt";
    Validator validator;
    Reader reader(validator);
    Parser parser(validator);

    vector<string> content = reader.ReadFile(filename);
    Check(validator);

    parser.ProcessContent(content);
    Check(validator);

    Maze maze(validator, parser.GetCells());
    maze.FindPath(make_pair(1, 1), make_pair(1, 6));
    Check(validator);

    vector<string> result = parser.MakeSolvedMaze(maze.GetPath());
    for (const string& res : result) {
        cout << res << endl;
    }
}


