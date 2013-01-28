#ifndef TREASURE_H
#define TREASURE_H

#include <Windows.h>
#include "../include/block.h"

#define FOREGROUND_YELLOW FOREGROUND_RED | FOREGROUND_GREEN

class Treasure : public Block
{
    public:
        Treasure(int _x, int _y) : Block::Block(_x, _y) {
            setAsciiChar(0x24);
            setAttributes(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
        }
    protected:
    private:
};

#endif // TREASURE_H
