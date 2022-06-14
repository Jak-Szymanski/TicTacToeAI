#pragma once

#include "adjlistedge.h"


template<typename Type>
class AdjacencyListGraph: public Graph<Type>{

    private:

        Dequeue<Dequeue<std::shared_ptr<Edge<Type>>>> AdjacencyList;

    public:

        AdjacencyListGraph();

        //AdjacencyListGraph(const Graph G);

        friend std::ostream &operator << (std::ostream &out, AdjacencyListGraph<Type> const &graph);

        //Dequeue<Dequeue<AdjacencyListEdge*>> GetAdjacencyList() const {return AdjacencyList;};

        std::shared_ptr<Vertex<Type>> InsertVertex(Type x);

        std::shared_ptr<Edge<Type>> InsertEdge(int x, std::shared_ptr<Vertex<Type>> start, std::shared_ptr<Vertex<Type>> end);

        Dequeue<std::shared_ptr<Edge<Type>>> StartingEdges(std::shared_ptr<Vertex<Type>> V) const;

        Dequeue<std::shared_ptr<Edge<Type>>> IncidentEdges(std::shared_ptr<Vertex<Type>> V) const;

        Dequeue<std::shared_ptr<Vertex<Type>>> AdjacentVertices(std::shared_ptr<Vertex<Type>> V) const;

        bool AreAdjacent(std::shared_ptr<Vertex<Type>> V1, std::shared_ptr<Vertex<Type>> V2) const;

        void RemoveEdge(std::shared_ptr<Edge<Type>> E);

};

template<typename Type>
AdjacencyListGraph<Type>::AdjacencyListGraph(){
    
    *Vertices() = Dequeue<std::shared_ptr<Vertex<Type>>>();
    *Edges() = Dequeue<std::shared_ptr<Edge<Type>>>();
    AdjacencyList = Dequeue<Dequeue<std::shared_ptr<Edge<Type>>>>();
}

template<typename Type>
std::ostream &operator << (std::ostream &out, AdjacencyListGraph<Type> const &graph){

    if(graph.AdjacencyList.IsEmpty()){
        out << "Lista sasiedztwa jest pusta!" << std::endl;
        return out;
    }

    Node<Dequeue<std::shared_ptr<Edge<Type>>>> *ptr = graph.AdjacencyList.GetHead();

    while(ptr != NULL){
        out << "Sasiedztwo wierzcholka:" << std::endl;
        out << &(ptr->GetElem()) << std::endl;

        ptr = ptr->GetNext();
    }
    return out;
}


/* AdjacencyListGraph::AdjacencyListGraph(const Graph G){

    Graph copyG(G);
    Dequeue<std::shared_ptr<Vertex>> tmp_vertices = *copyG.Vertices();
    Dequeue<Edge> tmp_incident;
    Dequeue<std::shared_ptr<Edge>> tmp_adj;
    Edge tmp_edge;
    std::shared_ptr<Vertex> tmp_vertex;

    while(!tmp_vertices.IsEmpty()){
        tmp_vertex = tmp_vertices.RemoveFirst();
        tmp_incident = copyG.IncidentEdges(tmp_vertex);
        while(!tmp_incident.IsEmpty()){
            tmp_edge = tmp_incident.RemoveFirst();
            std::shared_ptr<Edge> tmp_adjedge = std::dynamic_pointer_cast<Edge>(std::make_shared<AdjacencyListEdge>(tmp_edge));
            tmp_adj.InsertEnd(tmp_adjedge);
        }
        Vertices()->InsertEnd(std::dynamic_pointer_cast<Vertex>(std::make_shared<AdjacencyListVertex>(*tmp_vertex)));        //uwaga zmieniłem
        if(!tmp_adj.IsEmpty()) AdjacencyList.InsertEnd(tmp_adj);
    }


    Dequeue<std::shared_ptr<Edge>> tmp_edges = *copyG.Edges();
    std::shared_ptr<Edge> tmp_edgeptr;
   // AdjacencyListEdge tmp_adjedge;
    while(!tmp_edges.IsEmpty()){
        tmp_edgeptr = tmp_edges.RemoveFirst();
        tmp_adjedge = AdjacencyListEdge(*tmp_edgeptr);
        tmp_adj = *tmp_adjedge.GetStart().GetAdjListPos();
        Node<std::shared_ptr<Edge>>* ptr = tmp_adj.GetHead();
        while(ptr != NULL){
            if(ptr->GetElem())
        }
       

        tmp_edgeptr = std::dynamic_pointer_cast<Edge>(std::make_shared<AdjacencyListEdge>(*tmp_edges.RemoveFirst()));
        Edges()->InsertEnd(tmp_edgeptr);
    }
} */

template<typename Type>
Dequeue<std::shared_ptr<Edge<Type>>> AdjacencyListGraph<Type>::StartingEdges(std::shared_ptr<Vertex<Type>> V) const{
    
    Dequeue<std::shared_ptr<Edge<Type>>> starting;
    Node<std::shared_ptr<Edge<Type>>>* ptr = V->GetAdjList()->GetHead();

    while(ptr != NULL){
        if(ptr->GetElem()->GetEnd() != V) starting.InsertEnd(ptr->GetElem());
        ptr = ptr->GetNext();
    }
    return starting;
}


template<typename Type>
Dequeue<std::shared_ptr<Edge<Type>>> AdjacencyListGraph<Type>::IncidentEdges(std::shared_ptr<Vertex<Type>> V) const{

    return *V->GetAdjList();
}


template<typename Type>
Dequeue<std::shared_ptr<Vertex<Type>>> AdjacencyListGraph<Type>::AdjacentVertices(std::shared_ptr<Vertex<Type>> V) const {
    
    Dequeue<std::shared_ptr<Vertex<Type>>> tmp_adjacent;
    Node<std::shared_ptr<Edge<Type>>>* ptr = V->GetAdjList()->GetHead();

    while(ptr != NULL){
        if(ptr->GetElem()->GetEnd() != V) tmp_adjacent.InsertEnd(ptr->GetElem()->GetEnd());
        ptr = ptr->GetNext();
    }
    return tmp_adjacent;
}


template<typename Type>
std::shared_ptr<Vertex<Type>> AdjacencyListGraph<Type>::InsertVertex(Type x){

    auto V = std::make_shared<AdjacencyListVertex<Type>>(x);
    Dequeue<std::shared_ptr<Edge<Type>>>* tmp_adjlist = new Dequeue<std::shared_ptr<Edge<Type>>>();

    
    AdjacencyList.InsertEnd(*tmp_adjlist);
    V->SetAdjList(tmp_adjlist);
    std::cout << "vertex: " << tmp_adjlist << std::endl;

    Vertices()->InsertFront(V);
    Vertices()->GetHead()->GetElem()->SetPos(Vertices()->GetHead());
    return V;   
}


template<typename Type>
std::shared_ptr<Edge<Type>> AdjacencyListGraph<Type>::InsertEdge(int x, std::shared_ptr<Vertex<Type>> start, std::shared_ptr<Vertex<Type>> end){

    auto E = std::make_shared<AdjacencyListEdge<Type>>(x,start,end);

        Edges()->InsertFront(E);
    Edges()->GetHead()->GetElem()->SetPos(Edges()->GetHead());

    std::cout << "edge: "<< start->GetAdjList() << std::endl << std::endl;

    start->GetAdjList()->InsertEnd(E);

    // std::cout << "po: "<< start->GetAdjList() << std::endl;
    E->SetAdjListStart(start->GetAdjList()->GetTail());

    end->GetAdjList()->InsertEnd(E);
    E->SetAdjListEnd(end->GetAdjList()->GetTail());



    return E;
}


template<typename Type>
bool AdjacencyListGraph<Type>::AreAdjacent(std::shared_ptr<Vertex<Type>> V1, std::shared_ptr<Vertex<Type>> V2) const{

    Node<std::shared_ptr<Edge<Type>>>* ptr = V1->GetAdjList()->GetHead();

    while(ptr != NULL){
        if (ptr->GetElem()->GetEnd() == V2) return true;
        ptr = ptr->GetNext();
    }
    return false;
}


template<typename Type>
void AdjacencyListGraph<Type>::RemoveEdge(std::shared_ptr<Edge<Type>> E){

    Node<std::shared_ptr<Edge<Type>>>* ptr = E->GetPos();

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
    delete ptr;
}

