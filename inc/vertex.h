#pragma once

#include "gamestate.h"

/*Wierzchołek grafu zawierący stan gry*/
class Vertex{

    private:

        GameState Object;

        /*Pozycja danego wierzchołka w kolejce wierzchołków grafu*/
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


std::ostream &operator << (std::ostream &out, Vertex const &vertex);

