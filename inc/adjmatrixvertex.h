#pragma once

#include "vertex.h"

class AdjacencyMatrixVertex: public Vertex{

    private:

        int Index;

    public:

        AdjacencyMatrixVertex();

        AdjacencyMatrixVertex(Vertex V);

        int GetIndex() const {return Index;};

        void SetIndex (int new_index) {Index = new_index;};

};