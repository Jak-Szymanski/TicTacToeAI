#pragma once

#include "vertex.h"

template<typename Type>
class Edge{

    private:

        int Object;

        Vertex<Type>* Start;

        Vertex<Type>* End;

        Node<Edge<Type>*>* Pos;

    public:

        Edge();

        Edge(int x, Vertex<Type>* new_start, Vertex<Type>* new_end);
    
        Node<Edge<Type>*>* GetPos() const {return Pos;};

        void SetPos(Node<Edge<Type>*>* new_pos) {Pos = new_pos;};

        int GetObject() const {return Object;};

        void SetObject(int new_object) {Object = new_object;};

        Vertex<Type>* GetStart() {return Start;};

        void SetStart(Vertex<Type>* new_start) {Start = new_start;};

        Vertex<Type>* GetEnd() {return End;};

        void SetEnd(Vertex<Type>* new_end) {End = new_end;};

        virtual Node<Edge<Type>*>* GetAdjListStart() {return NULL;};

        virtual Node<Edge<Type>*>* GetAdjListEnd() {return NULL;};

        friend std::ostream &operator << (std::ostream &out, Edge<Type> const &edge);

};

template<typename Type>
std::ostream &operator << (std::ostream &out, Edge<Type> const &edge){

    out << "Poczatek: " << std::endl;
    out << *edge.Start << std::endl;
    out << "Koniec: " << std::endl;
    out << *edge.End << std::endl;
    out << "Obiekt: " << std::endl;
    out << edge.Object << std::endl;
    return out;
}


template<typename Type>
Edge<Type>::Edge(){

    Object = 0;
    Start = NULL;
    End = NULL;
    Pos = NULL;
}


template<typename Type>
Edge<Type>::Edge(int x, Vertex<Type>* new_start, Vertex<Type>* new_end){

    Object = x;
    Start = new_start;
    End = new_end;
    Pos = NULL;
}


