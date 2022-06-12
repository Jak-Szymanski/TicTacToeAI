#ifndef GRAPH_H
#define GRAPH_H

#include "dequeueptr.h"

#define SEARCH_DEPTH 1




class Graph{

    private:

        Dequeue<std::shared_ptr<Vertex>> VQueue;

        Dequeue<std::shared_ptr<Edge>> EQueue;

    public:

        Graph();

        Graph(const Graph &G);

        Dequeue<std::shared_ptr<Vertex>>* Vertices(){return &VQueue;};

        Dequeue<std::shared_ptr<Edge>>* Edges(){return &EQueue;};

/*         Dequeue<std::shared_ptr<Vertex>> Vertices() const {return VQueue;};

        Dequeue<std::shared_ptr<Edge>> Edges() const {return EQueue;}; */

        virtual std::shared_ptr<Vertex> InsertVertex(GameState x);

        virtual std::shared_ptr<Edge> InsertEdge(int x, std::shared_ptr<Vertex> start, std::shared_ptr<Vertex> end);

        virtual Dequeue<std::shared_ptr<Edge>> IncidentEdges(std::shared_ptr<Vertex> V) const;

        virtual Dequeue<std::shared_ptr<Vertex>> AdjacentVertices(std::shared_ptr<Vertex> V) const;

        virtual bool AreAdjacent(std::shared_ptr<Vertex> V1, std::shared_ptr<Vertex> V2) const;

        virtual void RemoveEdge(std::shared_ptr<Edge> E);

        virtual void RemoveVertex(std::shared_ptr<Vertex> V);

        int NumberVertices() const {return VQueue.Size();};

        int NumberEdges() const {return EQueue.Size();};

        void Delete();

        void CreateFutureMovesTree(std::shared_ptr<Vertex> V1, int i);

        int Min(std::shared_ptr<Vertex> V, int *alpha, int *beta);

        int Max(std::shared_ptr<Vertex> V, int *alpha, int *beta);

        int Minimax(std::shared_ptr<Vertex> V, int* alpha, int* beta);

        GameState GetMaxMove(std::shared_ptr<Vertex> V);

        friend std::ostream &operator << (std::ostream &out, Graph &graph);
};

#endif

