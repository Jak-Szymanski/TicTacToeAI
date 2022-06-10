#pragma once

#include "graph.h"
#include "adjlistvertex.h"
#include "adjlistedge.h"


class AdjacencyListGraph{

    private:

        Dequeue<AdjacencyListVertex> VQueue;

        Dequeue<AdjacencyListEdge> EQueue;

        Dequeue<Dequeue<AdjacencyListEdge*>> AdjacencyList;

    public:

        //AdjacencyListGraph();

        AdjacencyListGraph(Graph G);

        friend std::ostream &operator << (std::ostream &out, Graph const &graph);

};

