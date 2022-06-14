#pragma once

#include "graph.h"

template<typename Type>
class AdjacencyListVertex: public Vertex<Type>{

    private:

        Dequeue<std::shared_ptr<Edge<Type>>>* AdjList;

    public:

        AdjacencyListVertex();

        AdjacencyListVertex(Vertex<Type> V);

        void SetAdjList(Dequeue<std::shared_ptr<Edge<Type>>>* new_adjlist) {AdjList = new_adjlist;};

        Dequeue<std::shared_ptr<Edge<Type>>>* GetAdjList() {return AdjList;};

        //void SetAdjListPos(Dequeue<std::shared_ptr<Edge>>* new_adjlistpos){AdjListPos = new_adjlistpos;};
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