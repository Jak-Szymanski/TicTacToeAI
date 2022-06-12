#pragma once

#include "vertex.h"


class Edge{

    private:

        int Object;

        std::shared_ptr<Vertex> Start;

        std::shared_ptr<Vertex> End;

        Node<std::shared_ptr<Edge>>* Pos;

    public:

        Edge();

        Edge(int x, std::shared_ptr<Vertex> new_start, std::shared_ptr<Vertex> new_end);
    
        Node<std::shared_ptr<Edge>>* GetPos() const {return Pos;};

        void SetPos(Node<std::shared_ptr<Edge>>* new_pos) {Pos = new_pos;};

        int GetObject() const {return Object;};

        void SetObject(int new_object) {Object = new_object;};

        std::shared_ptr<Vertex> GetStart() {return Start;};

        void SetStart(std::shared_ptr<Vertex> new_start) {Start = new_start;};

        std::shared_ptr<Vertex> GetEnd() {return End;};

        void SetEnd(std::shared_ptr<Vertex> new_end) {End = new_end;};

        virtual Node<std::shared_ptr<Edge>>* GetAdjListStart() {return NULL;};

        virtual Node<std::shared_ptr<Edge>>* GetAdjListEnd() {return NULL;};

        friend std::ostream &operator << (std::ostream &out, Edge const &edge);

};


