#pragma once

#define SEARCH_DEPTH 4

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

        Dequeue<Edge<Size>> IncidentEdges(Vertex<Size> *V) const;

        Dequeue<Vertex<Size>> AdjacentVertices(Vertex<Size> *V) const;

        void Delete();

        //void CreateGraph (GameState<Size> GS);

        void CreateFutureMovesTree(Vertex<Size>* V1, int i);

        void Min(Vertex<Size> *V);

        void Max(Vertex<Size> *V);

        void Minimax(Vertex<Size> *V);

        GameState<Size> GetMaxMove(Vertex<Size> *V);
};

/* template<int Size>
void Graph<Size>::CreateGraph (GameState<Size> GS){

} */

template<int Size>
void Graph<Size>::CreateFutureMovesTree (Vertex<Size>* V1, int i){

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
            CreateFutureMovesTree(V2, i-1);
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

template<int Size>
Dequeue<Edge<Size>> Graph<Size>::IncidentEdges(Vertex<Size> *V) const{

    Dequeue<Edge<Size>> dequeue;
    
    Node<Edge<Size>> *ptr = EQueue.GetHead();
    while(ptr != NULL){
        if (ptr->GetElem().GetStart() == *V){
            dequeue.InsertFront(ptr->GetElem());
        }
        ptr = ptr->GetNext();
    }
    return dequeue;
}

template<int Size>
Dequeue<Vertex<Size>> Graph<Size>::AdjacentVertices(Vertex<Size> *V) const{

    Dequeue<Edge<Size>> incident = IncidentEdges(V);
    Dequeue<Vertex<Size>> adjacent;

    while(!incident.IsEmpty()){
        adjacent.InsertFront(incident.RemoveFirst().GetEnd());
    }
    return adjacent;
}

template<int Size>
void Graph<Size>::Delete(){

    VQueue.Delete();
    EQueue.Delete();
}


template<int Size>
void Graph<Size>::Min(Vertex<Size> *V){

    Dequeue<Vertex<Size>> adjacent = AdjacentVertices(V);
    int min = 100;
    int tmp_cost;

    while(!adjacent.IsEmpty()){
        tmp_cost = adjacent.RemoveFirst().GetObject().GetCost();
        if(tmp_cost < min){
            min = tmp_cost;
        }
    }
    V->SetCost(min);
}


template<int Size>
void Graph<Size>::Max(Vertex<Size> *V){

    Dequeue<Vertex<Size>> adjacent = AdjacentVertices(V);
    int max = -100;
    int tmp_cost;

    while(!adjacent.IsEmpty()){
        tmp_cost = adjacent.RemoveFirst().GetObject().GetCost();
        if(tmp_cost > max){
            max = tmp_cost;
        }
    }
    V->SetCost(max);
}

template<int Size>
void Graph<Size>::Minimax(Vertex<Size> *V){

    if (IncidentEdges(V).IsEmpty()){
        if(V->GetObject().NextMove == 1){
            Max(V);
        } else {
            Min(V);
        }
        return;
    }

    Dequeue<Vertex<Size>> adjacent = AdjacentVertices(V);

    while (!adjacent.IsEmpty()){
        Minimax(&adjacent.RemoveFirst());
    }

    if(V->GetObject().NextMove == 1){
        Max(V);
    } else {
        Min(V);
    }
}

template<int Size>
GameState<Size> Graph<Size>::GetMaxMove(Vertex<Size> *V){

    Dequeue<Vertex<Size>> adjacent = AdjacentVertices(V);
    GameState<Size> GS;

    while(!adjacent.IsEmpty()){
        GS = adjacent.RemoveFirst().GetObject();
        if(GS.GetCost() == V->GetObject().GetCost()){
            return GS;  
        }
    }
}