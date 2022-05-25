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

        Edge(int x, Vertex<Size>* new_start, Vertex<Size>* new_end);
    
        Node<Edge<Size>>* GetPos() const {return Pos;};

        void SetPos(Node<Edge<Size>>* new_pos) {Pos = new_pos;};

        int GetObject() const {return Object;};

        Vertex<Size> GetStart() const {return *Start;};

        Vertex<Size> GetEnd() const {return *End;};

};

template<int Size>
std::ostream &operator << (std::ostream &out, Edge<Size> const &edge){
    out << "Poczatek: " << std::endl;
    out << edge.GetStart() << std::endl;
    out << "Koniec: " << std::endl;
    out << edge.GetEnd() << std::endl;
    out << "Obiekt: " << std::endl;
    out << edge.GetObject() << std::endl;
    return out;
}


template <int Size>
Edge<Size>::Edge(){

    Object = 0;
    Start = NULL;
    End = NULL;
    Pos = NULL;
}

template <int Size>
Edge<Size>::Edge(int x, Vertex<Size>* new_start, Vertex<Size>* new_end){

    Object = x;
    Start = new_start;
    End = new_end;
    Pos = NULL;
}