#pragma once

#include "graph.h"
#include "adjmatrixvertex.h"

/*Graf zawierający elementy typu Type opisany poprzez macierz sąsiedztwa
  Jest on rozszerzeniem grafu opisanego przez samą listy krawędzi i wierzchołków*/
template<typename Type>
class AdjacencyMatrixGraph: public Graph<Type>{

    private:

        /*Macierz sąsiedztwa - zawiera wskaźniki na krawędź w polu opisanym przez indeksy przylegąjacych do niej wierzchołków*/
        std::vector<std::vector<Edge<Type>*>> AdjacencyMatrix;

    public:

       // AdjacencyMatrixGraph(const Graph G);

        friend std::ostream &operator << (std::ostream &out, AdjacencyMatrixGraph<Type> const &graph);

        /*Wstaw nowy wierzchołek zawierający element x, i zwróć wskaźnik na niego*/
        Vertex<Type>* InsertVertex(Type x);

        /*Wstaw nową krawędź zawierająca element x i mająca dane wierzchołki końcowe, i zwróć wskaźnik na nią*/
        Edge<Type>* InsertEdge(int x, Vertex<Type>* start, Vertex<Type>* end);

        /*Zwróć krawędzie przylegające do danego wierzchołka*/
        Dequeue<Edge<Type>*> IncidentEdges(Vertex<Type>* V) const;

        /*Zwróć krawędzie zaczynające się z danego wierzchołka*/
        Dequeue<Edge<Type>*> StartingEdges(Vertex<Type>* V) const;

        /*Zwróć wierzchołki sąsiadujące z danym wierzchołkiem*/
        Dequeue<Vertex<Type>*> AdjacentVertices(Vertex<Type>* V) const;

        /*Czy dane wierzchołki ze sobą sąsiadują*/
        bool AreAdjacent(Vertex<Type>* V1, Vertex<Type>* V2) const;

        /*Usuń daną krawędź*/
        void RemoveEdge(Edge<Type>* E);

        /*Usuń dany wierzchołek*/
        void RemoveVertex(Vertex<Type>* V);

        /*Wyczyść cały graf*/
        void Delete();

};

template<typename Type>
Vertex<Type>* AdjacencyMatrixGraph<Type>::InsertVertex(Type x){

    auto V = new AdjacencyMatrixVertex<Type>(x);

    int new_size = NumberVertices() + 1;
    V->SetIndex(new_size-1);
    AdjacencyMatrix.resize(new_size, std::vector<Edge<Type>*>(new_size, NULL));
    for (auto &row: AdjacencyMatrix) row.resize(new_size, NULL);
    Vertices()->InsertFront(V);
    Vertices()->GetHead()->GetElem()->SetPos(Vertices()->GetHead());
    return V;

}


template<typename Type>
Edge<Type>* AdjacencyMatrixGraph<Type>::InsertEdge(int x, Vertex<Type>* start, Vertex<Type>* end){
    
    auto E = new Edge<Type>(x,start,end);

    Edges()->InsertFront(E);
    Edges()->GetHead()->GetElem()->SetPos(Edges()->GetHead());
    int i = start->GetIndex();
    int j = end->GetIndex();
    AdjacencyMatrix[i][j] = E;
    // AdjacencyMatrix[j][i] = E;
    return E;
}


template<typename Type>
Dequeue<Edge<Type>*> AdjacencyMatrixGraph<Type>::StartingEdges(Vertex<Type>* V) const {

    int j = V->GetIndex();
    Dequeue<Edge<Type>*> tmp_incident;
    int size = NumberVertices();
    for(int i=0; i<size; i++){
        if(AdjacencyMatrix[j][i] != NULL) tmp_incident.InsertEnd(AdjacencyMatrix[j][i]);
    }
    return tmp_incident;
}


template<typename Type>
 Dequeue<Edge<Type>*> AdjacencyMatrixGraph<Type>::IncidentEdges(Vertex<Type>* V) const {

    int j = V->GetIndex();
    Dequeue<Edge<Type>*> tmp_incident;
    int size = NumberVertices();
    for(int i=0; i<size; i++){
        if(AdjacencyMatrix[j][i] != NULL) tmp_incident.InsertEnd(AdjacencyMatrix[j][i]);
        if(AdjacencyMatrix[i][j] != NULL) tmp_incident.InsertEnd(AdjacencyMatrix[i][j]);
    }
    return tmp_incident; 
 }


template<typename Type>
Dequeue<Vertex<Type>*> AdjacencyMatrixGraph<Type>::AdjacentVertices(Vertex<Type>* V) const {

    int j = V->GetIndex();
    Dequeue<Vertex<Type>*> tmp_adjacent;
    int size = NumberVertices();
    for(int i=0; i<size; i++){
        if(AdjacencyMatrix[j][i] != NULL) tmp_adjacent.InsertEnd(AdjacencyMatrix[j][i]->GetEnd());
    }
    return tmp_adjacent;

}


template<typename Type>
bool AdjacencyMatrixGraph<Type>::AreAdjacent(Vertex<Type>* V1, Vertex<Type>* V2) const{

    return AdjacencyMatrix[V1->GetIndex()][V2->GetIndex()] != NULL;
}


template<typename Type>
void AdjacencyMatrixGraph<Type>::RemoveEdge(Edge<Type>* E){

    AdjacencyMatrix[E->GetStart()->GetIndex()][E->GetEnd()->GetIndex()] = NULL;

    Node<Edge<Type>*>* ptr = E->GetPos();

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
void AdjacencyMatrixGraph<Type>::RemoveVertex(Vertex<Type>* V){

   Node<Edge<Type>*>* ptr_e = IncidentEdges(V).GetHead();

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


    Node<Vertex<Type>*>* ptr_v = V->GetPos();

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

    Node<Vertex<Type>*>* next = ptr_v->GetNext();

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

template<typename Type>
void AdjacencyMatrixGraph<Type>::Delete(){

    VQueue.Delete();
    EQueue.Delete();
    AdjacencyMatrix.clear();
    AdjacencyMatrix.resize(0); 
}