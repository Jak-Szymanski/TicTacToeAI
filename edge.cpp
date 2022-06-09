#include "./inc/edge.h"

std::ostream &operator << (std::ostream &out, Edge const &edge){
    out << "Poczatek: " << std::endl;
    out << edge.GetStart() << std::endl;
    out << "Koniec: " << std::endl;
    out << edge.GetEnd() << std::endl;
    out << "Obiekt: " << std::endl;
    out << edge.GetObject() << std::endl;
    return out;
}



Edge::Edge(){

    Object = 0;
    Start = NULL;
    End = NULL;
    Pos = NULL;
}


Edge::Edge(int x, Vertex* new_start, Vertex* new_end){

    Object = x;
    Start = new_start;
    End = new_end;
    Pos = NULL;
}