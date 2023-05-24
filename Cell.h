#pragma once

struct Cell {

    const int MAX_D = 1000;
    int distance = MAX_D;
    const int cost = 1;

    int parent_row = -1;
    int parent_col = -1;

    bool empty;
    int row, col;

    Cell() : Cell(false, 0, 0) {}
    Cell(bool _empty, int _row, int _col) :
        empty(_empty), row(_row), col(_col) {}

    void ChangeParent(Cell& parent) {
        parent_row = parent.row;
        parent_col = parent.col;
    }

    void operator=(Cell& other) {
        row = other.row;
        col = other.col;
        parent_row = other.parent_row;
        parent_col = other.parent_col;
        distance = other.distance;
    }

    bool operator==(Cell& other) {
        return row == other.row && col == other.col;
    }
};