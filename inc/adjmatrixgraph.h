#pragma once

#include "graph.h"
#include "adjmatrixvertex.h"

class AdjacencyMatrixGraph: public Graph{

    private:

        std::vector<std::vector<std::shared_ptr<Edge>>> AdjacencyMatrix;

    public:

        AdjacencyMatrixGraph(const Graph G);

        friend std::ostream &operator << (std::ostream &out, AdjacencyMatrixGraph const &graph);

};