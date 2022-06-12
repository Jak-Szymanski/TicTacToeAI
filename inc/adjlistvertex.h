#pragma once

#include "graph.h"

class AdjacencyListVertex: public Vertex{

    private:

        Dequeue<std::shared_ptr<Edge>>* AdjListPos;

    public:

        AdjacencyListVertex();

        AdjacencyListVertex(Vertex V);

        void SetAdjListPos(Dequeue<std::shared_ptr<Edge>>* new_adjlistpos) {AdjListPos = new_adjlistpos;};

        Dequeue<std::shared_ptr<Edge>>* GetAdjListPos() {return AdjListPos;};

        //void SetAdjListPos(Dequeue<std::shared_ptr<Edge>>* new_adjlistpos){AdjListPos = new_adjlistpos;};
};