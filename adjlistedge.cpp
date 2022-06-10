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
    SetStart(&E.GetStart());
    SetEnd(&E.GetEnd());
    AdjListStart = NULL;
    AdjListEnd = NULL;
}