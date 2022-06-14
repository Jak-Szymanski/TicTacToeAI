#pragma once

#include "dequeueptr.h"

#define SEARCH_DEPTH 1



template<typename Type>
class Graph{

    private:

        Dequeue<std::shared_ptr<Vertex<Type>>> VQueue;

        Dequeue<std::shared_ptr<Edge<Type>>> EQueue;

    public:

        Graph();

        Graph(const Graph<Type> &G);

        Dequeue<std::shared_ptr<Vertex<Type>>>* Vertices(){return &VQueue;};

        Dequeue<std::shared_ptr<Edge<Type>>>* Edges(){return &EQueue;};

        virtual std::shared_ptr<Vertex<Type>> InsertVertex(Type x);

        virtual std::shared_ptr<Edge<Type>> InsertEdge(int x, std::shared_ptr<Vertex<Type>> start, std::shared_ptr<Vertex<Type>> end);

        virtual Dequeue<std::shared_ptr<Edge<Type>>> StartingEdges(std::shared_ptr<Vertex<Type>> V) const;

        virtual Dequeue<std::shared_ptr<Edge<Type>>> IncidentEdges(std::shared_ptr<Vertex<Type>> V) const;

        virtual Dequeue<std::shared_ptr<Vertex<Type>>> AdjacentVertices(std::shared_ptr<Vertex<Type>> V) const;

        virtual bool AreAdjacent(std::shared_ptr<Vertex<Type>> V1, std::shared_ptr<Vertex<Type>> V2) const;

        virtual void RemoveEdge(std::shared_ptr<Edge<Type>> E);

        virtual void RemoveVertex(std::shared_ptr<Vertex<Type>> V);

        int NumberVertices() const {return VQueue.Size();};

        int NumberEdges() const {return EQueue.Size();};

        void Delete();

        void CreateFutureMovesTree(std::shared_ptr<Vertex<Type>> V1, int i);

        int Min(std::shared_ptr<Vertex<Type>> V, int *alpha, int *beta);

        int Max(std::shared_ptr<Vertex<Type>> V, int *alpha, int *beta);

        int Minimax(std::shared_ptr<Vertex<Type>> V, int* alpha, int* beta);

        Type GetMaxMove(std::shared_ptr<Vertex<Type>> V);

        friend std::ostream &operator << (std::ostream &out, Graph<Type> &graph);
};



template<typename Type>
Graph<Type>::Graph(){

    VQueue = Dequeue<std::shared_ptr<Vertex<Type>>>();
    EQueue = Dequeue<std::shared_ptr<Edge<Type>>>();
}

template<typename Type>
Graph<Type>::Graph(const Graph<Type> &G){

    Node<std::shared_ptr<Vertex<Type>>> *ptr_v = G.VQueue.GetHead();
    while(ptr_v != NULL){
        Vertex<Type> tmp_v = *ptr_v->GetElem();
        VQueue.InsertEnd(std::make_shared<Vertex<Type>>(tmp_v));
        ptr_v = ptr_v->GetNext();
    }

    Node<std::shared_ptr<Edge<Type>>> *ptr_e = G.EQueue.GetHead();
    while(ptr_e != NULL){
        Edge<Type> tmp_e = *ptr_e->GetElem();
        EQueue.InsertEnd(std::make_shared<Edge<Type>>(tmp_e));
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
std::shared_ptr<Vertex<Type>> Graph<Type>::InsertVertex(Type x){

    auto V = std::make_shared<Vertex<Type>>(x);

    VQueue.InsertFront(V);
    VQueue.GetHead()->GetElem()->SetPos(VQueue.GetHead());
    return V;    
}


template<typename Type>
std::shared_ptr<Edge<Type>> Graph<Type>::InsertEdge(int x, std::shared_ptr<Vertex<Type>> start, std::shared_ptr<Vertex<Type>> end){

    auto E = std::make_shared<Edge<Type>>(x,start,end);

    EQueue.InsertFront(E);
    EQueue.GetHead()->GetElem()->SetPos(EQueue.GetHead());
    return E;
}


template<typename Type>
Dequeue<std::shared_ptr<Edge<Type>>> Graph<Type>::StartingEdges(std::shared_ptr<Vertex<Type>> V) const{

    Dequeue<std::shared_ptr<Edge<Type>>> dequeue;
    
    Node<std::shared_ptr<Edge<Type>>> *ptr = EQueue.GetHead();
    while(ptr != NULL){
        if (*ptr->GetElem()->GetStart() == *V){
            dequeue.InsertFront(ptr->GetElem());
        }
        ptr = ptr->GetNext();
    }
    return dequeue;
}


template<typename Type>
Dequeue<std::shared_ptr<Edge<Type>>> Graph<Type>::IncidentEdges(std::shared_ptr<Vertex<Type>> V) const{

    Dequeue<std::shared_ptr<Edge<Type>>> dequeue;
    
    Node<std::shared_ptr<Edge<Type>>> *ptr = EQueue.GetHead();
    while(ptr != NULL){
        if (*ptr->GetElem()->GetStart() == *V || *ptr->GetElem()->GetEnd() == *V){
            dequeue.InsertFront(ptr->GetElem());
        }
        ptr = ptr->GetNext();
    }
    return dequeue;    
}


template<typename Type>
Dequeue<std::shared_ptr<Vertex<Type>>> Graph<Type>::AdjacentVertices(std::shared_ptr<Vertex<Type>> V) const{

    Dequeue<std::shared_ptr<Edge<Type>>> incident = StartingEdges(V);
    Dequeue<std::shared_ptr<Vertex<Type>>> adjacent;

    while(!incident.IsEmpty()){
        adjacent.InsertFront(incident.RemoveFirst()->GetEnd());
    }
    return adjacent;
}

template<typename Type>
bool Graph<Type>::AreAdjacent(std::shared_ptr<Vertex<Type>> V1, std::shared_ptr<Vertex<Type>> V2) const {

    Node<std::shared_ptr<Edge<Type>>>* ptr = EQueue.GetHead();

    while(ptr != NULL){
        if(ptr->GetElem()->GetStart() == V1 && ptr->GetElem()->GetEnd() == V2) return true;
        ptr = ptr->GetNext();
    }
    return false;
}

template<typename Type>
void Graph<Type>::RemoveEdge(std::shared_ptr<Edge<Type>> E){

    Node<std::shared_ptr<Edge<Type>>>* ptr = E->GetPos();

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
void Graph<Type>::RemoveVertex(std::shared_ptr<Vertex<Type>> V){

   Node<std::shared_ptr<Edge<Type>>>* ptr_e = IncidentEdges(V).GetHead();

    while(ptr_e != NULL){
        RemoveEdge(ptr_e->GetElem());
        ptr_e = ptr_e->GetNext();
    }

    Node<std::shared_ptr<Vertex<Type>>>* ptr_v = V->GetPos();

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




