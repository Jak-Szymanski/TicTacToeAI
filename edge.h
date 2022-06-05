#pragma once

#include "vertex.h"


class Edge{

    private:

        int Object;

        Vertex* Start;

        Vertex* End;

        Node<Edge>* Pos;

    public:

        Edge();

        Edge(int x, Vertex* new_start, Vertex* new_end);
    
        Node<Edge>* GetPos() const {return Pos;};

        void SetPos(Node<Edge>* new_pos) {Pos = new_pos;};

        int GetObject() const {return Object;};

        Vertex GetStart() const {return *Start;};

        Vertex GetEnd() const {return *End;};

};


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