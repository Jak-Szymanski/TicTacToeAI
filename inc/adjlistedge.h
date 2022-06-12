#pragma once

#include "adjlistvertex.h"

class AdjacencyListEdge: public Edge{

    private:

        Node<std::shared_ptr<Edge>>* AdjListStart;

        Node<std::shared_ptr<Edge>>* AdjListEnd;

    public:

        AdjacencyListEdge();

        AdjacencyListEdge(Edge E);

        AdjacencyListEdge(int x, std::shared_ptr<Vertex> new_start, std::shared_ptr<Vertex> new_end);

        void SetAdjListStart(Node<std::shared_ptr<Edge>>* new_adjliststart) {AdjListStart = new_adjliststart;};

        void SetAdjListEnd(Node<std::shared_ptr<Edge>>* new_adjlistend) {AdjListEnd = new_adjlistend;};

        Node<std::shared_ptr<Edge>>* GetAdjListStart() {return AdjListStart;};

        Node<std::shared_ptr<Edge>>* GetAdjListEnd() {return AdjListEnd;};


    
};