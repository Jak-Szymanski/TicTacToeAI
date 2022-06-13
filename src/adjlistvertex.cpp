#include "../inc/adjlistvertex.h"

AdjacencyListVertex::AdjacencyListVertex(){

    SetObject(GameState());
    SetPos(NULL);
    AdjList = NULL;

}

AdjacencyListVertex::AdjacencyListVertex(Vertex V){

    SetObject(V.GetObject());
    SetPos(V.GetPos());
    AdjList = NULL;

}