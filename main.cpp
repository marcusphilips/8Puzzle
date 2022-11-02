#include <iostream>
#include <queue>
#include "board.h"

using namespace std;

void uniformCost(int n, string &s);
void misplacedCost(int n, string &s);
void manhattanCost(int n, string &s);

int main(int argc, char **argv)
{
    // "1 2 3 5 0 6 4 7 8 "
    // "7 1 2 4 8 5 6 3 0 "
    // "1 3 6 5 0 7 4 8 2 "
    // "0 7 2 4 6 1 3 5 8 "
    // "1 6 7 5 0 3 4 8 2 "
    string txt = "1 6 7 5 0 3 4 8 2 ";
    manhattanCost(3, txt);
    misplacedCost(3, txt);
   // uniformCost(3, txt);
    return 0;
}

void uniformCost(int n, string &s)
{
    Board *b = new Board(n, s);
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
                cout << "Uniform Cost\nFound solution Expanded: " << boards
                     << " Added to Queue: " << addedToQueue
                     << "\nPrinting history:" << endl;
                q.front()->printHistory();
                cout << "Solution found. No more expansion." << endl;
                return; // break out of the outer loop
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
    Board::clearHistory();
}

void misplacedCost(int n, string &s){
    Board *c = new Board(n, s);
    c->misplacedCost();
    list<Board *> l;
    l.push_front(c);
    int boards = 0;
    int addedToQueue = 0;
    while (true)
    {
        if (l.empty())
        {
            cout << "No solution found" << endl;
            break;
        }
        // read the front
        if (l.front()->isSolved())
        {
            cout << "Misplaced Cost\nFound solution Expanded: " << boards
                 << " Added to Queue: " << addedToQueue
                 << "\nPrinting history:" << endl;
            l.front()->printHistory();
            cout << "Solution found. No more expansion." << endl;
            break;
        }
        // expand all directions of the front node
        list<Board *> l2;
        Board *up = l.front()->moveBlankUp();
        if (up != nullptr)
        {
            boards++;
            // cout << "Up:\n" << up->toString() << endl;
            if (!up->isInHistory())
            {
                up->misplacedCost();
                addedToQueue++;
                l2.push_back(up);
                up->addThis();
            }
            else
            {
                delete up; // save some mem
            }
        }
        Board *down = l.front()->moveBlankDown();
        if (down != nullptr)
        {
            boards++;
            if (!down->isInHistory())
            {
                down->misplacedCost();
                addedToQueue++;
                l2.push_back(down);
                down->addThis();
            }
            else
            {
                delete down; // save some mem
            }
        }
        Board *left = l.front()->moveBlankLeft();
        if (left != nullptr)
        {
            boards++;
            if (!left->isInHistory())
            {
                left->misplacedCost();
                addedToQueue++;
                l2.push_back(left);
                left->addThis();
            }
            else
            {
                delete left; // save some mem
            }
        }
        Board *right = l.front()->moveBlankRight();
        if (right != nullptr)
        {
            boards++;
            if (!right->isInHistory())
            {
                right->misplacedCost();
                addedToQueue++;
                l2.push_back(right);
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
        // cout << "Printing list:\n" ;
        // for (list<Board* >::iterator it = l.begin(); it != l.end(); it++)
        // {
        //          cout << "Cost: " << (*it)->getCost() << '\n'
        //          << (*it)->toString() << endl;
        // }
        // cin.get();
        // cout << "\nBoards: " << boards << "\t\tBoards Added to Queue: " << addedToQueue << '\n'
        //     << l.front()->toString() << endl;
        // cout << "Printing costs:\n";
        // for (list<Board *>::iterator it = l.begin(); it != l.end(); it++)
        // {
        //     cout << (*it)->getCost() << ' ';
        // }

        // cout << "\nBoards: " << boards << "\t\tBoards Added to Queue: " << addedToQueue << '\n'
        //     << l.front()->toString() << endl;
        // cin.get();
    }
    Board::clearHistory();
}

void manhattanCost(int n, string &s){
    Board* c = new Board(n, s);
    c->manhattanCost();
    list<Board *> l;
    l.push_front(c);
    int boards = 0;
    int addedToQueue = 0;
    while (true)
    {
        if (l.empty())
        {
            cout << "No solution found" << endl;
            break;
        }
        // read the front
        if (l.front()->isSolved())
        {
            cout << "Manhattan Cost\nFound solution Expanded: " << boards
                 << " Added to Queue: " << addedToQueue
                 << " printing history:" << endl;
            l.front()->printHistory();
            cout << "Solution found. No more expansion." << endl;
            break;
        }
        // expand all directions of the front node
        list<Board *> l2;
        Board *up = l.front()->moveBlankUp();
        if (up != nullptr)
        {
            boards++;
            // cout << "Up:\n" << up->toString() << endl;
            if (!up->isInHistory())
            {
                up->manhattanCost();
                addedToQueue++;
                l2.push_back(up);
                up->addThis();
            }
            else
            {
                delete up; // save some mem
            }
        }
        Board *down = l.front()->moveBlankDown();
        if (down != nullptr)
        {
            boards++;
            if (!down->isInHistory())
            {
                down->manhattanCost();
                addedToQueue++;
                l2.push_back(down);
                down->addThis();
            }
            else
            {
                delete down; // save some mem
            }
        }
        Board *left = l.front()->moveBlankLeft();
        if (left != nullptr)
        {
            boards++;
            if (!left->isInHistory())
            {
                left->manhattanCost();
                addedToQueue++;
                l2.push_back(left);
                left->addThis();
            }
            else
            {
                delete left; // save some mem
            }
        }
        Board *right = l.front()->moveBlankRight();
        if (right != nullptr)
        {
            boards++;
            if (!right->isInHistory())
            {
                right->manhattanCost();
                addedToQueue++;
                l2.push_back(right);
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
        // cout << "Printing costs:\n";
        // for (list<Board *>::iterator it = l.begin(); it != l.end(); it++)
        // {
        //     cout << (*it)->getCost() << ' ';
        // }

        // cout << "\nBoards: " << boards << "\t\tBoards Added to Queue: " << addedToQueue << '\n'
        //      << l.front()->toString() << endl;
        // if (boards % 1000 == 0)
        //     cin.get();
    }
    Board::clearHistory();
}
