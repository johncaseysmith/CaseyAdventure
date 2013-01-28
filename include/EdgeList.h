#ifndef EDGELIST_H
#define EDGELIST_H

#include <vector>
#include "../include/Edge.h"

using std::vector;

class EdgeList
{
    public:
        EdgeList();
        ~EdgeList();

        vector<Edge> edges;
    protected:
    private:
};

#endif // EDGELIST_H
