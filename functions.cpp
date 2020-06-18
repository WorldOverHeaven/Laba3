#include "functions.h"
#include "iostream"
#include "Game.h"
#include "Tree.h"
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
