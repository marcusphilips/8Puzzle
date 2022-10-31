#include <iostream>
#include <queue>
#include "board.h"

using namespace std;

int main(int argc, char **argv)
{
    Board *b = new Board(3, "3 1 2 0 5 6 4 7 8 ");
    // Uniform Cost Search
    queue<Board *> *q;
    q->push(b);
    while (true)
    {
        if (q->empty())
        {
            cout << "No solution found" << endl;
        }
        queue<Board *> *next = new queue<Board *>();
        while (!q->empty())
        {
            if (q->front()->isSolved()){
                cout << "Found solution printing history:" << endl;
                q->front()->printHistory();
                cout << "Solution found. No more expansion." << endl;
                goto OUTER_LOOP;
            }
            Board *up = q->front()->moveBlankUp();
            if (up != nullptr)
            {
                if (!up->isInHistory())
                {
                    next->push(up);
                    up->addThis();
                }
            }
            Board *down = q->front()->moveBlankDown();
            if (down != nullptr)
            {
                if (!down->isInHistory())
                {
                    next->push(down);
                    down->addThis();
                }
            }
            Board *left = q->front()->moveBlankLeft();
            if (left != nullptr)
            {
                if (!left->isInHistory())
                {
                    next->push(left);
                    left->addThis();
                }
            }
            Board *right = q->front()->moveBlankRight();
            if (right != nullptr)
            {
                if (!right->isInHistory())
                {
                    next->push(right);
                    right->addThis();
                }
            }
            q->pop();
        }
    }
    // Testing basic operations

    // Board other = b;
    // cout << b.toString() << endl;
    // b.moveBlankLeft();
    // cout << b.toString() << endl;
    // b.moveBlankRight();
    // cout << b.toString() << endl;
    // b.moveBlankUp();
    // Board k(b);
    // cout << b.toString() << endl;
    // b.moveBlankLeft();
    // cout << b.toString() << endl;
    // b.moveBlankDown();
    // cout << b.toString() << endl;
    // cout << k.toString() << endl;
    // cout << other.toString() << endl;

    OUTER_LOOP:return 0;
}