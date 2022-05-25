#pragma once
#include "vertex.h"

template <int Size>
class Edge{

    private:

        int Object;

        Vertex<Size>* Start;

        Vertex<Size>* End;

        Node<Edge<Size>>* Pos;

    public:

        Edge();

        Edge(GameState<Size> x, Vertex<Size>* new_start, Vertex<Size>* new_end);

};

template<int Size>
std::ostream &operator << (std::ostream &out, Edge<Size> const &edge){
    out << "Początek: " << std::endl;
    out << edge.Start << std::endl;
    out << "Koniec: " << std::endl;
    out << edge.End << std::endl;
    return out;
}


template <int Size>
Edge<Size>::Edge(){

    Object = GameState<Size>();
    Start = NULL;
    End = NULL;
    Pos = NULL;
}

template <int Size>
Edge<Size>::Edge(GameState<Size> x, Vertex<Size>* new_start, Vertex<Size>* new_end){

    Object = x;
    Start = new_start;
    End = new_end;
    Pos = NULL;
}