#include "../include/Vertex.h"

Vertex::~Vertex()
{
    //dtor
}

std::ostream& operator<<( std::ostream& os, const Vertex& v)
{
    os << "{" << v.id << "}";
    return os;
}
