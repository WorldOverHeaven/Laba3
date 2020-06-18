#include "Game.h"
#include "functions.h"
#include <iostream>
using namespace std;

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
