#include "./inc/adjlistgraph.h"

/* AdjacencyListGraph::AdjacencyListGraph(){

} */

AdjacencyListGraph::AdjacencyListGraph(Graph G){

    Dequeue<Vertex> tmp_vertices = G.Vertices();
    Dequeue<Edge> tmp_incident;
    Dequeue<AdjacencyListEdge*> tmp_adj;
    Edge tmp_edge;
    Vertex tmp_vertex;

    while(!tmp_vertices.IsEmpty()){
        tmp_vertex = tmp_vertices.RemoveFirst();
        tmp_incident = G.IncidentEdges(&tmp_vertex);
        while(!tmp_incident.IsEmpty()){
            tmp_edge = tmp_incident.RemoveFirst();
            AdjacencyListEdge *tmp_adjedge = new AdjacencyListEdge(tmp_edge);
            tmp_adj.InsertEnd(tmp_adjedge);
            VQueue.InsertEnd(AdjacencyListVertex(tmp_vertex));
        }
        AdjacencyList.InsertEnd(tmp_adj);
    }


/*     Dequeue<Vertex> Vertices = G.Vertices();
    while(!tmp_vertices.IsEmpty()){
        VQueue.InsertEnd(AdjacencyListVertex(tmp_vertices.RemoveFirst()));
    } */

    Dequeue<Edge> tmp_edges = G.Edges();
    while(!tmp_edges.IsEmpty()){
        EQueue.InsertEnd(AdjacencyListEdge(tmp_edges.RemoveFirst()));
    }
}