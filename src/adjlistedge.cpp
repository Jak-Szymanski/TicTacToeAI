#include "../inc/adjlistedge.h"

AdjacencyListEdge::AdjacencyListEdge(){

    SetObject(0);
    SetPos(NULL);
    SetStart(NULL);
    SetEnd(NULL);
    AdjListStart = NULL;
    AdjListEnd = NULL;
}

AdjacencyListEdge::AdjacencyListEdge(int x, std::shared_ptr<Vertex> new_start, std::shared_ptr<Vertex> new_end){

    SetObject(x);
    SetStart(new_start);
    SetEnd(new_end);
    SetPos(NULL);
    AdjListStart = NULL;
    AdjListEnd = NULL; 
}

AdjacencyListEdge::AdjacencyListEdge(Edge E){

    SetObject(E.GetObject());
    SetPos(E.GetPos());
    SetStart(E.GetStart());
    SetEnd(E.GetEnd());
    AdjListStart = NULL;
    AdjListEnd = NULL;
}