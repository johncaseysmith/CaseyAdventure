#ifndef VERTEX_H
#define VERTEX_H

#include <iostream>

class Vertex
{
    public:
        Vertex() : id(), degree(0), color(-1) { }
        Vertex(int idnum) : id(idnum), degree(0), color(-1) { std::cout << "Making vertex with id " << id << std::endl; }
        Vertex(const Vertex& v) : id(v.id), degree(v.degree), color(v.color) {}
        ~Vertex();

        int id;
        int degree;
        int color;

        Vertex& operator=(const Vertex& v) { id = v.id; degree = v.degree; color = v.color; return *this; }
        bool operator==(const Vertex& v) { return id == v.id; }
        friend std::ostream& operator<<( std::ostream& os, const Vertex& v);
    protected:
    private:
};

#endif // VERTEX_H
