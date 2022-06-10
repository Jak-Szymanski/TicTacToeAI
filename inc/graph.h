#pragma once

#include "dequeueptr.h"

#define SEARCH_DEPTH 1




class Graph{

    private:

        Dequeue<std::shared_ptr<Vertex>> VQueue;

        Dequeue<std::shared_ptr<Edge>> EQueue;

    public:

        Graph();

        Graph(const Graph &G);

        Dequeue<std::shared_ptr<Vertex>> Vertices() const {return VQueue;};

        Dequeue<std::shared_ptr<Edge>> Edges() const {return EQueue;};

        std::shared_ptr<Vertex> InsertVertex(GameState x);

        std::shared_ptr<Edge> InsertEdge(int x, std::shared_ptr<Vertex> start, std::shared_ptr<Vertex> end);

        Dequeue<Edge> IncidentEdges(std::shared_ptr<Vertex> V) const;

        Dequeue<Vertex> AdjacentVertices(std::shared_ptr<Vertex> V) const;

        int NumberVertices() const {return VQueue.Size();};

        int NumberEdges() const {return EQueue.Size();};

        void Delete();

        void CreateFutureMovesTree(std::shared_ptr<Vertex> V1, int i);

        int Min(std::shared_ptr<Vertex> V, int *alpha, int *beta);

        int Max(std::shared_ptr<Vertex> V, int *alpha, int *beta);

        int Minimax(std::shared_ptr<Vertex> V, int* alpha, int* beta);

        GameState GetMaxMove(std::shared_ptr<Vertex> V);

        friend std::ostream &operator << (std::ostream &out, Graph const &graph);
};

