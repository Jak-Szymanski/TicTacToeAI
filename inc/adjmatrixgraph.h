#pragma once

#include "graph.h"
#include "adjmatrixvertex.h"

/*Graf zawierający elementy typu Type opisany poprzez macierz sąsiedztwa
  Jest on rozszerzeniem grafu opisanego przez samą listy krawędzi i wierzchołków*/
template<typename Type>
class AdjacencyMatrixGraph: public Graph<Type>{

    private:

        /*Macierz sąsiedztwa - zawiera wskaźniki na krawędź w polu opisanym przez indeksy przylegąjacych do niej wierzchołków*/
        // std::vector<std::vector<Edge<Type>*>> AdjacencyMatrix;
        Edge<Type>*** AdjacencyMatrix; 

    public:

       // AdjacencyMatrixGraph();

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
        int size = NumberVertices();

    Edge<Type>*** copy = new Edge<Type>**[size];
    for(int i=0; i < size; i++){
        copy[i] = new Edge<Type>*[size];
    }

    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            copy[i][j] = AdjacencyMatrix[i][j];
            //AdjacencyMatrix[i][j]->Delete();
           // delete AdjacencyMatrix[i][j];
        }
        delete[] AdjacencyMatrix[i];
    }
    delete[] AdjacencyMatrix;

    AdjacencyMatrix = new Edge<Type>**[size+1];
    for(int i=0; i < size+1; i++){
        AdjacencyMatrix[i] = new Edge<Type>*[size+1];
    }

    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            AdjacencyMatrix[i][j] = copy[i][j];
           // copy[i][j]->Delete();
           // delete copy[i][j];
        }
        delete [] copy[i];
    }
    delete[] copy;

    for(int i=0; i<size; i++){
        AdjacencyMatrix[size-1][i] = NULL;
        AdjacencyMatrix[i][size-1] = NULL;
    }

    V->SetIndex(size);
    //AdjacencyMatrix.resize(size+1, std::vector<Edge<Type>*>(new_size+1, NULL));
    //for (auto &row: AdjacencyMatrix) row.resize(new_size, NULL);
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

    std::cout << "incident";
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
    std::cout << "edge" << std::endl;

    std::cout << E->GetStart()->GetIndex();
    std::cout << "   " << E->GetEnd()->GetIndex() << std::endl;
    AdjacencyMatrix[E->GetStart()->GetIndex()][E->GetEnd()->GetIndex()];    
    std::cout << "bruh" << std::endl;     //przetestować to zwalnianie
    
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
    //E->Delete();
    //delete ptr;
}


template<typename Type>
void AdjacencyMatrixGraph<Type>::RemoveVertex(Vertex<Type>* V){

   Node<Edge<Type>*>* ptr_e = IncidentEdges(V).GetHead();
       std::cout << "przedprzed";

    while(ptr_e != NULL){
        RemoveEdge(ptr_e->GetElem());
        ptr_e = ptr_e->GetNext();
    }

    std::cout << "po";


    int index = V->GetIndex();
    int size = NumberVertices();
    

    Edge<Type>*** copy = new Edge<Type>**[size-1];
    for(int i=0; i < size-1; i++){
        copy[i] = new Edge<Type>*[size-1];
    }

    int k = 0;      //iteracja po kopii (bo trzeba usunąć komórki z indeksem wierzchołka)
    int l = 0;

    std::cout << "przed";
    for(int i=0; i<size; i++){
        l = 0;
        if(i==index){
            delete[] AdjacencyMatrix[i];
            continue;
        }
        for(int j=0; j<size; j++){
            if(i != index && j != index){
                copy[k][l] = AdjacencyMatrix[i][j];
                //delete AdjacencyMatrix[i][j];
                l++;
            }
        }
        k++;
        delete[] AdjacencyMatrix[i];
    }
    delete[] AdjacencyMatrix;

    std::cout << "po";
    AdjacencyMatrix = new Edge<Type>**[size-1];
    for(int i=0; i < size-1; i++){
        AdjacencyMatrix[i] = new Edge<Type>*[size-1];
    }

    for(int i=0; i<size-1; i++){
        for(int j=0; j<size-1; j++){
            AdjacencyMatrix[i][j] = copy[i][j];
           // delete copy[i][j];
        }
        delete[] copy[i];
    }
    delete[] copy;

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
    V->Delete();
    //delete ptr_v;
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

    Vertices()->Delete();
    Edges()->Delete();

    int size = NumberVertices();
    for(int i=0; i<size; i++){
        for(int j=0;j<size; j++){
            delete AdjacencyMatrix[i][j];           //zobaczyć czy to coś zmienia
        }
        delete[] AdjacencyMatrix[i];
    }
    delete[] AdjacencyMatrix;

}