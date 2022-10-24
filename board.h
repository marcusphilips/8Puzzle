#ifndef BOARD_H
#define BOARD_H
#include <string>
#include <iostream>
#include <list>
#include <iterator>

// Board represents n by n board with the 8 numbers and the one-blank piece
// Blank piece will be 0
class Board
{
private:
    // n represents the number of columns and rows
    // and thus the board will be square
    int n;
    int** pos;
    static std::list<Board> history();
public:
    Board(int n);
    Board(int n, const std::string& customBoard);
    bool operator==(const Board& rhs) const;
    bool isSolved() const;
    bool moveBlankUp();
    bool moveBlankDown();
    bool moveBlankRight();
    bool moveBlankLeft();
    // getters
    int getN() const;
    int getPos(int y, int x) const;
    std::string toString() const;
};
#endif 