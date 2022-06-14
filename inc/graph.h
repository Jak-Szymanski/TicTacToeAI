#pragma once

#include "dequeueptr.h"

#define SEARCH_DEPTH 1



template<typename Type>
class Graph{

    private:

        Dequeue<Vertex<Type>*> VQueue;

        Dequeue<Edge<Type>*> EQueue;

    public:

        Graph();

        Graph(const Graph<Type> &G);

        Dequeue<Vertex<Type>*>* Vertices(){return &VQueue;};

        Dequeue<Edge<Type>*>* Edges(){return &EQueue;};

        virtual Vertex<Type>* InsertVertex(Type x);

        virtual Edge<Type>* InsertEdge(int x, Vertex<Type>* start, Vertex<Type>* end);

        virtual Dequeue<Edge<Type>*> StartingEdges(Vertex<Type>* V) const;

        virtual Dequeue<Edge<Type>*> IncidentEdges(Vertex<Type>* V) const;

        virtual Dequeue<Vertex<Type>*> AdjacentVertices(Vertex<Type>* V) const;

        virtual bool AreAdjacent(Vertex<Type>* V1, Vertex<Type>* V2) const;

        virtual void RemoveEdge(Edge<Type>* E);

        virtual void RemoveVertex(Vertex<Type>* V);

        int NumberVertices() const {return VQueue.Size();};

        int NumberEdges() const {return EQueue.Size();};

        void Delete();

        void CreateFutureMovesTree(Vertex<Type>* V1, int i);

        int Min(Vertex<Type>* V, int *alpha, int *beta);

        int Max(Vertex<Type>* V, int *alpha, int *beta);

        int Minimax(Vertex<Type>* V, int* alpha, int* beta);

        Type GetMaxMove(Vertex<Type>* V);

        friend std::ostream &operator << (std::ostream &out, Graph<Type> &graph);
};



template<typename Type>
Graph<Type>::Graph(){

    VQueue = Dequeue<Vertex<Type>*>();
    EQueue = Dequeue<Edge<Type>*>();
}

template<typename Type>
Graph<Type>::Graph(const Graph<Type> &G){

    Node<Vertex<Type>*> *ptr_v = G.VQueue.GetHead();
    while(ptr_v != NULL){
        Vertex<Type> tmp_v = *ptr_v->GetElem();
        VQueue.InsertEnd(&tmp_v);
        ptr_v = ptr_v->GetNext();
    }

    Node<Edge<Type>*> *ptr_e = G.EQueue.GetHead();
    while(ptr_e != NULL){
        Edge<Type> tmp_e = *ptr_e->GetElem();
        EQueue.InsertEnd(&tmp_e);
        ptr_e = ptr_e->GetNext();
    }
}




template<typename Type>
std::ostream &operator << (std::ostream &out, Graph<Type> &graph){
    out << "Wierzcholki: " << std::endl << *graph.Vertices();
    out << "Krawedzie: " << std::endl << *graph.Edges();
    return out;
}


template<typename Type>
Vertex<Type>* Graph<Type>::InsertVertex(Type x){

    auto V = new Vertex<Type>(x);

    VQueue.InsertFront(V);
    VQueue.GetHead()->GetElem()->SetPos(VQueue.GetHead());
    return V;    
}


template<typename Type>
Edge<Type>* Graph<Type>::InsertEdge(int x, Vertex<Type>* start, Vertex<Type>* end){

    auto E = new Edge<Type>(x,start,end);

    EQueue.InsertFront(E);
    EQueue.GetHead()->GetElem()->SetPos(EQueue.GetHead());
    return E;
}


template<typename Type>
Dequeue<Edge<Type>*> Graph<Type>::StartingEdges(Vertex<Type>* V) const{

    Dequeue<Edge<Type>*> dequeue;
    
    Node<Edge<Type>*> *ptr = EQueue.GetHead();
    while(ptr != NULL){
        if (*ptr->GetElem()->GetStart() == *V){
            dequeue.InsertFront(ptr->GetElem());
        }
        ptr = ptr->GetNext();
    }
    return dequeue;
}


template<typename Type>
Dequeue<Edge<Type>*> Graph<Type>::IncidentEdges(Vertex<Type>* V) const{

    Dequeue<Edge<Type>*> dequeue;
    
    Node<Edge<Type>*> *ptr = EQueue.GetHead();
    while(ptr != NULL){
        if (*ptr->GetElem()->GetStart() == *V || *ptr->GetElem()->GetEnd() == *V){
            dequeue.InsertFront(ptr->GetElem());
        }
        ptr = ptr->GetNext();
    }
    return dequeue;    
}


template<typename Type>
Dequeue<Vertex<Type>*> Graph<Type>::AdjacentVertices(Vertex<Type>* V) const{

    Dequeue<Edge<Type>*> incident = StartingEdges(V);
    Dequeue<Vertex<Type>*> adjacent;

    while(!incident.IsEmpty()){
        adjacent.InsertFront(incident.RemoveFirst()->GetEnd());
    }
    return adjacent;
}

template<typename Type>
bool Graph<Type>::AreAdjacent(Vertex<Type>* V1, Vertex<Type>* V2) const {

    Node<Edge<Type>*>* ptr = EQueue.GetHead();

    while(ptr != NULL){
        if(ptr->GetElem()->GetStart() == V1 && ptr->GetElem()->GetEnd() == V2) return true;
        ptr = ptr->GetNext();
    }
    return false;
}

template<typename Type>
void Graph<Type>::RemoveEdge(Edge<Type>* E){

    Node<Edge<Type>*>* ptr = E->GetPos();

    if(ptr == EQueue.GetHead()){
        EQueue.RemoveFirst();
        return;
    } 
    if(ptr == EQueue.GetTail()){
        EQueue.RemoveLast();
        return;
    }

    ptr->GetPrev()->SetNext(ptr->GetNext());
    ptr->GetNext()->SetPrev(ptr->GetPrev());
    delete ptr;
}

template<typename Type>
void Graph<Type>::RemoveVertex(Vertex<Type>* V){

   Node<Edge<Type>*>* ptr_e = IncidentEdges(V).GetHead();

    while(ptr_e != NULL){
        RemoveEdge(ptr_e->GetElem());
        ptr_e = ptr_e->GetNext();
    }

    Node<Vertex<Type>*>* ptr_v = V->GetPos();

    if(ptr_v == VQueue.GetHead()){
        VQueue.RemoveFirst();
        return;
    } 
    if(ptr_v == VQueue.GetTail()){
        VQueue.RemoveLast();
        return;
    }

    ptr_v->GetPrev()->SetNext(ptr_v->GetNext());
    ptr_v->GetNext()->SetPrev(ptr_v->GetPrev());
    delete ptr_v;
}


template<typename Type>
void Graph<Type>::Delete(){

    VQueue.Delete();
    EQueue.Delete();
}




