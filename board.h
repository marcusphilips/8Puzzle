#ifndef BOARD_H
#define BOARD_H
#include <string>
#include <iostream>
#include <vector>

// Board represents 3 by 3 board with the 8 numbers and the one-blank piece
// Blank piece will be 0
class Board
{
private:
    // n represents the number of columns and rows
    // and thus the board will be square
    int n;
    int pos[][];
public:
    Board(int n);
    Board(int n, const string& customBoard);
    bool operator==(const Board& rhs) const;
    bool isDone() const;
    bool moveBlankUp();
    bool moveBlankDown();
    bool moveBlankRight();
    bool moveBlankLeft();
    // getters
    int getN() const;
    int getPos(int x, int y) const;
};
#endif 