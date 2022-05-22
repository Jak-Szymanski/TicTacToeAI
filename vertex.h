#pragma once

#include "node.h"
#include "graph.h"

template <int Size>
class Vertex{

    private:

        GameState<Size> Object;

        Node<Vertex<Size>> *Pos;

    public:

        Vertex();

        Vertex(GameState<Size> x);
};

template<int Size>
std::ostream &operator << (std::ostream &out, Vertex<Size> const &vertex){
    out << vertex.Object;
    return out;
}


template <int Size>
Vertex<Size>::Vertex(){

    Object = GameState();
    Pos = NULL;
}

/* template <int Size>
Vertex<Size>::Vertex(GameState<Size> x){

    
} */
