#pragma once
#include <vector>
#include <stack>
#include "Queue.h"
#include "Cell.h"

using namespace std;

class Maze
{
    Validator *validator;

    vector<vector<Cell>> cells;
		
	int rows;
	int cols;

	stack<Cell> path;

    bool GetDijkstra(Cell from, Cell to) {

        Queue<Cell> checked_cells;
        cells[from.row][from.col].distance = 0;
        checked_cells.Enqueu(cells[from.row][from.col]);

        while (!checked_cells.IsEmpty()) {

            Cell top = checked_cells.Dequeu();

            if (top == to) {
                Cell to_add = top;
                while (to_add.distance!=0) {
                    path.push(to_add);
                    to_add = cells[to_add.parent_row][to_add.parent_col];
                }
                path.push(to_add);
                return true;
            }

            vector<Cell> neighbors = GetNeigbours(top);

            for (const Cell& neighbor : neighbors) {
                if (cells[neighbor.row][neighbor.col].distance > top.distance + neighbor.cost) {
                    cells[neighbor.row][neighbor.col].distance = top.distance + neighbor.cost;
                    cells[neighbor.row][neighbor.col].ChangeParent(top);
                    checked_cells.Enqueu(cells[neighbor.row][neighbor.col]);
                }
            }
        }
        return false;
    }

    vector<Cell> GetNeigbours(Cell from) {
        vector<Cell> result;
        Cell to_add(from);

        //left
        to_add.col = to_add.col - 1;
        if (to_add.col > 0 && cells[to_add.row][to_add.col].empty) {
            result.push_back(cells[to_add.row][to_add.col]);
        }
        to_add = from;
        //right
        to_add.col = to_add.col + 1;
        if (to_add.col < cols && cells[to_add.row][to_add.col].empty) {
            result.push_back(cells[to_add.row][to_add.col]);
        }
        to_add = from;
        //up
        to_add.row = to_add.row - 1;
        if (to_add.row > 0 && cells[to_add.row][to_add.col].empty) {
            result.push_back(cells[to_add.row][to_add.col]);
        }
        to_add = from;
        //down
        to_add.row = to_add.row + 1;
        if (to_add.row < rows && cells[to_add.row][to_add.col].empty) {
            result.push_back(cells[to_add.row][to_add.col]);
        }
        return result;
    }
 
public:
    Maze(Validator& _validator, vector<vector<Cell>> _cells) {
        validator = &_validator;
        cells = _cells;
        rows = (int)_cells.size();
        cols = (int)_cells[0].size();
    }

    stack<Cell> GetPath() { return path; }
    
    void FindPath(pair<int, int> _from, pair<int, int> _to) {

        validator->ValidateRequest(cells, _from, _to);
        if (!validator->IsValid()) return;

        Cell from = cells[_from.first][_from.second];
        Cell to = cells[_to.first][_to.second];
        
        if (!GetDijkstra(from, to)) {
            validator->AddError("No path between spots\n");
        }

        
    }
};

