#pragma once

#include "dequeue.h"
#include "size.h"
#include <vector>

#define OUTSIDE_BOARD_ERR 1
#define INCORRECT_TYPE_ERR 2
#define SPACE_TAKEN_ERR 3

#define DRAW -2
#define POTENTIAL_DRAW -100

class GameState{

    private:

        std::vector<std::vector<int>> Board;

        int Cost;

        int NextMove;

    public:

        GameState();

        GameState(const GameState &GS);

        void InsertChar(int x, int y);

        void InsertBoard(GameState GS);

        void DeleteChar(int x, int y);

        //std::vector<std::vector<int>> GetBoard() const {return Board;};

        int GetCost() const {return Cost;};

        void SetCost(int new_cost) {Cost = new_cost;};

        int GetNextMove() const {return NextMove;};

        int CheckWinner();

        int DetermineCost();

        Dequeue<GameState> GeneratePossibleMoves() const;

        void ChangeMove() {NextMove = -NextMove;};

        bool operator == (const GameState &GS) const;

        friend std::ostream &operator<< (std::ostream &out, const GameState& GS);

};
