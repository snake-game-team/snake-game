#pragma once

class Gate {
private:
    int row;
    int col;
public:
    Gate(int y, int x) : row(y), col(x) {}

    int getY() const { 
        return row; 
    }

    int getX() const { 
        return col; 
    }

    void setPosition(int y, int x) {
        row = y;
        col = x;
    }

    bool isAt(int y, int x) const {
        return row == y && col == x;
    }
};
