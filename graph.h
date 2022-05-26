#pragma once

#define SEARCH_DEPTH 2

#include "dequeue.h"
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

        //void CreateGraph (GameState<Size> GS);

        void SearchGraph(Vertex<Size>* V1, int i);
};

/* template<int Size>
void Graph<Size>::CreateGraph (GameState<Size> GS){

} */

template<int Size>
void Graph<Size>::SearchGraph (Vertex<Size>* V1, int i){

    if(i==0) return;

    Dequeue<GameState<Size>> possible_moves;
    Vertex<Size> *V2 = new Vertex<Size>();
    GameState<Size> tmp_gs;

    possible_moves = V1->GetObject().GeneratePossibleMoves();

    while(!possible_moves.IsEmpty()){
        tmp_gs = possible_moves.RemoveFirst();
        V2 = InsertVertex(tmp_gs);
        InsertEdge(1,V1,V2);
        if(tmp_gs.Cost != Size && tmp_gs.Cost != -Size){
            SearchGraph(V2, i-1);
        }
    }
}




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
   //std::cout << *V << std::endl;
    return V;    
}

template <int Size>
Edge<Size> Graph<Size>::InsertEdge(int x, Vertex<Size>* start, Vertex<Size>* end){

    Edge<Size> E(x,start,end);
    EQueue.InsertFront(E);
    EQueue.GetHead()->GetElem().SetPos(EQueue.GetHead());
    return E;
}