#ifndef GAME_H
#define GAME_H

#include <vector>
#include "../include/Edge.h"
#include "../include/block.h"
#include "../include/io.h"

using std::vector;

class Game
{
    public:
        Game() : cursor_mode(false) { }
        ~Game();

        bool cursor_mode;
        IO io;
        bool generate_dungeon(Dungeon& d, int rooms);
        void populate_dungeon(Dungeon& dungeon);
        bool el_contains(vector<Edge> el, Edge e);
        vector<Edge> BFS(vector<Edge> el);
        bool compareEdges(Edge& e1, Edge& e2) { return e1.v2.id < e2.v2.id; }
        vector<Edge> findEdgesFor(Vertex v, vector<Edge> el);
    protected:
    private:
};

#endif // GAME_H
