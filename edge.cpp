#include "./inc/edge.h"

std::ostream &operator << (std::ostream &out, Edge const &edge){
    out << "Poczatek: " << std::endl;
    out << *edge.Start << std::endl;
    out << "Koniec: " << std::endl;
    out << *edge.End << std::endl;
    out << "Obiekt: " << std::endl;
    out << edge.Object << std::endl;
    return out;
}



Edge::Edge(){

    Object = 0;
    Start = NULL;
    End = NULL;
    Pos = NULL;
}


Edge::Edge(int x, std::shared_ptr<Vertex> new_start, std::shared_ptr<Vertex> new_end){

    Object = x;
    Start = new_start;
    End = new_end;
    Pos = NULL;
}