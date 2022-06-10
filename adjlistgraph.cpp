#include "./inc/adjlistgraph.h"
//#include "./inc/dequeueptr.h"

std::ostream &operator << (std::ostream &out, AdjacencyListGraph const &graph){

    Node<Dequeue<std::shared_ptr<Edge>>> *ptr = graph.AdjacencyList.GetHead();

    while(ptr != NULL){
        out << "Sasiedztwo wierzcholka:" << std::endl;
        out << ptr->GetElem() << std::endl;

        ptr = ptr->GetNext();
    }
    return out;
}


AdjacencyListGraph::AdjacencyListGraph(const Graph G){

    Graph copyG(G);
    Dequeue<std::shared_ptr<Vertex>> tmp_vertices = copyG.Vertices();
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
            Vertices().InsertEnd(std::dynamic_pointer_cast<Vertex>(std::make_shared<AdjacencyListVertex>(*tmp_vertex)));
        }
        if(!tmp_adj.IsEmpty()) AdjacencyList.InsertEnd(tmp_adj);
    }


    Dequeue<std::shared_ptr<Edge>> tmp_edges = copyG.Edges();
    std::shared_ptr<Edge> tmp_edgeptr;
   // AdjacencyListEdge tmp_adjedge;
    while(!tmp_edges.IsEmpty()){
/*         tmp_edgeptr = tmp_edges.RemoveFirst();
        tmp_adjedge = AdjacencyListEdge(*tmp_edgeptr);
        tmp_adj = *tmp_adjedge.GetStart().GetAdjListPos();
        Node<std::shared_ptr<Edge>>* ptr = tmp_adj.GetHead();
        while(ptr != NULL){
            if(ptr->GetElem())
        }
        */

        tmp_edgeptr = std::dynamic_pointer_cast<Edge>(std::make_shared<AdjacencyListEdge>(*tmp_edges.RemoveFirst()));
        Edges().InsertEnd(tmp_edgeptr);
    }
}