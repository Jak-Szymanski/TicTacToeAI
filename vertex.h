#pragma once

#include "field.h"

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

        GameState<Size> GetObject() const {return Object;};

        bool operator == (const Vertex<Size> &V) const;

        void SetCost(int new_cost) {Object.SetCost(new_cost);};
};

template<int Size>
std::ostream &operator << (std::ostream &out, Vertex<Size> const &vertex){
    out << vertex.GetObject();
    return out;
}


template <int Size>
Vertex<Size>::Vertex(){

    Object = GameState<Size>();
    Pos = NULL;
}

template <int Size>
Vertex<Size>::Vertex(GameState<Size> x){

    Object = x;
    Pos = NULL;    
}

template<int Size>
bool Vertex<Size>::operator== (const Vertex<Size> &V) const{

    return (Object == V.GetObject() && Pos == V.GetPos());
}

