#include <iostream>
#include <queue>
#include "board.h"

using namespace std;


int main(int argc, char** argv)
{
    Board b = Board(3, "3 1 2 0 5 6 4 7 8 ");
    cout << b.toString() << endl;
    return 0;
}