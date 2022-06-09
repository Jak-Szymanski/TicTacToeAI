#pragma once

#include "graph.h"
#include "adjlistvertex.h"

class AdjacencyListGraph{

    private:

        Dequeue<AdjacencyListVertex> VQueue;

        Dequeue<AdjacencyListEdge> EQueue;

        Dequeue<Dequeue<Edge*>> AdjacencyList;

    public:

        AdjacencyListGraph();

        AdjacencyListGraph(Graph G);

};