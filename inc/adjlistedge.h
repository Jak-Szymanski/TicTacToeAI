#pragma once

#include "adjlistvertex.h"

template<typename Type>
class AdjacencyListEdge: public Edge<Type>{

    private:

        Node<std::shared_ptr<Edge<Type>>>* AdjListStart;

        Node<std::shared_ptr<Edge<Type>>>* AdjListEnd;

    public:

        AdjacencyListEdge();

        AdjacencyListEdge(Edge<Type> E);

        AdjacencyListEdge(int x, std::shared_ptr<Vertex<Type>> new_start, std::shared_ptr<Vertex<Type>> new_end);

        void SetAdjListStart(Node<std::shared_ptr<Edge<Type>>>* new_adjliststart) {AdjListStart = new_adjliststart;};

        void SetAdjListEnd(Node<std::shared_ptr<Edge<Type>>>* new_adjlistend) {AdjListEnd = new_adjlistend;};

        Node<std::shared_ptr<Edge<Type>>>* GetAdjListStart() {return AdjListStart;};

        Node<std::shared_ptr<Edge<Type>>>* GetAdjListEnd() {return AdjListEnd;};


    
};

template<typename Type>
AdjacencyListEdge<Type>::AdjacencyListEdge(){

    SetObject(0);
    SetPos(NULL);
    SetStart(NULL);
    SetEnd(NULL);
    AdjListStart = NULL;
    AdjListEnd = NULL;
}

template<typename Type>
AdjacencyListEdge<Type>::AdjacencyListEdge(int x, std::shared_ptr<Vertex<Type>> new_start, std::shared_ptr<Vertex<Type>> new_end){

    SetObject(x);
    SetStart(new_start);
    SetEnd(new_end);
    SetPos(NULL);
    AdjListStart = NULL;
    AdjListEnd = NULL; 
}

template<typename Type>
AdjacencyListEdge<Type>::AdjacencyListEdge(Edge<Type> E){

    SetObject(E.GetObject());
    SetPos(E.GetPos());
    SetStart(E.GetStart());
    SetEnd(E.GetEnd());
    AdjListStart = NULL;
    AdjListEnd = NULL;
}