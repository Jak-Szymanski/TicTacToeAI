#pragma once

#include "vertex.h"

template<typename Type>
class Edge{

    private:

        int Object;

        std::shared_ptr<Vertex<Type>> Start;

        std::shared_ptr<Vertex<Type>> End;

        Node<std::shared_ptr<Edge<Type>>>* Pos;

    public:

        Edge();

        Edge(int x, std::shared_ptr<Vertex<Type>> new_start, std::shared_ptr<Vertex<Type>> new_end);
    
        Node<std::shared_ptr<Edge<Type>>>* GetPos() const {return Pos;};

        void SetPos(Node<std::shared_ptr<Edge<Type>>>* new_pos) {Pos = new_pos;};

        int GetObject() const {return Object;};

        void SetObject(int new_object) {Object = new_object;};

        std::shared_ptr<Vertex<Type>> GetStart() {return Start;};

        void SetStart(std::shared_ptr<Vertex<Type>> new_start) {Start = new_start;};

        std::shared_ptr<Vertex<Type>> GetEnd() {return End;};

        void SetEnd(std::shared_ptr<Vertex<Type>> new_end) {End = new_end;};

        virtual Node<std::shared_ptr<Edge<Type>>>* GetAdjListStart() {return NULL;};

        virtual Node<std::shared_ptr<Edge<Type>>>* GetAdjListEnd() {return NULL;};

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
Edge<Type>::Edge(int x, std::shared_ptr<Vertex<Type>> new_start, std::shared_ptr<Vertex<Type>> new_end){

    Object = x;
    Start = new_start;
    End = new_end;
    Pos = NULL;
}


