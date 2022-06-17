#include "../inc/edge.h"

std::ostream &operator << (std::ostream &out, Edge const &edge){
    out << "Poczatek: " << std::endl;
    out << edge.GetStart() << std::endl;
    out << "Koniec: " << std::endl;
    out << edge.GetEnd() << std::endl;
    return out;
}



Edge::Edge(){

    Start = NULL;
    End = NULL;
    Pos = NULL;
}


Edge::Edge(Vertex* new_start, Vertex* new_end){

    Start = new_start;
    End = new_end;
    Pos = NULL;
}
