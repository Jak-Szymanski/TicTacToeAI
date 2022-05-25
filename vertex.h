#pragma once

#include "node.h"

template <int Size>
class Vertex{

    private:

        GameState<Size> Object;

        Node<Vertex<Size>> *Pos;

    public:

        Vertex();

        Vertex(GameState<Size> x);

        Node<Vertex<Size>>* GetPos() const {return Pos;};

        void SetPos(Node<Vertex<Size>>* new_pos) {Pos = new_pos;};
};

template<int Size>
std::ostream &operator << (std::ostream &out, Vertex<Size> const &vertex){
    out << vertex.Object;
    return out;
}


template <int Size>
Vertex<Size>::Vertex(){

    Object = GameState<Size>();
    Pos = NULL;
}

/* template <int Size>
Vertex<Size>::Vertex(GameState<Size> x){

    
} */
