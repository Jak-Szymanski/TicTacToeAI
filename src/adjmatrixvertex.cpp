#include "../inc/adjmatrixvertex.h"

AdjacencyMatrixVertex::AdjacencyMatrixVertex(){
    
    SetObject(GameState());
    SetPos(NULL);
    SetIndex(0);
};

AdjacencyMatrixVertex::AdjacencyMatrixVertex(Vertex V){

    SetObject(V.GetObject());
    SetPos(V.GetPos());
    SetIndex(0);
}