#ifndef XO_GAME_H
#define XO_GAME_H

#include "functions.h"

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

#endif
