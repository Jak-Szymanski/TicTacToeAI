#pragma once

#include "vertex.h"
#include "edge.h"

class AdjacencyListVertex: public Vertex{

    private:

        Dequeue<Edge*>* AdjListPos;

    public:

        AdjacencyListVertex();

        AdjacencyListVertex(Vertex V);

        void SetAdjListPos(Dequeue<Edge*>* new_adjlistpost) {AdjListPos = new_adjlistpost;};
};