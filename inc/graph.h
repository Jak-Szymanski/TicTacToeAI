#pragma once

#include "edge.h"

#define SEARCH_DEPTH 4



/*Graf zawierający stany gry opisany poprzez listę krawędzi i listę wierzchołków*/
class Graph{

    private:

        /*Lista wierzchołków*/
        Dequeue<Vertex> VQueue;

        /*Lista krawędzi*/
        Dequeue<Edge> EQueue;

    public:
        /* --- Metody grafu: --- */

        Dequeue<Vertex> Vertices() const {return VQueue;};

        Dequeue<Edge> Edges() const {return EQueue;};

       /*Wstaw nowy wierzchołek zawierający element x, i zwróć wskaźnik na niego*/
        Vertex* InsertVertex(GameState x);

        /*Wstaw nową krawędź mająca dane wierzchołki końcowe, i zwróć wskaźnik na nią*/
        Edge InsertEdge(Vertex* start, Vertex* end);

        /*Zwróć krawędzie przylegające do danego wierzchołka*/
        Dequeue<Edge> IncidentEdges(Vertex *V) const;

        /*Zwróć wierzchołki sąsiadujące z danym wierzchołkiem*/
        Dequeue<Vertex> AdjacentVertices(Vertex *V) const;

        /*Wyczyść cały graf*/
        void Delete();

        /* --- Metody sztucznej inteligencji gry: -----*/


        /*Stwórz graf zawierający potencjalne przyszłe ruchy obu członków, zaczynając od stanu opisanego wierzchołkiem V1
        szukając o i ruchów do przodu*/
        void CreateFutureMovesTree(Vertex* V1, int i);


        /*Wykonaj na wierzchołku V algorytm Min z algorytmu Minimax
        Zwróć 1 jeżeli będzie musiało nastąpić cięcie beta, 0 jeżeli nie
        Wpisz odpowiednie wartości alfa i beta do argumentów*/
        int Min(Vertex *V, int *alpha, int *beta);


        /*Wykonaj na wierzchołku V algorytm Max z algorytmu Minimax
        Zwróć 1 jeżeli będzie musiało nastąpić cięcie alfa, 0 jeżeli nie
        Wpisz odpowiednie wartości alfa i beta do argumentów*/
        int Max(Vertex *V, int *alpha, int *beta);

        /*Wykonuj rekursywnie algorytm minimax z alfa-beta cięciami na wierzchołku V i każdym jego kolejnym wierzchołku
        Wartość alfa powinna teoretycznie być równa nieskonczoności a beta minus nieskonczoności
         Są one na każdym poziomie przechodzenia przez ruchy ustawiane na wartości 100 i -100 */
        int Minimax(Vertex *V, int* alpha, int* beta);

        /*Zwróć ruch o największej wartości (czyli ruch najlepszy dla komputera po wykonaniu algorytmu minimax)*/
        GameState GetMaxMove(Vertex *V);
};

std::ostream &operator << (std::ostream &out, Graph const &graph);