#ifndef PRINCESS_H
#define PRINCESS_H
#include <Windows.h>
#include "../include/block.h"

#define FOREGROUND_WHITE FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE

class Princess : public Block
{
    public:
        Princess(int _x, int _y) : Block::Block(_x, _y) {
            setAsciiChar(0x0C);
            setAttributes(FOREGROUND_RED | FOREGROUND_INTENSITY);
        }
    protected:
    private:
};

#endif // PRINCESS_H
