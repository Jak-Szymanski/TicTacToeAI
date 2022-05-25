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

        Dequeue<Vertex<Size>> Vertices() const {return VQueue;};

        Dequeue<Edge<Size>> Edges() const {return EQueue;};

        Vertex<Size>* InsertVertex(GameState<Size> x);

        Edge<Size> InsertEdge(int x, Vertex<Size>* start, Vertex<Size>* end);
};



template<int Size>
std::ostream &operator << (std::ostream &out, Graph<Size> const &graph){
    out << "Wierzcholki: " << std::endl << graph.Vertices();
    out << "Krawedzie: " << std::endl << graph.Edges();
    return out;
}


template <int Size>
Vertex<Size>* Graph<Size>::InsertVertex(GameState<Size> x){

    Vertex<Size> *V = new Vertex<Size>(x);
    VQueue.InsertFront(*V);
    VQueue.GetHead()->GetElem().SetPos(VQueue.GetHead());
   // std::cout << V << std::endl;
    return V;    
}

template <int Size>
Edge<Size> Graph<Size>::InsertEdge(int x, Vertex<Size>* start, Vertex<Size>* end){

    Edge<Size> E(x,start,end);
    EQueue.InsertFront(E);
    EQueue.GetHead()->GetElem().SetPos(EQueue.GetHead());
    return E;
}