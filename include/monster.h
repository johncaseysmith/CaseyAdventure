#ifndef MONSTER_H
#define MONSTER_H

#include <Windows.h>
#include "../include/block.h"

#define FOREGROUND_WHITE FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE

class Monster : public Block
{
    public:
        Monster(int _x, int _y) : Block::Block(_x, _y) {
            setAsciiChar(0x02);
            setAttributes(FOREGROUND_RED | FOREGROUND_INTENSITY);
        }
    protected:
    private:
};

#endif // MONSTER_H
