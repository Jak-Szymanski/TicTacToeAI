#pragma once

#include "node.h"
#include "dequeue.h"
#include "vertex.h"
#include "edge.h"

template <int Size>
class Graph{

    private:

        Dequeue<Vertex<Size>> VQueue;

        Dequeue<Edge<Size>> EQueue;

    public:

        Dequeue<Vertex<Size>> Vertices() const {return VQueue;};

        Dequeue<Edge<Size>> Edges() const{return EQueue;};

        Vertex<Size> InsertVertex(GameState<Size> x);

        Edge<Size> InsertEdge(GameState<Size> x, Vertex<Size>* start, Vertex<Size>* end);
};


template <int Size>
Vertex<Size> Graph<Size>::InsertVertex(GameState<Size> x){

    Vertex<Size> V(x);
    VQueue.InsertFront(V);
    VQueue.Head->Elem.Pos = VQueue.Head;
    return V;    
}

template <int Size>
Edge<Size> Graph<Size>::InsertEdge(GameState<Size> x, Vertex<Size>* start, Vertex<Size>* end){

    Edge<Size> E(x,start,end);
    EQueue.InsertFront(E);
    EQueue.Head->Elem.Pos = EQueue.Head;
    return E;
}