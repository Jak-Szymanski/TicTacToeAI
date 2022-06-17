#include "../inc/vertex.h"

std::ostream &operator << (std::ostream &out, Vertex const &vertex){
    out << vertex.GetObject();
    return out;
}



Vertex::Vertex(){

    Object = GameState();
    Pos = NULL;
}


Vertex::Vertex(GameState x){

    Object = GameState(x);
    Pos = NULL;    
}


bool Vertex::operator== (const Vertex &V) const{

    return (Object == V.GetObject() && Pos == V.GetPos());
}
