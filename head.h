#ifndef XO_HEAD_H
#define XO_HEAD_H
enum status {
    win0,
    winX,
    draw,
    endGame
};
int factorial(int);

void go();

class Game {
private:
    int a[9]{};
    int step;
    status st;
public:
    Game();
    Game(const Game & obj);
    int getStep();
    status getStatus();
    void print();
    status prediction();
    bool put(int y);
    void in1();
    void in2();
};

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
#endif //XO_HEAD_H
