#pragma once

#include "dequeue.h"
#include "size.h"
#include <vector>

#define OUTSIDE_BOARD_ERR 1
#define INCORRECT_TYPE_ERR 2
#define SPACE_TAKEN_ERR 3

#define DRAW -2
#define POTENTIAL_DRAW -100


/*Klasa opisująca stan gry w kółko krzyżyk w danym momencie*/
class GameState{

    private:

        /*Tablica gry w kółko krzyżyk (1 = kółko, -1 = krzyżyk)*/
        std::vector<std::vector<int>> Board;

        /* Wartość heurystyczna gry w danym momencie */
        int Cost;

        /* Który z graczy ma następny ruch (1 = kółko, -1 = krzyżyk) */
        int NextMove;

    public:

        GameState();

        GameState(const GameState &GS);

        /* Wykonaj ruch na danym miejscu planszy zgodnie z tym, który gracz powinien pójść następny*/
        void MakeMove(int x, int y);

        /*Wstaw daną planszę do obecnej planszy (nie zmieniaj innych parametrów)*/
        void InsertBoard(GameState GS);

        /*Usuń znak w danym miejscu planszy*/
        void DeleteChar(int x, int y);

        //std::vector<std::vector<int>> GetBoard() const {return Board;};

        int GetCost() const {return Cost;};

        void SetCost(int new_cost) {Cost = new_cost;};

        int GetNextMove() const {return NextMove;};

        /*Sprawdź czy któryś z graczy wygrał (1 = kółko, -1 = krzyżyk, 0 = w danym momencie nikt nie wygrał)*/
        int CheckWinner();

        /*Funkcja heurystyczna do wyznaczania kosztu obecnej planszy*/
        int DetermineCost();

        /*Zwróć tablicę wszystkich możliwych plansz w następnym ruchu*/
        Dequeue<GameState> GeneratePossibleMoves() const;

        /*Zmień gracza który ma następny ruch na przeciwnego*/
        void ChangeMove() {NextMove = -NextMove;};

        bool operator == (const GameState &GS) const;

        /*Wyświetlanie planszy (tylko planszy)*/
        friend std::ostream &operator<< (std::ostream &out, const GameState& GS);

};
