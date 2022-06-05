#pragma once

#define SEARCH_DEPTH 3

#include "dequeue.h"
#include "edge.h"


class Graph{

    private:

        Dequeue<Vertex> VQueue;

        Dequeue<Edge> EQueue;

    public:

        Dequeue<Vertex> Vertices() const {return VQueue;};

        Dequeue<Edge> Edges() const {return EQueue;};

        Vertex* InsertVertex(GameState x);

        Edge InsertEdge(int x, Vertex* start, Vertex* end);

        Dequeue<Edge> IncidentEdges(Vertex *V) const;

        Dequeue<Vertex> AdjacentVertices(Vertex *V) const;

        void Delete();

        void CreateFutureMovesTree(Vertex* V1, int i);

        int Min(Vertex *V, int *alpha, int *beta);

        int Max(Vertex *V, int *alpha, int *beta);

        int Minimax(Vertex *V, int* alpha, int* beta);

        GameState GetMaxMove(Vertex *V);
};




void Graph::CreateFutureMovesTree (Vertex* V1, int i){

    if(i==0) return;

    Dequeue<GameState> possible_moves;
    Vertex *V2 = new Vertex();   
    GameState tmp_gs;

    possible_moves = V1->GetObject().GeneratePossibleMoves();

    while(!possible_moves.IsEmpty()){
        tmp_gs = possible_moves.RemoveFirst();
        V2 = InsertVertex(tmp_gs);
        InsertEdge(1,V1,V2);
        if(tmp_gs.Cost != BOARD_SIZE && tmp_gs.Cost != -BOARD_SIZE){
            CreateFutureMovesTree(V2, i-1);
        }
    }

}





std::ostream &operator << (std::ostream &out, Graph const &graph){
    out << "Wierzcholki: " << std::endl << graph.Vertices();
    out << "Krawedzie: " << std::endl << graph.Edges();
    return out;
}



Vertex* Graph::InsertVertex(GameState x){

    Vertex *V = new Vertex(x);
    VQueue.InsertFront(*V);
    VQueue.GetHead()->GetElem().SetPos(VQueue.GetHead());
   //std::cout << *V << std::endl;
    return V;    
}


Edge Graph::InsertEdge(int x, Vertex* start, Vertex* end){

    Edge E(x,start,end);
    EQueue.InsertFront(E);
    EQueue.GetHead()->GetElem().SetPos(EQueue.GetHead());
    return E;
}


Dequeue<Edge> Graph::IncidentEdges(Vertex *V) const{

    Dequeue<Edge> dequeue;
    
    Node<Edge> *ptr = EQueue.GetHead();
    while(ptr != NULL){
        if (ptr->GetElem().GetStart() == *V){
            dequeue.InsertFront(ptr->GetElem());
        }
        ptr = ptr->GetNext();
    }
    return dequeue;
}


Dequeue<Vertex> Graph::AdjacentVertices(Vertex *V) const{

    Dequeue<Edge> incident = IncidentEdges(V);
    Dequeue<Vertex> adjacent;

    while(!incident.IsEmpty()){
        adjacent.InsertFront(incident.RemoveFirst().GetEnd());
    }
    return adjacent;
}


void Graph::Delete(){

    VQueue.Delete();
    EQueue.Delete();
}



int Graph::Min(Vertex *V, int *alpha, int* beta){

    Dequeue<Vertex> adjacent = AdjacentVertices(V);
    int min = 100;
    int tmp_cost;

    while(!adjacent.IsEmpty()){
        tmp_cost = adjacent.RemoveFirst().GetObject().GetCost();
        if(tmp_cost < min){
            min = tmp_cost;
        }
    }
    
    if(min < *alpha) *alpha = min;


    V->SetCost(min);

    if(min > *beta) return 1;
    else return 0;
}



int Graph::Max(Vertex *V, int *alpha, int *beta){

    Dequeue<Vertex> adjacent = AdjacentVertices(V);
    int max = -100;
    int tmp_cost;

    while(!adjacent.IsEmpty()){
        tmp_cost = adjacent.RemoveFirst().GetObject().GetCost();
        if(tmp_cost > max){
            max = tmp_cost;
        }
    }

    if(max > *beta) *beta = max;

    V->SetCost(max);

    if(max < *alpha) return 1;
    else return 0;
}


int Graph::Minimax(Vertex *V, int* alpha, int* beta){

    if (IncidentEdges(V).IsEmpty()){
        if(V->GetObject().NextMove == 1){
            Max(V, alpha, beta);
        } else {
            Min(V, alpha, beta);
        }
        return 0;
    }

    Dequeue<Vertex>* adjacent = &AdjacentVertices(V);

    while (!adjacent->IsEmpty()){
        if(Minimax(&adjacent->RemoveFirst(), alpha, beta)==1){
            while(!adjacent->IsEmpty()){
                adjacent->RemoveFirst();
            }
            break;
        }
    }

    if(V->GetObject().NextMove == 1){
        Max(V, alpha, beta);
    } else {
        Min(V, alpha, beta);
    }
    return 0;
}


GameState Graph::GetMaxMove(Vertex *V){

    Dequeue<Vertex> adjacent = AdjacentVertices(V);
    GameState GS;

    while(!adjacent.IsEmpty()){
        GS = adjacent.RemoveFirst().GetObject();
        if(GS.GetCost() == V->GetObject().GetCost()){
            return GS;  
        }
    }
}