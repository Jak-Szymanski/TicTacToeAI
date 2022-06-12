#pragma once

#include "graph.h"
#include "adjmatrixvertex.h"

class AdjacencyMatrixGraph: public Graph{

    private:

        std::vector<std::vector<std::shared_ptr<Edge>>> AdjacencyMatrix;

    public:

       // AdjacencyMatrixGraph(const Graph G);

        friend std::ostream &operator << (std::ostream &out, AdjacencyMatrixGraph const &graph);

        std::shared_ptr<Vertex> InsertVertex(GameState x);

        std::shared_ptr<Edge> InsertEdge(int x, std::shared_ptr<Vertex> start, std::shared_ptr<Vertex> end);

        Dequeue<std::shared_ptr<Edge>> IncidentEdges(std::shared_ptr<Vertex> V) const;

        Dequeue<std::shared_ptr<Vertex>> AdjacentVertices(std::shared_ptr<Vertex> V) const;

        bool AreAdjacent(std::shared_ptr<Vertex> V1, std::shared_ptr<Vertex> V2) const;

        void RemoveEdge(std::shared_ptr<Edge> E);

        void RemoveVertex(std::shared_ptr<Vertex> V);

};