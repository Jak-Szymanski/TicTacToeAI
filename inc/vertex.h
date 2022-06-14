#pragma once

#include "gamestate.h"

template<typename Type>
class Edge;

/*Wierzchołek grafu zawierającego obiekty typu Type
  Jest on używany w grafie opisanego poprzez listy krawędzi i wierzchołków*/
template<typename Type>
class Vertex{

    private:

        Type Object;

        /*Pozycja danego wierzchołka w kolejce wierzchołków grafu*/
        Node<Vertex*>* Pos;

    public:

        Vertex();

        Vertex(Type x);

        Node<Vertex*>* GetPos() const {return Pos;};

        void SetPos(Node<Vertex*>* new_pos) {Pos = new_pos;};

        Type GetObject() const {return Object;};

        void SetObject(Type new_object) {Object = new_object;};

        bool operator == (const Vertex &V) const;

        void SetCost(int new_cost) {Object.SetCost(new_cost);};

        //virtual Dequeue<Edge>>* GetAdjListPos() const {return NULL;};

        friend std::ostream &operator << (std::ostream &out, Vertex const &vertex); 

            /* --- Poniższe wirtualne metody są opisane tylko przy innych reprezentacji grafu (listy i macierzy sąsiedztwa) --- */

        virtual int GetIndex() const {return 2;};

        virtual void SetIndex(int new_index){};

        virtual Dequeue<Edge<Type>*>* GetAdjList() {return NULL;};

        virtual void SetAdjList(Dequeue<Edge<Type>*>* new_adjlistpos){};
        
       

};

template<typename Type>
std::ostream &operator << (std::ostream &out, Vertex<Type> const &vertex){
    out << vertex.Object;
    return out;
}


template<typename Type>
Vertex<Type>::Vertex(){

    Object = Type();
    Pos = NULL;
}

template<typename Type>
Vertex<Type>::Vertex(Type x){

    Object = Type(x);
    Pos = NULL;    
}

template<typename Type>
bool Vertex<Type>::operator== (const Vertex<Type> &V) const{

    return (Object == V.GetObject() && Pos == V.GetPos());
}




