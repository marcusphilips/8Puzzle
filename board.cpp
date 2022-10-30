#include "board.h"

/// @brief  Board represents n by n board with the 8 numbers and the one-blank piece
/// Blank piece will be 0
/// @param n 
Board::Board(int n)
{
    this->n = n; // set the dimension of the board
    // default method board will just create
    int num = 1;
    pos = new int*[n]; // n by n array as specified by the user
    for (int i = 0; i < n; i++)
        pos[i] = new int[n];
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            if (num != 9)
                pos[row][col] = num;
            else
                pos[row][col] = 0;
            num++;
        }
    }
}
/// @brief the custom string input for the board the format should be precisely (ignore quotes)
/// "num_1 num_2 ... num_(n^2 - 1) "
/// ex (ignore quotes) for 3 by 3 board
/// "1 3 4 5 6 8 2 7 "
/// Does not check for duplicates other than making sure the numbers are between 1 and n^2 - 1, inclusive.
/// @param n how many rows or columns
/// @param customBoard a custom string representation of the board (please append a space at the end)
Board::Board(int n, const std::string &customBoard)
{
    this->n = n;
    int s = 0;
    pos = new int*[n]; // n by n array as specified by the user
    for (int i = 0; i < n; i++)
        pos[i] = new int[n];
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            std::string remaining = customBoard.substr(s);
            unsigned end = remaining.find(" ");
            if (end == std::string::npos){
                std::cout << "Invalid string input. Read documentation. Quitting." << std::endl;
                exit(1);
            }
            int num = 0;
            try{
                num = std::stoi(remaining.substr(0, end));
            }
            catch(std::exception e){
                std::cout << e.what() << std::endl;
                std::cout << "Tried to parse <" << remaining.substr(0, end) << "> and failed. Quitting." 
                    << std::endl;
                exit(1);
            }
            s += end + 1;
            
            if (num >= 1 || num <= n*n - 1){
                pos[row][col] = num;}
            else
            {
                std::cout << "Error: invalid numeral used <" << num << ">\n"
                     << "Only numerals 1-8 or 0 or \' \' are valid for the the 8 Puzzle." << endl;
                exit(1);
            }
        }
    }
}
/// @brief Checks whether two boards are in equivalent states. Does not check size. That should be left to the user.
/// @param rhs 
/// @return bool
bool Board::operator==(const Board& rhs) const {
    for (int row = 0; row < n; row++){
        for (int col; col < n; col++){
            if (pos[row][col] != rhs.getPos(row, col)){
                return false;
            }
        }
    }
    return true;
}

std::string Board::toString() const {
    std::string acc = "";
    for (int row = 0; row < n; row++){
        for (int col = 0; col < n; col++){
            acc += pos[row][col] + " ";
        }
        acc += "\n";
    }
}

/// @brief Returns the integer of the position given. 0 if it is the blank. 
/// Does not check out of bounds.
/// @param y the row
/// @param x the col
/// @return the number at the position
int Board::getPos(int y, int x) const {
    return pos[y][x];
}

bool Board::isSolved() const {
    int count = 1;
    for (int row = 0; row < n; row++){
        for (int col = 0; col < n; col++){
            if (row == n - 1 && col == n - 1){
                if (pos[row][col] != 0){
                    return false;}}
            else {
                if (pos[row][col] != count)
                {
                    return false;
                }
                else{
                    count++;
                }
            }
        }
    }
    return true;
}