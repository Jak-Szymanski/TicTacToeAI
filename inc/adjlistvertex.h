#pragma once

#include "graph.h"

/*Wierzchołek grafu zawierającego obiekty typu Type
  Jest on rozszerzeniem zwykłego wierzchołka i jest używany w grafie opisanego przez listę sąsiedztwa*/
template<typename Type>
class AdjacencyListVertex: public Vertex<Type>{

    private:

        /*Lista sąsiedztwa dla danego wierzchołka*/
        Dequeue<Edge<Type>*>* AdjList;

    public:

        AdjacencyListVertex();

        AdjacencyListVertex(Vertex<Type> V);

        void SetAdjList(Dequeue<Edge<Type>*>* new_adjlist) {AdjList = new_adjlist;};

        Dequeue<Edge<Type>*>* GetAdjList() {return AdjList;};

        //void SetAdjListPos(Dequeue<Edge>>* new_adjlistpos){AdjListPos = new_adjlistpos;};
};

template<typename Type>
AdjacencyListVertex<Type>::AdjacencyListVertex(){

    SetObject(Type());
    SetPos(NULL);
    AdjList = NULL;

}

template<typename Type>
AdjacencyListVertex<Type>::AdjacencyListVertex(Vertex<Type> V){

    SetObject(V.GetObject());
    SetPos(V.GetPos());
    AdjList = NULL;

}