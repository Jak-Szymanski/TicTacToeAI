#include "./inc/adjlistedge.h"

AdjacencyListEdge::AdjacencyListEdge(){

    SetObject(0);
    SetPos(NULL);
    SetStart(NULL);
    SetEnd(NULL);
    AdjListStart = NULL;
    AdjListEnd = NULL;
}

AdjacencyListEdge::AdjacencyListEdge(Edge E){

    SetObject(E.GetObject());
    SetPos(E.GetPos());
    SetStart(std::make_shared<Vertex>(E.GetStart()));
    SetEnd(std::make_shared<Vertex>(E.GetEnd()));
    AdjListStart = NULL;
    AdjListEnd = NULL;
}