#pragma once

#include "adjlistedge.h"


class AdjacencyListGraph: public Graph{

    private:

        Dequeue<Dequeue<std::shared_ptr<Edge>>> AdjacencyList;

    public:

        //AdjacencyListGraph();

        AdjacencyListGraph(const Graph G);

        friend std::ostream &operator << (std::ostream &out, AdjacencyListGraph const &graph);

        //Dequeue<Dequeue<AdjacencyListEdge*>> GetAdjacencyList() const {return AdjacencyList;};

};

