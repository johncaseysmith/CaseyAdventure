#ifndef EDGEVISITEDLIST_H
#define EDGEVISITEDLIST_H

#include <vector>
#include "Edge.h"

using std::vector;

class EdgeVisitedList
{
    public:
        EdgeVisitedList(vector<Edge> el) : edges(el), visited(vector<bool>(el.size())) { }
        ~EdgeVisitedList();

        vector<Edge> edges;
        vector<bool> visited;

        bool get(Edge e) { for(unsigned int i=0; i<edges.size(); i++) if(edges[i] == e) return visited[i]; return false; }
        void set(Edge e) { for(unsigned int i=0; i<edges.size(); i++) if(edges[i] == e) visited[i] = true; }
    protected:
    private:
};

#endif // EDGEVISITEDLIST_H
