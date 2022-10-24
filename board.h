#include <string>
#include <iostream>

// Board represents 3 by 3 board with the 8 numbers and the one-blank piece
// Blank piece will be 0
class Board
{
private:
    int pos[3][3];
public:
    Board();
    Board(const string& customBoard);
    bool operator==(const Board& rhs) const;
    bool isDone() const;
    bool moveBlankUp();
    bool moveBlankDown();
    bool 
};