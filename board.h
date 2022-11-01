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
    int **pos;
    /// @brief easier to keep track of the blank position rather than constantly trying to search
    /// for it
    int *blankPos;
    Board *parentNode = nullptr;
    static std::list<Board> history;
    static Board solvedBoard;
    int cost = -1; // Sentinel not possible
    int depth = 0;
    void printHistoryHelper() const;

public:

    // Constructors

    Board(int n);
    Board(int n, const std::string &customBoard);

    // Rule of Three

    ~Board();
    Board(const Board &b);
    Board &operator=(const Board &rhs);

    // comparisons useful for sorting

    bool operator==(const Board &rhs) const;
    bool operator<(const Board &rhs) const;
    bool costLessThan(const Board &rhs) const;

    // check Board

    bool isSolved() const;

    // operators

    Board *moveBlankUp();
    Board *moveBlankDown();
    Board *moveBlankRight();
    Board *moveBlankLeft();

    // getters

    int getN() const;
    int getPos(int y, int x) const;
    int getCost() const;
    std::string toString() const;

    // add history

    void addThis();
    bool isInHistory() const;
    void printHistory() const;
    static void clearHistory();

    // Heuristics and A*

    void misplacedCost();
};

#endif