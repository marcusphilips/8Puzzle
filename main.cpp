#include <iostream>
#include <queue>
#include "board.h"

using namespace std;

int main(int argc, char **argv)
{
    // 
    // "7 1 2 4 8 5 6 3 0 "
    // "1 3 6 5 0 7 4 8 2 "
    Board *b = new Board(3, "1 2 3 5 0 6 4 7 8 ");
    b->addThis();
    // Uniform Cost Search
    queue<Board* > q;
    q.push(b);
    while (true)
    {
        if (q.empty())
        {
            cout << "No solution found" << endl;
            break;
        }
        queue<Board *> next =  queue<Board *>();
        while (!q.empty())
        {
           // cout << q.front()->toString() << endl;
            if (q.front()->isSolved()){
                cout << "Found solution printing history:" << endl;
                q.front()->printHistory();
                cout << "Solution found. No more expansion." << endl;
                goto OUTER_LOOP;
            }
            Board *up = q.front()->moveBlankUp();
            if (up != nullptr)
            {
               // cout << "Up:\n" << up->toString() << endl;
                if (!up->isInHistory())
                {
                    next.push(up);
                    up->addThis();
                }
                else {
                    delete up; // save some mem
                }
            }
            Board *down = q.front()->moveBlankDown();
            if (down != nullptr)
            {
                if (!down->isInHistory())
                {
                    next.push(down);
                    down->addThis();
                }
                else {
                    delete down; // save some mem
                }
            }
            Board *left = q.front()->moveBlankLeft();
            if (left != nullptr)
            {
                if (!left->isInHistory())
                {
                    next.push(left);
                    left->addThis();
                }
                else {
                    delete left; // save some mem
                }
            }
            Board *right = q.front()->moveBlankRight();
            if (right != nullptr)
            {
                if (!right->isInHistory())
                {
                    next.push(right);
                    right->addThis();
                }
                else {
                    delete right; // save some mem
                }
            }
            q.pop();
        }
        q = next;
    }
    OUTER_LOOP:Board::clearHistory();
    return 0;
}