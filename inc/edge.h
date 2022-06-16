#pragma once

#include "vertex.h"

/*Krawędź grafu zawierającego obiekty typu Type
  Jest ona używana w grafie opisanego poprzez listy krawędzi i wierzchołków*/
template<typename Type>
class Edge{

    private:

        /*Krawędź zawsze zawiera obiekty typu int*/
        int Object;

        /*Wskaźnik na wierzchołek na początku krawędzi*/
        Vertex<Type>* Start;

        /*Wskaźnik na wierzchołek na końcu krawędzi*/
        Vertex<Type>* End;

        /*Pozycja danej krawędzi w kolejce krawędzi grafu*/
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

        template<typename Type>
        friend std::ostream &operator << (std::ostream &out, Edge<Type> const &edge);

        virtual void Delete();

        /* --- Poniższe wirtualne metody są opisane tylko przy innych reprezentacji grafu (listy i macierzy sąsiedztwa) --- */

        virtual Node<Edge<Type>*>* GetAdjListStart() {return NULL;};

        virtual Node<Edge<Type>*>* GetAdjListEnd() {return NULL;};
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

template<typename Type>
void Edge<Type>::Delete(){
    //free(Start);
    //free(End);
   // delete Pos->Elem;
    free(Pos);
}

