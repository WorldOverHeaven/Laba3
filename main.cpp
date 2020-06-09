#include <iostream>
#include "head.h"
using namespace std;

void go() {
    cout << "Select mode:\n1 - prediction\n2 - play" << endl;
    int t;
    cin >> t;
    if (t == 1) {
        cout << "Enter field" << endl;
        Game a;
        a.in2();
        Tree b(a);
        b.print();
        b.printWin();
        Tree::del(&b);
    }
    if (t == 2) {
        cout << "Will you go first or second?" << endl;
        int k;
        cin >> k;
        Game a;
        Tree b(a);
        int y;
        if (k == 1) {
            b.print();
            while (b.getStatus() == draw) {
                cin >> y;
                while (!a.put(y)) {
                    cin >> y;
                }
                b = a;
                b.print();
                b = b.printWin();
                a = b.getField();
            }
        }
        if (k == 2) {
            while (b.getStatus() == draw) {
                b = b.printWin();
                a = b.getField();
                if (b.getStatus() != draw) {
                    break;
                }
                cin >> y;
                while (!a.put(y)) {
                    cin >> y;
                }
                b = a;
                b.print();
            }
        }
        Tree::del(&b);
    }
    cout << "Again?\nEnter 1 if yes"<< endl;
}

int factorial(int a) {
    int k = 1;
    for (int i = 2; i <= a; ++i) {
        k *= i;
    }
    return k;
}

Game::Game() {
        for (int & i : a) {
            i = -1;
        }
        step = 0;
        st = draw;
    }

Game::Game(const Game & obj) {
    for (int i = 0; i < 9; ++i) {
        a[i] = obj.a[i];
    }
    step = obj.step;
    st = obj.st;
}

int Game::getStep() {
    return step;
}

status Game::getStatus() {
    return st;
}

void Game::print() {
    for (int i = 0; i < 9; i += 3) {
        if (a[i] == -1) {
            cout << ". ";
        }
        if (a[i] == 0) {
            cout << "0 ";
        }
        if (a[i] == 1) {
            cout << "X ";
        }
        if (a[i + 1] == -1) {
            cout << ". ";
        }
        if (a[i + 1] == 0) {
            cout << "0 ";
        }
        if (a[i + 1] == 1) {
            cout << "X ";
        }
        if (a[i + 2] == -1) {
            cout << ". ";
        }
        if (a[i + 2] == 0) {
            cout << "0 ";
        }
        if (a[i + 2] == 1) {
            cout << "X ";
        }
        cout << "" << endl;
    }
    cout << "" << endl;
}

status Game::prediction() {
    if (step == 9) {
        return endGame;
    }
    if (step <= 4) {
        return draw;
    }
    for (int i = 0; i < 9; i += 3) {
        if (a[i] == 0 && a[i + 1] == 0 && a[i + 2] == 0) {
            return win0;
        }
        if (a[i] == 1 && a[i + 1] == 1 && a[i + 2] == 1) {
            return winX;
        }
    }
    for (int i = 0; i < 3; ++i) {
        if (a[i] == 0 && a[i + 3] == 0 && a[i + 6] == 0) {
            return win0;
        }
        if (a[i] == 1 && a[i + 3] == 1 && a[i + 6] == 1) {
            return winX;
        }
    }
    if (a[0] == 0 && a[4] == 0 && a[8] == 0) {
        return win0;
    }
    if (a[6] == 0 && a[4] == 0 && a[2] == 0) {
        return win0;
    }
    if (a[0] == 1 && a[4] == 1 && a[8] == 1) {
        return winX;
    }
    if (a[6] == 1 && a[4] == 1 && a[2] == 1) {
        return winX;
    }
    return draw;
}

bool Game::put(int y) {
    if (a[y] == -1) {
        a[y] = (step + 1) % 2;
        ++step;
        st = prediction();
        return true;
    }
    else {
        return false;
    }
}

void Game::in1() {
    cout << "Enter" << endl;
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int k;
        cin >> k;
        put(k);
    }
    print();
}

void Game::in2() {
    char c;
    bool flag = false;
    while (!flag) {
        int x = 0;
        int o = 0;
        for (int &i : a) {
            cin >> c;
            if (c == '0' || c == 'o' || c == 'O') {
                i = 0;
                ++step;
                ++o;
            }
            if (c == '1' || c == 'X' || c == 'x') {
                i = 1;
                ++step;
                ++x;
            }
        }
        if (x - o == 1 || x - o == 0) {
            flag = true;
        }
        else {
            cout << "Incorrect" << endl;
            for (int &i : a) {
                i = -1;
            }
            step = 0;
        }
    }
    st = prediction();
}

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

int main() {
    int T = 1;
    while (T == 1) {
        go();
        cin >> T;
    }
    return 0;
}
