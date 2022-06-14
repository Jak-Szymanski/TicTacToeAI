#pragma once

#include "vertex.h"

/*Wierzchołek grafu zawierającego obiekty typu Type
  Jest on rozszerzeniem zwykłego wierzchołka i jest używany w grafie opisanego przez macierz sąsiedztwa*/
template<typename Type>
class AdjacencyMatrixVertex: public Vertex<Type>{

    private:

        /*Indeks wierzchołka w macierzy sąsiedztwa*/
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