#pragma once

#include "gamestate.h"

template<typename Type>
class Edge;

template<typename Type>
class Vertex{

    private:

        Type Object;

        Node<std::shared_ptr<Vertex>>* Pos;

    public:

        Vertex();

        Vertex(Type x);

        Node<std::shared_ptr<Vertex>>* GetPos() const {return Pos;};

        void SetPos(Node<std::shared_ptr<Vertex>>* new_pos) {Pos = new_pos;};

        Type GetObject() const {return Object;};

        void SetObject(Type new_object) {Object = new_object;};

        bool operator == (const Vertex &V) const;

        void SetCost(int new_cost) {Object.SetCost(new_cost);};

        //virtual Dequeue<std::shared_ptr<Edge>>* GetAdjListPos() const {return NULL;};

        virtual int GetIndex() const {return 2;};

        virtual void SetIndex(int new_index){};

        virtual Dequeue<std::shared_ptr<Edge<Type>>>* GetAdjList() {return NULL;};

        virtual void SetAdjList(Dequeue<std::shared_ptr<Edge<Type>>>* new_adjlistpos){};
        
        friend std::ostream &operator << (std::ostream &out, Vertex const &vertex);        

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




