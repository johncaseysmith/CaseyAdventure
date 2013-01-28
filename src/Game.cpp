#include <cstdlib>
#include <ctime>
#include <iostream>
#include <deque>
#include <map>
#include "../include/Game.h"
#include "../include/EdgeVisitedList.h"

using std::vector;
using std::deque;
using std::map;
using std::cout;
using std::endl;

Game::~Game()
{
    //dtor
}

bool Game::generate_dungeon(Dungeon& d, int rooms)
{
    srand(time(NULL));

    vector<Vertex> vl(rooms);
    vector<Edge> el(0);

    // Add all the vertices in the graph
    for (int i=0; i<rooms; i++)
        vl[i] = Vertex(i);

    // Color the first vertex black
    vl[0].color = 0;
    for (int i=0; i<rooms; i++)
    {
        // If necessary, change the vertex's color
        if (i && vl[i].color < 0) vl[i].color = !(vl[i-1].color);

        // Random chance of adding an edge
        int add = rand() % 4;
        while (add)
        {
            // Random vertex to add to the edge, only if it's a valid match
            int vid = rand() % rooms;
            if (vl[i].degree < 4 && vl[vid].degree < 4 && vl[vid].color != vl[i].color)
            {
                Edge newEdge(vl[i], vl[vid]);
                if (!Game::el_contains(el, newEdge))
                {
                    if (vl[vid].color < 0) vl[vid].color = !vl[i].color;
                    vl[i].degree++;
                    vl[vid].degree++;
                    cout << newEdge << endl;
                    el.push_back(newEdge);
                }
            }
            add = rand() % 4;
        }
    }

    vector<Edge> bfs = BFS(el);
    cout << endl << "BFS" << endl;
    for (unsigned int i=0; i<bfs.size(); i++) cout << bfs[i] << endl;

    if ((el.size() - bfs.size()) > (el.size() / 5)) return false;

    Dungeon dungeon(bfs.size());
    Room* startRoom = new Room(bfs[0].v1.id, dungeon.cols/2, dungeon.cols/2);
    dungeon.roomMap[startRoom->id] = startRoom;
    dungeon.rooms[startRoom->y * dungeon.cols + startRoom->x] = startRoom;
    dungeon.start = startRoom;
    io.current = startRoom;

    cout << endl << "Dungeon Time" << endl;

    for (unsigned int i=0; i<bfs.size(); i++)
    {
        int failsafe = 0;
        Edge e = bfs[i];
        int id = dungeon.roomMap[e.v1.id] ? e.v1.id : e.v2.id;
        cout << id << " ";
        int newid = dungeon.roomMap[e.v1.id] ? e.v2.id : e.v1.id;
        Room* room = dungeon.roomMap[id];
        if (dungeon.roomMap[newid])
        {
            Room* room2 = dungeon.roomMap[newid];
            if ((room->x == room2->x) && (room->y == room2->y-1))
            {
                cout << "n " << room2->id << " *" << endl;
                room->north = room2;
                room2->south = room;
            }
            else if ((room->x == room2->x-1) && (room->y == room2->y))
            {
                cout << "e " << room2->id << " *" << endl;
                room->east = room2;
                room2->west = room;
            }
            else if ((room->x == room2->x) && (room->y == room2->y+1))
            {
                cout << "s " << room2->id << " *" << endl;
                room->south = room2;
                room2->north = room;
            }
            else if ((room->x == room2->x+1) && (room->y == room2->y))
            {
                cout << "w " << room2->id << " *" << endl;
                room->west = room2;
                room2->east = room;
            }
            else
            {
                cout << "nope" << endl;
                continue;
            }
            dungeon.boss = room2;
            continue;
        }
        Room* newRoom = new Room(newid);

        bool ok = false;
        while(!ok)
        {
            failsafe++;
            int dir = rand() % 4;
            if (dir == 0)
            {
                cout << dungeon.rooms[room->y-1 * dungeon.cols + room->x] << endl;
                if (room->north == NULL && !dungeon.rooms[room->y-1 * dungeon.cols + room->x])
                {
                    cout << "n " << newRoom->id << endl;
                    room->north = newRoom;
                    newRoom->south = room;
                    newRoom->x = room->x;
                    newRoom->y = room->y-1;
                    dungeon.rooms[newRoom->y * dungeon.cols + newRoom->x] = newRoom;
                    dungeon.roomMap[newid] = newRoom;
                    ok = true;
                }
            }
            else if (dir == 1)
            {
                if (room->east == NULL && !dungeon.rooms[room->y * dungeon.cols + room->x+1])
                {
                    cout << "e " << newRoom->id << endl;
                    room->east = newRoom;
                    newRoom->west = room;
                    newRoom->x = room->x+1;
                    newRoom->y = room->y;
                    dungeon.rooms[newRoom->y * dungeon.cols + newRoom->x] = newRoom;
                    dungeon.roomMap[newid] = newRoom;
                    ok = true;
                }
            }
            else if (dir == 2)
            {
                if (room->south == NULL && !dungeon.rooms[room->y+1 * dungeon.cols + room->x])
                {
                    cout << "s " << newRoom->id << endl;
                    room->south = newRoom;
                    newRoom->north = room;
                    newRoom->x = room->x;
                    newRoom->y = room->y+1;
                    dungeon.rooms[newRoom->y * dungeon.cols + newRoom->x] = newRoom;
                    dungeon.roomMap[newid] = newRoom;
                    ok = true;
                }
            }
            else
            {
                if (room->west == NULL && !dungeon.rooms[room->y * dungeon.cols + room->x-1])
                {
                    cout << "w " << newRoom->id << endl;
                    room->west = newRoom;
                    newRoom->east = room;
                    newRoom->x = room->x-1;
                    newRoom->y = room->y;
                    dungeon.rooms[newRoom->y * dungeon.cols + newRoom->x] = newRoom;
                    dungeon.roomMap[newid] = newRoom;
                    ok = true;
                }
            }
            if (failsafe > dungeon.size) return false;
            dungeon.boss = newRoom;
        }
    }

    for (int i=0; i<dungeon.cols; i++)
    {
        for (int j=0; j<dungeon.cols; j++)
        {
            Room* r = dungeon.rooms[i*dungeon.cols+j];
            if (r) cout << r->id;
            else cout << " ";
            cout << " ";
        }
        cout << endl;
    }

    cout << "Start: " << dungeon.start->id << endl;
    cout << "Boss: " << dungeon.boss->id << endl;

    d = dungeon;
    return true;

}

void Game::populate_dungeon(Dungeon& dungeon)
{
    srand(time(NULL));
    Room* current;
    dungeon.enemies = 0;

    for (int i=0; i<dungeon.cols; i++)
    {
        if (dungeon.roomMap[i] && dungeon.roomMap[i] != dungeon.start && dungeon.roomMap[i] != dungeon.boss) {
            current = dungeon.roomMap[i];
            int roomType = (rand() % 5) + 1;
            int number = (rand() % 5) + 1;
            // add monsters
            for (int x = 0; x < roomType; x++) {
                dungeon.enemies++;
                current->objects.push_back(new Monster((rand() % 50) + 10, (rand() % 20) + 10));
            }
            // add treasure
            for (int x = 0; x < number; x++) {
                dungeon.monies++;
                current->objects.push_back(new Treasure((rand() % 50) + 10, (rand() % 20) + 10));
            }
        }
    }
}

// Checks to see if an edge is already in the edge list. It's miserable, I know. But it works.
bool Game::el_contains(vector<Edge> el, Edge e)
{
    for (unsigned int i=0; i<el.size(); i++)
    {
        if (el[i] == e) return true;
    }
    return false;
}

// Breadth-first-search with edges
vector<Edge> Game::BFS(vector<Edge> el)
{
    vector<Edge> bfs(0);
    deque<Vertex> q(0);
    EdgeVisitedList visited(el); // SCREW PASS BY VALUE

    q.push_back(el[0].v1);
    while (!q.empty())
    {
        Vertex v = q.front();
        q.pop_front();

        vector<Edge> edgesfor = findEdgesFor(v, el);
        for (unsigned int i=0; i<edgesfor.size(); i++)
        {

            if (!visited.get(edgesfor[i]))
            {
                visited.set(edgesfor[i]);
                bfs.push_back(edgesfor[i]);
                if (edgesfor[i].v1 == v)
                    q.push_back(edgesfor[i].v2);
                else
                    q.push_back(edgesfor[i].v1);
            }
        }
    }

    return bfs;
}

// Finds the edges in edge list el that include vertex v
vector<Edge> Game::findEdgesFor(Vertex v, vector<Edge> el)
{
    vector<Edge> edges(0);

    for (unsigned int i=0; i<el.size(); i++)
        if (el[i].v1 == v || el[i].v2 == v)
            edges.push_back(el[i]);

    return edges;
}


