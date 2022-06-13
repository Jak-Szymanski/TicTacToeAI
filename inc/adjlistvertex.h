#pragma once

#include "graph.h"

class AdjacencyListVertex: public Vertex{

    private:

        Dequeue<std::shared_ptr<Edge>>* AdjList;

    public:

        AdjacencyListVertex();

        AdjacencyListVertex(Vertex V);

        void SetAdjList(Dequeue<std::shared_ptr<Edge>>* new_adjlist) {AdjList = new_adjlist;};

        Dequeue<std::shared_ptr<Edge>>* GetAdjList() {return AdjList;};

        //void SetAdjListPos(Dequeue<std::shared_ptr<Edge>>* new_adjlistpos){AdjListPos = new_adjlistpos;};
};