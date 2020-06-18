#ifndef XO_TREE_H
#define XO_TREE_H

#include "Game.h"

class Tree {
private:
    Game field;
    int num;
    Tree *key[9]{};
    int score = 0;
public:
    Tree(const Game& a);
    Game getField();
    bool put(int y);
    void print();
    void printKey();
    void keys();
    int getScore();
    status getStatus();
    int getNum();
    Tree* getKey(int i);
    static void del(Tree* k);
    static int sumScore(Tree* k);
    void printSumScore();
    Tree printWin();
};

#endif
