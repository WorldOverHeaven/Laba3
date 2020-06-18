#include "Tree.h"
#include <iostream>
using namespace std;

Tree::Tree(const Game& a) {
    field = a;
    num = 9 - field.getStep();
    score = 0;
    if (field.getStatus() == draw) {
        this->keys();
    }
    else if (field.getStatus() == win0){
        score = -factorial(num);
    }
    else if (field.getStatus() == winX) {
        score = factorial(num);
    }
}

Game Tree::getField() {
    return field;
}

bool Tree::put(int y) {
    return field.put(y);
}

void Tree::print() {
    field.print();
}

void Tree::printKey() {
    for (int i = 0; i < num; ++i) {
        cout << sumScore(key[i]) << endl;
        key[i]->print();
    }
}

void Tree::keys() {
    for (int k = 0, i = 0; i < 9; ++i) {
        Game b = field;
        if (b.put(i)) {
            Tree tr(b);
            key[k] = new Tree(tr);
            ++k;
        }
    }
}

int Tree::getScore() {
    return score;
}

status Tree::getStatus() {
    return field.getStatus();
}

int Tree::getNum() {
    return num;
}

Tree* Tree::getKey(int i) {
    return key[i];
}

void Tree::del(Tree* k) {
    if (k->getStatus() == win0 || k->getStatus() == winX || k->getStatus() == endGame) {
        delete k;
    }
    else {
        for (int i = 0; i < k->getNum(); ++i) {
            del(k->getKey(i));
        }
    }
}

int Tree::sumScore(Tree* k) {
    if (k->getStatus() == win0 || k->getStatus() == winX || k->getStatus() == endGame) {
        return k->getScore();
    }
    else {
        int sum = 0;
        for (int i = 0; i < k->getNum(); ++i) {
            sum += sumScore(k->getKey(i));
        }
        return sum;
    }
}

void Tree::printSumScore() {
    for (int i = 0; i < num; ++i) {
        cout << sumScore(key[i]) << endl;
    }
}

Tree Tree::printWin() {
    if (field.getStatus() != draw) {
        return *this;
    }
    if (field.getStep() % 2 == 0) {
        int max = -400000;
        int k;
        int l = 0;
        for (int i = 0; i < num; ++i) {
            k = sumScore(key[i]);
            if (k > max) {
                max = k;
                l = i;
            }
        }
        key[l]->print();
        return *key[l];
    }
    else {
        int min = 400000;
        int k;
        int l = 0;
        for (int i = 0; i < num; ++i) {
            k = sumScore(key[i]);
            if (k < min) {
                min = k;
                l = i;
            }
        }
        key[l]->print();
        return *key[l];
    }
}
