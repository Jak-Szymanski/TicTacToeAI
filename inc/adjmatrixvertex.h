#pragma once

#include "vertex.h"

template<typename Type>
class AdjacencyMatrixVertex: public Vertex<Type>{

    private:

        int Index;

    public:

        AdjacencyMatrixVertex();

        AdjacencyMatrixVertex(Vertex<Type> V);

        int GetIndex() const {return Index;};

        void SetIndex (int new_index) {Index = new_index;};

};

template <typename Type>
AdjacencyMatrixVertex<Type>::AdjacencyMatrixVertex(){
    
    SetObject(Type());
    SetPos(NULL);
    SetIndex(0);
};

template <typename Type>
AdjacencyMatrixVertex<Type>::AdjacencyMatrixVertex(Vertex<Type> V){

    SetObject(V.GetObject());
    SetPos(V.GetPos());
    SetIndex(0);
}