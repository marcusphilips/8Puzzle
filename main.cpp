#include <iostream>
#include <queue>
#include "board.h"

using namespace std;

int main(int argc, char **argv)
{
    // "1 2 3 5 0 6 4 7 8 "
    // "7 1 2 4 8 5 6 3 0 "
    // "1 3 6 5 0 7 4 8 2 "
    Board *b = new Board(3, "1 2 3 5 0 6 4 7 8 ");
    b->addThis();
    // Uniform Cost Search
    queue<Board *> q;
    int boards = 0;
    int addedToQueue = 0;
    q.push(b);
    while (true)
    {
        if (q.empty())
        {
            cout << "No solution found" << endl;
            break;
        }
        queue<Board *> next = queue<Board *>();
        while (!q.empty())
        {
            // cout << q.front()->toString() << endl;
            if (q.front()->isSolved())
            {
                cout << "Found solution Expanded: " << boards
                     << " Added to Queue: " << addedToQueue
                     << " printing history:" << endl;
                q.front()->printHistory();
                cout << "Solution found. No more expansion." << endl;
                goto OUTER_LOOP; // break out of the outer loop
            }
            Board *up = q.front()->moveBlankUp();
            if (up != nullptr)
            {
                boards++;
                // cout << "Up:\n" << up->toString() << endl;
                if (!up->isInHistory())
                {
                    addedToQueue++;
                    next.push(up);
                    up->addThis();
                }
                else
                {
                    delete up; // save some mem
                }
            }
            Board *down = q.front()->moveBlankDown();
            if (down != nullptr)
            {
                boards++;
                if (!down->isInHistory())
                {
                    addedToQueue++;
                    next.push(down);
                    down->addThis();
                }
                else
                {
                    delete down; // save some mem
                }
            }
            Board *left = q.front()->moveBlankLeft();
            if (left != nullptr)
            {
                boards++;
                if (!left->isInHistory())
                {
                    addedToQueue++;
                    next.push(left);
                    left->addThis();
                }
                else
                {
                    delete left; // save some mem
                }
            }
            Board *right = q.front()->moveBlankRight();
            if (right != nullptr)
            {
                boards++;
                if (!right->isInHistory())
                {
                    addedToQueue++;
                    next.push(right);
                    right->addThis();
                }
                else
                {
                    delete right; // save some mem
                }
            }
            q.pop();
        }
        q = next;
    }
OUTER_LOOP:
    Board::clearHistory();
    Board c =  Board(3, "1 2 3 5 0 6 4 7 8 ");
    c.misplacedCost();
    list<Board > l;
    l.push_front(c);
    boards = 0;
    addedToQueue = 0;
    while (true)
    {
        if (l.empty())
        {
            cout << "No solution found" << endl;
            break;
        }
        // read the front
        if (l.front().isSolved())
        {
            cout << "Found solution Expanded: " << boards
                 << " Added to Queue: " << addedToQueue
                 << " printing history:" << endl;
            l.front().printHistory();
            cout << "Solution found. No more expansion." << endl;
            break;
        }
        // expand all directions of the front node
        list<Board > l2;
        Board *up = l.front().moveBlankUp();
        if (up != nullptr)
        {
            boards++;
            // cout << "Up:\n" << up->toString() << endl;
            if (!up->isInHistory())
            {
                up->misplacedCost();
                addedToQueue++;
                l2.push_back(*up);
                up->addThis();
            }
            else
            {
                delete up; // save some mem
            }
        }
        Board *down = l.front().moveBlankDown();
        if (down != nullptr)
        {
            boards++;
            if (!down->isInHistory())
            {
                down->misplacedCost();
                addedToQueue++;
                l2.push_back(*down);
                down->addThis();
            }
            else
            {
                delete down; // save some mem
            }
        }
        Board *left = l.front().moveBlankLeft();
        if (left != nullptr)
        {
            boards++;
            if (!left->isInHistory())
            {
                left->misplacedCost();
                addedToQueue++;
                l2.push_back(*left);
                left->addThis();
            }
            else
            {
                delete left; // save some mem
            }
        }
        Board *right = l.front().moveBlankRight();
        if (right != nullptr)
        {
            boards++;
            if (!right->isInHistory())
            {
                right->misplacedCost();
                addedToQueue++;
                l2.push_back(*right);
                right->addThis();
            }
            else
            {
                delete right; // save some mem
            }
        }
        l.pop_front(); // done with this node
        if (!l2.empty())
        {
            // sort by cost
            l2.sort(Board::costLessThan);
            // merge assumes both lists are sorted
            l.merge(l2, Board::costLessThan);
        }
        for (list<Board >::iterator it = l.begin(); it != l.end(); it++)
        {
            cout << "Cost: " << it->getCost() << '\n'
                 << it->toString() << endl;
        }
        cin.get();
    }
    return 0;
}