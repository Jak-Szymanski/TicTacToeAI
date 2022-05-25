#pragma once

#include "dequeue.h"
#include "vertex.h"
#include "edge.h"

template <int Size>
class Graph{

    private:

        Dequeue<Vertex<Size>> VQueue;

        Dequeue<Edge<Size>> EQueue;

    public:

        Dequeue<Vertex<Size>> Vertices() const;

        Dequeue<Edge<Size>> Edges() const;

        Vertex<Size> InsertVertex(GameState<Size> x);

        Edge<Size> InsertEdge(GameState<Size> x, Vertex<Size>* start, Vertex<Size>* end);
};

/* 
template<int Size>
Dequeue<Vertex<Size>> Graph<Size>::Vertices() const{
    return VQueue;
}


template<int Size>
std::ostream &operator << (std::ostream &out, Graph<Size> const &graph){
    out << "Wierzchołki: " << std::endl << graph.Vertices();
    out << "Krawędzie: " << std::endl << graph.Edges();
    return out;
}


template <int Size>
Vertex<Size> Graph<Size>::InsertVertex(GameState<Size> x){

    Vertex<Size> V(x);
    VQueue.InsertFront(V);
    VQueue.GetHead()->GetElem().SetPos(VQueue.GetHead());
    return V;    
}

template <int Size>
Edge<Size> Graph<Size>::InsertEdge(GameState<Size> x, Vertex<Size>* start, Vertex<Size>* end){

    Edge<Size> E(x,start,end);
    EQueue.InsertFront(E);
    EQueue.Head->Elem.Pos = EQueue.Head;
    return E;
} */