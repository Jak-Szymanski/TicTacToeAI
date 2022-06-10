#pragma once

#include "edge.h"

class AdjacencyListEdge: public Edge{

    private:

        AdjacencyListEdge** AdjListStart;

        AdjacencyListEdge** AdjListEnd;

    public:

        AdjacencyListEdge();

        AdjacencyListEdge(Edge E);

    
};