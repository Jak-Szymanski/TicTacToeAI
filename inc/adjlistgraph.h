#pragma once

#include "adjlistedge.h"

/*Graf zawierający elementy typu Type opisany poprzez listę sąsiedztwa
  Jest on rozszerzeniem grafu opisanego przez samą listy krawędzi i wierzchołków*/
template<typename Type>
class AdjacencyListGraph: public Graph<Type>{

    private:

        /*Lista sąsiedztwa (zawiera listy sąsiadujących krawędzi dla każdego z wierzchołków)*/
        Dequeue<Dequeue<Edge<Type>*>> AdjacencyList;

    public:

        AdjacencyListGraph();

        //AdjacencyListGraph(const Graph G);

        friend std::ostream &operator << (std::ostream &out, AdjacencyListGraph<Type> const &graph);

        //Dequeue<Dequeue<AdjacencyListEdge*>> GetAdjacencyList() const {return AdjacencyList;};

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

        /*Wyczyść cały graf*/
        void Delete();

                                                    //Napisać remove vertex!!!


};

template<typename Type>
AdjacencyListGraph<Type>::AdjacencyListGraph(){
    
    *Vertices() = Dequeue<Vertex<Type>*>();
    *Edges() = Dequeue<Edge<Type>*>();
    AdjacencyList = Dequeue<Dequeue<Edge<Type>*>>();
}

template<typename Type>
std::ostream &operator << (std::ostream &out, AdjacencyListGraph<Type> const &graph){

    if(graph.AdjacencyList.IsEmpty()){
        out << "Lista sasiedztwa jest pusta!" << std::endl;
        return out;
    }

    Node<Dequeue<Edge<Type>*>> *ptr = graph.AdjacencyList.GetHead();

    while(ptr != NULL){
        out << "Sasiedztwo wierzcholka:" << std::endl;
        out << &(ptr->GetElem()) << std::endl;

        ptr = ptr->GetNext();
    }
    return out;
}


/* AdjacencyListGraph::AdjacencyListGraph(const Graph G){

    Graph copyG(G);
    Dequeue<Vertex>> tmp_vertices = *copyG.Vertices();
    Dequeue<Edge> tmp_incident;
    Dequeue<Edge>> tmp_adj;
    Edge tmp_edge;
    Vertex> tmp_vertex;

    while(!tmp_vertices.IsEmpty()){
        tmp_vertex = tmp_vertices.RemoveFirst();
        tmp_incident = copyG.IncidentEdges(tmp_vertex);
        while(!tmp_incident.IsEmpty()){
            tmp_edge = tmp_incident.RemoveFirst();
            Edge> tmp_adjedge = std::dynamic_pointer_cast<Edge>(std::make_shared<AdjacencyListEdge>(tmp_edge));
            tmp_adj.InsertEnd(tmp_adjedge);
        }
        Vertices()->InsertEnd(std::dynamic_pointer_cast<Vertex>(std::make_shared<AdjacencyListVertex>(*tmp_vertex)));        //uwaga zmieniłem
        if(!tmp_adj.IsEmpty()) AdjacencyList.InsertEnd(tmp_adj);
    }


    Dequeue<Edge>> tmp_edges = *copyG.Edges();
    Edge> tmp_edgeptr;
   // AdjacencyListEdge tmp_adjedge;
    while(!tmp_edges.IsEmpty()){
        tmp_edgeptr = tmp_edges.RemoveFirst();
        tmp_adjedge = AdjacencyListEdge(*tmp_edgeptr);
        tmp_adj = *tmp_adjedge.GetStart().GetAdjListPos();
        Node<Edge>>* ptr = tmp_adj.GetHead();
        while(ptr != NULL){
            if(ptr->GetElem())
        }
       

        tmp_edgeptr = std::dynamic_pointer_cast<Edge>(std::make_shared<AdjacencyListEdge>(*tmp_edges.RemoveFirst()));
        Edges()->InsertEnd(tmp_edgeptr);
    }
} */

template<typename Type>
Dequeue<Edge<Type>*> AdjacencyListGraph<Type>::StartingEdges(Vertex<Type>* V) const{
    
    Dequeue<Edge<Type>*> starting;
    Node<Edge<Type>*>* ptr = V->GetAdjList()->GetHead();

    while(ptr != NULL){
        if(ptr->GetElem()->GetEnd() != V) starting.InsertEnd(ptr->GetElem());
        ptr = ptr->GetNext();
    }
    return starting;
}


template<typename Type>
Dequeue<Edge<Type>*> AdjacencyListGraph<Type>::IncidentEdges(Vertex<Type>* V) const{

    return *V->GetAdjList();
}


template<typename Type>
Dequeue<Vertex<Type>*> AdjacencyListGraph<Type>::AdjacentVertices(Vertex<Type>* V) const {
    
    Dequeue<Vertex<Type>*> tmp_adjacent;
    Node<Edge<Type>*>* ptr = V->GetAdjList()->GetHead();

    while(ptr != NULL){
        if(ptr->GetElem()->GetEnd() != V) tmp_adjacent.InsertEnd(ptr->GetElem()->GetEnd());
        ptr = ptr->GetNext();
    }
    return tmp_adjacent;
}


template<typename Type>
Vertex<Type>* AdjacencyListGraph<Type>::InsertVertex(Type x){

    auto V = new AdjacencyListVertex<Type>(x);
    Dequeue<Edge<Type>*>* tmp_adjlist = new Dequeue<Edge<Type>*>();

    
    AdjacencyList.InsertEnd(*tmp_adjlist);
    V->SetAdjList(tmp_adjlist);
   // std::cout << "vertex: " << tmp_adjlist << std::endl;

    Vertices()->InsertFront(V);
    Vertices()->GetHead()->GetElem()->SetPos(Vertices()->GetHead());
    return V;   
}


template<typename Type>
Edge<Type>* AdjacencyListGraph<Type>::InsertEdge(int x, Vertex<Type>* start, Vertex<Type>* end){

    auto E = new AdjacencyListEdge<Type>(x,start,end);

        Edges()->InsertFront(E);
    Edges()->GetHead()->GetElem()->SetPos(Edges()->GetHead());

    //std::cout << "edge: "<< start->GetAdjList() << std::endl << std::endl;

    start->GetAdjList()->InsertEnd(E);

    // std::cout << "po: "<< start->GetAdjList() << std::endl;
    E->SetAdjListStart(start->GetAdjList()->GetTail());

    end->GetAdjList()->InsertEnd(E);
    E->SetAdjListEnd(end->GetAdjList()->GetTail());



    return E;
}


template<typename Type>
bool AdjacencyListGraph<Type>::AreAdjacent(Vertex<Type>* V1, Vertex<Type>* V2) const{

    Node<Edge<Type>*>* ptr = V1->GetAdjList()->GetHead();

    while(ptr != NULL){
        if (ptr->GetElem()->GetEnd() == V2) return true;
        ptr = ptr->GetNext();
    }
    return false;
}


template<typename Type>
void AdjacencyListGraph<Type>::RemoveEdge(Edge<Type>* E){

    Node<Edge<Type>*>* ptr = E->GetPos();

    if(ptr == Edges()->GetHead()){
        Edges()->RemoveFirst();
    } else if (ptr == Edges()->GetTail()){
        Edges()->RemoveLast();
    } else {
    ptr->GetPrev()->SetNext(ptr->GetNext());
    ptr->GetNext()->SetPrev(ptr->GetPrev());
    }

    ptr = E->GetAdjListStart();
    if(ptr->GetNext() != NULL){
        ptr->GetNext()->SetPrev(ptr->GetPrev());   
    }
    if(ptr->GetPrev() != NULL){
        ptr->GetPrev()->SetNext(ptr->GetNext());
    }
   // E->Delete();
}



template<typename Type>
void AdjacencyListGraph<Type>::Delete(){

    Vertices()->Delete();
    Edges()->Delete();
    //AdjacencyList.Delete();
    Node<Dequeue<Edge<Type>*>>* ptr = AdjacencyList.GetHead();
    Node<Dequeue<Edge<Type>*>>* next;
    //free(AdjacencyList.GetHead());
    //free(AdjacencyList.GetTail());

     while(ptr != NULL){
        next = ptr->GetNext();
        ptr->GetElem().Delete();
        ptr = next;
    }
}
