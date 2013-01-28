#include "../include/Edge.h"

Edge::~Edge()
{
    //dtor
}

std::ostream& operator<<( std::ostream& os, const Edge& e)
{
    os << "[ " << e.v1.id << ", " << e.v2.id << " ]";
    return os;
}
