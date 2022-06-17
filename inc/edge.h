#pragma once

#include "vertex.h"

/*Krawędź grafu*/
class Edge{

    private:

        /*Wskaźnik na wierzchołek na początku krawędzi*/
        Vertex* Start;

        /*Wskaźnik na wierzchołek na końcu krawędzi*/
        Vertex* End;

        /*Pozycja danej krawędzi w kolejce krawędzi grafu*/
        Node<Edge>* Pos;

    public:

        Edge();

        Edge(Vertex* new_start, Vertex* new_end);
    
        Node<Edge>* GetPos() const {return Pos;};

        void SetPos(Node<Edge>* new_pos) {Pos = new_pos;};

        Vertex GetStart() const {return *Start;};

        Vertex GetEnd() const {return *End;};

};


std::ostream &operator << (std::ostream &out, Edge const &edge);