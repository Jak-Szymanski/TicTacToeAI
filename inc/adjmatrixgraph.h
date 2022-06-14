#pragma once

#include "graph.h"
#include "adjmatrixvertex.h"

template<typename Type>
class AdjacencyMatrixGraph: public Graph<Type>{

    private:

        std::vector<std::vector<std::shared_ptr<Edge<Type>>>> AdjacencyMatrix;

    public:

       // AdjacencyMatrixGraph(const Graph G);

        friend std::ostream &operator << (std::ostream &out, AdjacencyMatrixGraph<Type> const &graph);

        std::shared_ptr<Vertex<Type>> InsertVertex(Type x);

        std::shared_ptr<Edge<Type>> InsertEdge(int x, std::shared_ptr<Vertex<Type>> start, std::shared_ptr<Vertex<Type>> end);

        Dequeue<std::shared_ptr<Edge<Type>>> StartingEdges(std::shared_ptr<Vertex<Type>> V) const;

        Dequeue<std::shared_ptr<Edge<Type>>> IncidentEdges(std::shared_ptr<Vertex<Type>> V) const;

        Dequeue<std::shared_ptr<Vertex<Type>>> AdjacentVertices(std::shared_ptr<Vertex<Type>> V) const;

        bool AreAdjacent(std::shared_ptr<Vertex<Type>> V1, std::shared_ptr<Vertex<Type>> V2) const;

        void RemoveEdge(std::shared_ptr<Edge<Type>> E);

        void RemoveVertex(std::shared_ptr<Vertex<Type>> V);

};

template<typename Type>
std::shared_ptr<Vertex<Type>> AdjacencyMatrixGraph<Type>::InsertVertex(Type x){

    auto V = std::make_shared<AdjacencyMatrixVertex<Type>>(x);

    int new_size = NumberVertices() + 1;
    V->SetIndex(new_size-1);
    AdjacencyMatrix.resize(new_size, std::vector<std::shared_ptr<Edge<Type>>>(new_size, NULL));
    for (auto &row: AdjacencyMatrix) row.resize(new_size, NULL);
    Vertices()->InsertFront(V);
    Vertices()->GetHead()->GetElem()->SetPos(Vertices()->GetHead());
    return V;

}


template<typename Type>
std::shared_ptr<Edge<Type>> AdjacencyMatrixGraph<Type>::InsertEdge(int x, std::shared_ptr<Vertex<Type>> start, std::shared_ptr<Vertex<Type>> end){
    
    auto E = std::make_shared<Edge<Type>>(x,start,end);

    Edges()->InsertFront(E);
    Edges()->GetHead()->GetElem()->SetPos(Edges()->GetHead());
    int i = start->GetIndex();
    int j = end->GetIndex();
    AdjacencyMatrix[i][j] = E;
    // AdjacencyMatrix[j][i] = E;
    return E;
}


template<typename Type>
Dequeue<std::shared_ptr<Edge<Type>>> AdjacencyMatrixGraph<Type>::StartingEdges(std::shared_ptr<Vertex<Type>> V) const {

    int j = V->GetIndex();
    Dequeue<std::shared_ptr<Edge<Type>>> tmp_incident;
    int size = NumberVertices();
    for(int i=0; i<size; i++){
        if(AdjacencyMatrix[j][i] != NULL) tmp_incident.InsertEnd(AdjacencyMatrix[j][i]);
    }
    return tmp_incident;
}


template<typename Type>
 Dequeue<std::shared_ptr<Edge<Type>>> AdjacencyMatrixGraph<Type>::IncidentEdges(std::shared_ptr<Vertex<Type>> V) const {

    int j = V->GetIndex();
    Dequeue<std::shared_ptr<Edge<Type>>> tmp_incident;
    int size = NumberVertices();
    for(int i=0; i<size; i++){
        if(AdjacencyMatrix[j][i] != NULL) tmp_incident.InsertEnd(AdjacencyMatrix[j][i]);
        if(AdjacencyMatrix[i][j] != NULL) tmp_incident.InsertEnd(AdjacencyMatrix[i][j]);
    }
    return tmp_incident; 
 }


template<typename Type>
Dequeue<std::shared_ptr<Vertex<Type>>> AdjacencyMatrixGraph<Type>::AdjacentVertices(std::shared_ptr<Vertex<Type>> V) const {

    int j = V->GetIndex();
    Dequeue<std::shared_ptr<Vertex<Type>>> tmp_adjacent;
    int size = NumberVertices();
    for(int i=0; i<size; i++){
        if(AdjacencyMatrix[j][i] != NULL) tmp_adjacent.InsertEnd(AdjacencyMatrix[j][i]->GetEnd());
    }
    return tmp_adjacent;

}


template<typename Type>
bool AdjacencyMatrixGraph<Type>::AreAdjacent(std::shared_ptr<Vertex<Type>> V1, std::shared_ptr<Vertex<Type>> V2) const{

    return AdjacencyMatrix[V1->GetIndex()][V2->GetIndex()] != NULL;
}


template<typename Type>
void AdjacencyMatrixGraph<Type>::RemoveEdge(std::shared_ptr<Edge<Type>> E){

    AdjacencyMatrix[E->GetStart()->GetIndex()][E->GetEnd()->GetIndex()] = NULL;

    Node<std::shared_ptr<Edge<Type>>>* ptr = E->GetPos();

    if(ptr == Edges()->GetHead()){
        Edges()->RemoveFirst();
        return;
    } 
    if(ptr == Edges()->GetTail()){
        Edges()->RemoveLast();
        return;
    }

    ptr->GetPrev()->SetNext(ptr->GetNext());
    ptr->GetNext()->SetPrev(ptr->GetPrev());
    delete ptr;
}


template<typename Type>
void AdjacencyMatrixGraph<Type>::RemoveVertex(std::shared_ptr<Vertex<Type>> V){

   Node<std::shared_ptr<Edge<Type>>>* ptr_e = IncidentEdges(V).GetHead();

    while(ptr_e != NULL){
        RemoveEdge(ptr_e->GetElem());
        ptr_e = ptr_e->GetNext();
    }

    int index = V->GetIndex();
    AdjacencyMatrix.erase(AdjacencyMatrix.begin() + index);

    for(int i=0; i<AdjacencyMatrix.size(); i++){
        if(AdjacencyMatrix[i].size() > index){
            AdjacencyMatrix[i].erase(AdjacencyMatrix[i].begin() + index);
        }
    }


    Node<std::shared_ptr<Vertex<Type>>>* ptr_v = V->GetPos();

    if(ptr_v->GetNext() == NULL){
        Vertices()->SetTail(ptr_v->GetPrev());
    } else{
        ptr_v->GetNext()->SetPrev(ptr_v->GetPrev());   
    }
    if(ptr_v->GetPrev() == NULL){
        Vertices()->SetHead(ptr_v->GetNext());
    } else {
        ptr_v->GetPrev()->SetNext(ptr_v->GetNext());
    }

    Node<std::shared_ptr<Vertex<Type>>>* next = ptr_v->GetNext();

    while(next != NULL){
        next->GetElem()->SetIndex(next->GetElem()->GetIndex() - 1);
        next = next->GetNext();
    }
    delete ptr_v;
}


template<typename Type>
std::ostream &operator << (std::ostream &out, AdjacencyMatrixGraph<Type> const &graph){

    out << "Macierz sasiedztwa: " << std::endl;

    int size = graph.NumberVertices();

    if (size == 0){
        out << "Macierz jest pusta" << std::endl;
        return out;
    }
    std::cout << "rozmiar " << size << std::endl;
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            out << i << ", " << j << std::endl;
            if (graph.AdjacencyMatrix[i][j] == NULL){
                out << "Brak krawedzi" << std::endl;
            } else {
                out << *graph.AdjacencyMatrix[i][j] << std::endl;
            }
        }
    }
    return out;
}