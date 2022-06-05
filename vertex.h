#pragma once

#include "field.h"


class Vertex{

    private:

        GameState Object;

        Node<Vertex> *Pos;

    public:

        Vertex();

        Vertex(GameState x);

        Node<Vertex>* GetPos() const {return Pos;};

        void SetPos(Node<Vertex>* new_pos) {Pos = new_pos;};

        GameState GetObject() const {return Object;};

        bool operator == (const Vertex &V) const;

        void SetCost(int new_cost) {Object.SetCost(new_cost);};
};


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

