#ifndef DUNGEON_H
#define DUNGEON_H

#include <vector>
#include <map>
#include "Room.h"

using std::vector;
using std::map;

class Dungeon
{
    public:
        Dungeon() : size(), rooms() { }
        Dungeon(int col) : size(col*col), cols(col), rooms(col*col), enemies(0), monies(0) { }
        ~Dungeon();

        int size;
        int enemies;
        int monies;
        int cols;
        vector<Room*> rooms;
        map<int, Room*> roomMap;
        Room* start;
        Room* boss;

        void operator=(const Dungeon& d) { size = d.size; cols = d.cols; rooms = d.rooms; roomMap = d.roomMap; start = d.start; boss = d.boss; }
    protected:
    private:
};

#endif // DUNGEON_H
