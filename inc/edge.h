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

        void SetObject(int new_object) {Object = new_object;};

        Vertex GetStart() const {return *Start;};

        void SetStart(Vertex* new_start) {Start = new_start;};

        Vertex GetEnd() const {return *End;};

        void SetEnd(Vertex* new_end) {End = new_end;};

        friend std::ostream &operator << (std::ostream &out, Edge const &edge);

};


