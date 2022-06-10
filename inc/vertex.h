#pragma once

#include "gamestate.h"


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

        void SetObject(GameState new_object) {Object = new_object;};

        bool operator == (const Vertex &V) const;

        void SetCost(int new_cost) {Object.SetCost(new_cost);};
        
        friend std::ostream &operator << (std::ostream &out, Vertex const &vertex);        

};




