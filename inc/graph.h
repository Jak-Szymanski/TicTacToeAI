#pragma once

#include "edge.h"

#define SEARCH_DEPTH 4




class Graph{

    private:

        Dequeue<Vertex> VQueue;

        Dequeue<Edge> EQueue;

    public:

        Dequeue<Vertex> Vertices() const {return VQueue;};

        Dequeue<Edge> Edges() const {return EQueue;};

        Vertex* InsertVertex(GameState x);

        Edge InsertEdge(int x, Vertex* start, Vertex* end);

        Dequeue<Edge> IncidentEdges(Vertex *V) const;

        Dequeue<Vertex> AdjacentVertices(Vertex *V) const;

        void Delete();

        void CreateFutureMovesTree(Vertex* V1, int i);

        int Min(Vertex *V, int *alpha, int *beta);

        int Max(Vertex *V, int *alpha, int *beta);

        int Minimax(Vertex *V, int* alpha, int* beta);

        GameState GetMaxMove(Vertex *V);

        friend std::ostream &operator << (std::ostream &out, Graph const &graph);
};

