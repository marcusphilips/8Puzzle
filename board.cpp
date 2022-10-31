#include "board.h"

std::list<Board> Board::history = std::list<Board> ();

/// @brief  Board represents n by n board with the n*n - 1 numbers and the one-blank piece
/// Blank piece will be 0
/// @param n
Board::Board(int n)
{
    this->n = n; // set the dimension of the board
    // default method board will just create the solved board
    int num = 1;
    pos = new int *[n]; // n by n array as specified by the user
    for (int i = 0; i < n; i++)
        pos[i] = new int[n];
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            if (num != 9)
                pos[row][col] = num;
            else
            {
                pos[row][col] = 0;
                blankPos = new int[2];
                blankPos[0] = row;
                blankPos[1] = col;
            }
            num++;
        }
    }
}

/// @brief the custom string input for the board the format should be precisely (ignore quotes)
/// "num_1 num_2 ... num_(n^2 - 1) 0"
/// ex (ignore quotes) for 3 by 3 board
/// "1 3 4 5 6 8 2 7 0 "
/// Does not check for duplicates other than making sure the numbers are between 1 and n^2 - 1, inclusive.
/// Use 0 to indicate the blank spot
/// @param n how many rows or columns
/// @param customBoard a custom string representation of the board (please append a space at the end)
Board::Board(int n, const std::string &customBoard)
{
    this->n = n;
    int s = 0;
    pos = new int *[n]; // n by n array as specified by the user
    for (int i = 0; i < n; i++)
        pos[i] = new int[n];
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            std::string remaining = customBoard.substr(s);
            unsigned end = remaining.find(" ");
            if (end == std::string::npos)
            {
                std::cout << "Invalid string input. Read documentation. Quitting." << std::endl;
                exit(1);
            }
            int num = 0;
            try
            {
                num = std::stoi(remaining.substr(0, end));
            }
            catch (std::exception e)
            {
                std::cout << e.what() << std::endl;
                std::cout << "Tried to parse <" << remaining.substr(0, end) << "> and failed. Quitting."
                          << std::endl;
                exit(1);
            }
            s += end + 1;

            if (num >= 1 && num <= n * n - 1)
            {
                pos[row][col] = num;
            }
            else if (num == 0)
            {
                pos[row][col] = 0;
                blankPos = new int[2];
                blankPos[0] = row;
                blankPos[1] = col;
            }
            else
            {
                std::cout << "Error: invalid numeral used <" << num << ">\n"
                          << "Only numerals 1-(n*n-1) or 0 are valid for the the 8 Puzzle." << std::endl;
                exit(1);
            }
        }
    }
}

/// @brief Checks whether two boards are in equivalent states. Does not check size. That should be left to the user.
/// @param rhs
/// @return bool
bool Board::operator==(const Board &rhs) const
{
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            if (pos[row][col] != rhs.getPos(row, col))
            {
                return false;
            }
        }
    }
    return true;
}

/// @brief Gives a string representation of the board
/// @return a string representation of the board
std::string Board::toString() const
{
    std::string acc;
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            acc.append(std::to_string(pos[row][col]));
            acc.push_back(' ');
        }
        acc.push_back('\n');
    }
    return acc;
}

/// @brief Returns the integer of the position given. 0 if it is the blank.
/// Does not check out of bounds.
/// @param y the row
/// @param x the col
/// @return the number at the position
int Board::getPos(int y, int x) const
{
    return pos[y][x];
}

/// @brief Is this current board solved?
/// @return a bool indicating whether the Board has been solved
bool Board::isSolved() const
{
    int count = 1;
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            if (row == n - 1 && col == n - 1)
            {
                if (pos[row][col] != 0)
                {
                    return false;
                }
            }
            else
            {
                if (pos[row][col] != count)
                {
                    return false;
                }
                else
                {
                    count++;
                }
            }
        }
    }
    return true;
}

/// @brief what is the length or the width (the same since it's a square) of the board
/// @return an integer
int Board::getN() const
{
    return n;
}

/// @brief attempts to move Blank up
/// @return board pointer did it actually move the blank up null pointer if not
Board *Board::moveBlankUp()
{

    if (blankPos[0] == 0) // if row is 0
        return nullptr;
    Board *b = new Board(*this);
    b->pos[b->blankPos[0]][b->blankPos[1]] = b->pos[b->blankPos[0] - 1][b->blankPos[1]];
    b->pos[b->blankPos[0] - 1][b->blankPos[1]] = 0;
    b->blankPos[0] = b->blankPos[0] - 1;
    b->parentNode = this;
    return b;
}

/// @brief attempts to move blank down
/// @return Board pointer it actually move the blank down
Board *Board::moveBlankDown()
{
    if (blankPos[0] == n - 1) // if row is n -1
        return nullptr;
    Board *b = new Board(*this);
    b->pos[b->blankPos[0]][b->blankPos[1]] = b->pos[b->blankPos[0] + 1][b->blankPos[1]];
    b->pos[b->blankPos[0] + 1][b->blankPos[1]] = 0;
    b->blankPos[0] = b->blankPos[0] + 1;
     b->parentNode = this;
    return b;
}

/// @brief attempts to move blank down
/// @return Board pointer it actually move the blank down
Board *Board::moveBlankRight()
{
    if (blankPos[1] == n - 1) // if col is n -1
        return nullptr;

    Board *b = new Board(*this);
    b->pos[b->blankPos[0]][b->blankPos[1]] = b->pos[b->blankPos[0]][b->blankPos[1] + 1];
    b->pos[b->blankPos[0]][b->blankPos[1] + 1] = 0;
    b->blankPos[1] = b->blankPos[1] + 1;
     b->parentNode = this;
    return b;
}

/// @brief attempts to move blank left
/// @return Board pointer did it actually move the blank left
Board *Board::moveBlankLeft()
{
    if (blankPos[1] == 0) // if col is n -1
        return nullptr;

    Board *b = new Board(*this);
    b->pos[b->blankPos[0]][b->blankPos[1]] = b->pos[b->blankPos[0]][b->blankPos[1] - 1];
    b->pos[b->blankPos[0]][b->blankPos[1] - 1] = 0;
    b->blankPos[1] = b->blankPos[1] - 1;
    b->parentNode = this;
    return b;
}

// this is my punishment for using dynamically allocated arrays

/// @brief deallocator
Board::~Board()
{
    for (int row = 0; row < n; row++)
    {
        delete[] pos[row];
    }
    delete[] pos;
    delete[] blankPos;
}

/// @brief Copy constructor
/// @param b Board
Board::Board(const Board &b)
{
    this->n = b.getN();
    this->parentNode = b.parentNode;
    pos = new int *[n]; // n by n array as specified by the user
    blankPos = new int[2];
    for (int i = 0; i < n; i++)
        pos[i] = new int[n];
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            pos[row][col] = b.getPos(row, col);
            if (pos[row][col] == 0)
            {
                blankPos[0] = row;
                blankPos[1] = col;
            }
        }
    }
}

/// @brief assignment operator
/// @param rhs another Board
/// @return the Board equal to rhs
Board &Board::operator=(const Board &rhs)
{
    if (this == &rhs)
        return *this;

    for (int row = 0; row < n; row++)
    {
        delete[] pos[row];
    }
    delete[] pos;
    this->n = rhs.getN();
    pos = new int *[n]; // n by n array as specified by the user
    for (int i = 0; i < n; i++)
        pos[i] = new int[n];
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            pos[row][col] = rhs.getPos(row, col);
            if (pos[row][col] == 0)
            {
                blankPos[0] = row;
                blankPos[1] = col;
            }
        }
    }
    return *this;
}

/// @brief Compares wheter this is less than rhs. Assumes the comparisons are on boards of
/// equivalent size, n.
/// @param rhs another Board object to compare to
/// @return a bool on whether this Board object is less than rhs
bool Board::operator<(const Board &rhs) const
{
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            if (pos[row][col] < rhs.getPos(row, col))
                return true;
            else if (pos[row][col] > rhs.getPos(row, col))
                return false;
            // else continue comparing
        }
    }
    // basically the boards are equal and thus not less than
    return false;
}

/// @brief Add this Board object to the history of all boards. But in a sorted way to save time
void Board::addThis()
{
    std::list<Board>::iterator it;
    std::cout << history.size() << std::endl;
    it = std::lower_bound(history.begin(), history.end(), *this);
    history.insert(it, *this);
}

/// @brief Has the Board already been recorded
/// @return bool is the current Board in the history of the object
bool Board::isInHistory() const
{
    std::list<Board>::iterator it;
    it = std::lower_bound(history.begin(), history.end(), *this);
    if (it != history.end())
        return true;
    else
        return false;
}

/// @brief prints the history of the choices
void Board::printHistory() const {
    std::cout << toString() << std::endl;
    if (parentNode != nullptr)
       parentNode->printHistory();
}
