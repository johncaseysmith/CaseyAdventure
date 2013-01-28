#ifndef EDGE_H
#define EDGE_H

#include <iostream>
#include "../include/Vertex.h"

class Edge
{
    public:
        Edge() : v1(), v2() {}
        Edge(Vertex u, Vertex v) : v1(u), v2(v) { }
        ~Edge();

        Vertex v1;
        Vertex v2;

        bool operator==(const Edge& e) { return (v1 == e.v1 && v2 == e.v2) || (v1 == e.v2 && v2 == e.v1); }
        friend std::ostream& operator<<( std::ostream& os, const Edge& e);
    protected:
    private:
};

#endif // EDGE_H
