#ifndef PLAYER_H
#define PLAYER_H

#include <Windows.h>
#include "../include/block.h"

#define FOREGROUND_WHITE FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE

class Player : public Block
{
    public:
        Player(int _x, int _y, int _level) : Block::Block(_x, _y), level(_level), health(10), score(0) {
            setAsciiChar(0x01);
            setAttributes(FOREGROUND_WHITE);
        }
        int score;
    protected:
    private:
        int level;
        int health;

};

#endif // PLAYER_H
