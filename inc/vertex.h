#pragma once

#include "gamestate.h"

class Edge;

class Vertex{

    private:

        GameState Object;

        Node<std::shared_ptr<Vertex>>* Pos;

    public:

        Vertex();

        Vertex(GameState x);

        Node<std::shared_ptr<Vertex>>* GetPos() const {return Pos;};

        void SetPos(Node<std::shared_ptr<Vertex>>* new_pos) {Pos = new_pos;};

        GameState GetObject() const {return Object;};

        void SetObject(GameState new_object) {Object = new_object;};

        bool operator == (const Vertex &V) const;

        void SetCost(int new_cost) {Object.SetCost(new_cost);};

        //virtual Dequeue<std::shared_ptr<Edge>>* GetAdjListPos() const {return NULL;};

        virtual int GetIndex() const {return 2;};

        virtual void SetIndex(int new_index){};

        virtual Dequeue<std::shared_ptr<Edge>>* GetAdjListPos() {return NULL;};

        virtual void SetAdjListPos(Dequeue<std::shared_ptr<Edge>>* new_adjlistpos){};
        
        friend std::ostream &operator << (std::ostream &out, Vertex const &vertex);        

};




