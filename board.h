#ifndef BOARD_H
#define BOARD_H
#include <string>
#include <vector>
#include <iostream>
#include <list>
#include <iterator>
#include <exception>
#include <algorithm>

/// @brief Board represents n by n board with the 8 numbers and the one-blank piece
/// Blank piece will be 0
class Board
{
private:
    // n represents the number of columns and rows
    // and thus the board will be square
    int n;
    /// @brief A 2D array representation of the board
    int** pos;
    /// @brief easier to keep track of the blank position rather than constantly trying to search
    /// for it
    int* blankPos;
    static std::list<Board> history();
    bool operator<(const Board& rhs) const;
public:
    Board(int n);
    Board(int n, const std::string& customBoard);
    ~Board();
    Board(const Board& b);
    Board& operator=(const Board& rhs);
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
    // add history
    void addThis();
    bool isInHistory() const;
};
#endif 