#ifndef ROOM_H
#define ROOM_H

#include <vector>
#include "block.h"

using std::vector;

class Room
{
    public:
        Room() : id(), x(), y(), north(0), east(0), south(0), west(0), objects() { }
        Room(int idnum) : id(idnum), x(), y(), north(0), east(0), south(0), west(0), objects() {  }
        Room(int idnum, int _x, int _y) : id(idnum), x(_x), y(_y), north(0), east(0), south(0), west(0), objects() { }
        ~Room();

        int id;
        int x;
        int y;
        Room* north;
        Room* east;
        Room* south;
        Room* west;
        vector<Block*> objects;
    protected:
    private:
};

#endif // ROOM_H
