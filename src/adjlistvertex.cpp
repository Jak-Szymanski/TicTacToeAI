#include "../inc/adjlistvertex.h"

AdjacencyListVertex::AdjacencyListVertex(){

    SetObject(GameState());
    SetPos(NULL);
    AdjListPos = NULL;

}

AdjacencyListVertex::AdjacencyListVertex(Vertex V){

    SetObject(V.GetObject());
    SetPos(V.GetPos());
    AdjListPos = NULL;

}