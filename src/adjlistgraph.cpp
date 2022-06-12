#include "../inc/adjlistgraph.h"
//#include "./inc/dequeueptr.h"

AdjacencyListGraph::AdjacencyListGraph(){
    
    *Vertices() = Dequeue<std::shared_ptr<Vertex>>();
    *Edges() = Dequeue<std::shared_ptr<Edge>>();
    AdjacencyList = Dequeue<Dequeue<std::shared_ptr<Edge>>>();
}


std::ostream &operator << (std::ostream &out, AdjacencyListGraph const &graph){

    if(graph.AdjacencyList.IsEmpty()){
        out << "Lista sasiedztwa jest pusta!" << std::endl;
        return out;
    }

    Node<Dequeue<std::shared_ptr<Edge>>> *ptr = graph.AdjacencyList.GetHead();

    while(ptr != NULL){
        out << "Sasiedztwo wierzcholka:" << std::endl;
        out << ptr->GetElem() << std::endl;

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

Dequeue<std::shared_ptr<Edge>> AdjacencyListGraph::IncidentEdges(std::shared_ptr<Vertex> V) const{
    return *V->GetAdjListPos();
}

Dequeue<std::shared_ptr<Vertex>> AdjacencyListGraph::AdjacentVertices(std::shared_ptr<Vertex> V) const {
    
    Dequeue<std::shared_ptr<Vertex>> tmp_adjacent;
    Node<std::shared_ptr<Edge>>* ptr = V->GetAdjListPos()->GetHead();

    while(ptr != NULL){
        tmp_adjacent.InsertEnd(ptr->GetElem()->GetEnd());
        ptr = ptr->GetNext();
    }
    return tmp_adjacent;
}

std::shared_ptr<Vertex> AdjacencyListGraph::InsertVertex(GameState x){

    auto V = std::make_shared<AdjacencyListVertex>(x);
    Dequeue<std::shared_ptr<Edge>>* tmp_adjlist = new Dequeue<std::shared_ptr<Edge>>;

    AdjacencyList.InsertEnd(*tmp_adjlist);
    V->SetAdjListPos(tmp_adjlist);
    Vertices()->InsertFront(V);
    Vertices()->GetHead()->GetElem()->SetPos(Vertices()->GetHead());
    return V;   
}

std::shared_ptr<Edge> AdjacencyListGraph::InsertEdge(int x, std::shared_ptr<Vertex> start, std::shared_ptr<Vertex> end){

    auto E = std::make_shared<AdjacencyListEdge>(x,start,end);

    start->GetAdjListPos()->InsertEnd(E);
    E->SetAdjListStart(start->GetAdjListPos()->GetTail());

    Edges()->InsertFront(E);
    Edges()->GetHead()->GetElem()->SetPos(Edges()->GetHead());

    return E;
}

bool AdjacencyListGraph::AreAdjacent(std::shared_ptr<Vertex> V1, std::shared_ptr<Vertex> V2) const{

    Node<std::shared_ptr<Edge>>* ptr = V1->GetAdjListPos()->GetHead();

    while(ptr != NULL){
        if (ptr->GetElem()->GetEnd() == V2) return true;
        ptr = ptr->GetNext();
    }
    return false;
}

void AdjacencyListGraph::RemoveEdge(std::shared_ptr<Edge> E){

    Node<std::shared_ptr<Edge>>* ptr = E->GetPos();

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