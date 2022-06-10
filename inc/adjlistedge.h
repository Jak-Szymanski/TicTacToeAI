#pragma once

#include "adjlistvertex.h"

class AdjacencyListEdge: public Edge{

    private:

        std::shared_ptr<Edge>* AdjListStart;

        std::shared_ptr<Edge>* AdjListEnd;

    public:

        AdjacencyListEdge();

        AdjacencyListEdge(Edge E);

        void SetAdjListStart(std::shared_ptr<Edge>* new_adjliststart) {AdjListStart = new_adjliststart;};

        void SetAdjListEnd(std::shared_ptr<Edge>* new_adjlistend) {AdjListEnd = new_adjlistend;};

    
};