#pragma once

#include "dequeueptr.h"

#define SEARCH_DEPTH 3


/*Graf zawierający elementy typu Type opisany poprzez listę krawędzi i listę wierzchołków*/
template<typename Type>
class Graph{

    private:

        /*Lista wierzchołków*/
        Dequeue<Vertex<Type>*> VQueue;

        /*Lista krawędzi*/
        Dequeue<Edge<Type>*> EQueue;

    public:

        Graph();

        Graph(const Graph<Type> &G);

        Dequeue<Vertex<Type>*>* Vertices(){return &VQueue;};

        Dequeue<Edge<Type>*>* Edges(){return &EQueue;};

        /*Wstaw nowy wierzchołek zawierający element x, i zwróć wskaźnik na niego*/
        virtual Vertex<Type>* InsertVertex(Type x);

        /*Wstaw nową krawędź zawierająca element x i mająca dane wierzchołki końcowe, i zwróć wskaźnik na nią*/
        virtual Edge<Type>* InsertEdge(int x, Vertex<Type>* start, Vertex<Type>* end);

        /*Zwróć krawędzie przylegające do danego wierzchołka*/
        virtual Dequeue<Edge<Type>*> IncidentEdges(Vertex<Type>* V) const;

        /*Zwróć krawędzie zaczynające się z danego wierzchołka*/
        virtual Dequeue<Edge<Type>*> StartingEdges(Vertex<Type>* V) const;

        /*Zwróć wierzchołki sąsiadujące z danym wierzchołkiem*/
        virtual Dequeue<Vertex<Type>*> AdjacentVertices(Vertex<Type>* V) const;

        /*Czy dane wierzchołki ze sobą sąsiadują*/
        virtual bool AreAdjacent(Vertex<Type>* V1, Vertex<Type>* V2) const;

        /*Usuń daną krawędź*/
        virtual void RemoveEdge(Edge<Type>* E);

        /*Usuń dany wierzchołek (i wszystkie krawędzie przylegające do niego)*/
        virtual void RemoveVertex(Vertex<Type>* V);

        /*Zwróć liczbę wierzchołków*/
        int NumberVertices() const {return VQueue.Size();};

        /*Zwróć liczbę krawędzi*/
        int NumberEdges() const {return EQueue.Size();};

        /*Wyczyść cały graf*/
        virtual void Delete();

        friend std::ostream &operator << (std::ostream &out, Graph<Type> const &graph);

            /* --- Poniższe metody są opisane tylko dla grafu zawierającego klasę GameState (w pliku src/gamestate.cpp) --- */
        void CreateFutureMovesTree(Vertex<Type>* V1, int i);

        int Min(Vertex<Type>* V, int *alpha, int *beta);

        int Max(Vertex<Type>* V, int *alpha, int *beta);

        int Minimax(Vertex<Type>* V, int* alpha, int* beta);

        Type GetMaxMove(Vertex<Type>* V);




        
};

/* template<typename Type>
std::ostream &operator << (std::ostream &out, Graph<Type> &graph); */


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
    //E->Delete();
  //  delete ptr;
    E->Delete();
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
   //V->Delete();
  //  delete ptr_v;
  //  delete ptr_e;
   V->Delete();
}



template<typename Type>
void Graph<Type>::Delete(){

   // if(std::is_pointer<Type>::value){
/*         VQueue.DeletePtr();
        EQueue.DeletePtr(); */
   // } else {
        VQueue.Delete();
        EQueue.Delete();
    //}
}




