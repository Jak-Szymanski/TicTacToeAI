#pragma once

#include "adjlistvertex.h"

/*Krawędź grafu zawierającego obiekty typu Type
  Jest ona rozszerzeniem zwykłej krawędzi i jest używana w grafie opisanego przez listę sąsiedztwa*/
template<typename Type>
class AdjacencyListEdge: public Edge<Type>{

    private:

        /*Pozycja danej krawędzi w kolejce sąsiedztwa wierzchołka na początku krawędzi*/
        Node<Edge<Type>*>* AdjListStart;

        /*Pozycja danej krawędzi w kolejce sąsiedztwa wierzchołka na końcu krawędzi*/
        Node<Edge<Type>*>* AdjListEnd;

    public:

        AdjacencyListEdge();

        AdjacencyListEdge(Edge<Type> E);

        AdjacencyListEdge(int x, Vertex<Type>* new_start, Vertex<Type>* new_end);

        void SetAdjListStart(Node<Edge<Type>*>* new_adjliststart) {AdjListStart = new_adjliststart;};

        void SetAdjListEnd(Node<Edge<Type>*>* new_adjlistend) {AdjListEnd = new_adjlistend;};

        Node<Edge<Type>*>* GetAdjListStart() {return AdjListStart;};

        Node<Edge<Type>*>* GetAdjListEnd() {return AdjListEnd;};


    
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
AdjacencyListEdge<Type>::AdjacencyListEdge(int x, Vertex<Type>* new_start, Vertex<Type>* new_end){

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