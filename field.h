#pragma once

#include "dequeue.h"

#define OUTSIDE_BOARD_ERR 1
#define INCORRECT_TYPE_ERR 2
#define SPACE_TAKEN_ERR 3

#define DRAW -2
#define POTENTIAL_DRAW -100

template<int Size>
class GameState{

    public:

        int Board[Size][Size];

        int Cost;

        int NextMove;

    //public:

        GameState();

        GameState(const GameState<Size> &GS);

        void InsertChar(int x, int y);

        void InsertBoard(GameState<Size> GS);

       // GameState &operator = (const GameState& GS) {return *this;};

        void DeleteChar(int x, int y);

        int GetCost() {return Cost;};

        void SetCost(int new_cost) {Cost = new_cost;};

        int CheckWinner();

        int DetermineCost();

        Dequeue<GameState<Size>> GeneratePossibleMoves() const;

        void ChangeMove() {NextMove = -NextMove;};

        bool operator == (const GameState<Size> &GS) const;

};

template<int Size>
std::ostream &operator << (std::ostream &out, GameState<Size> const &GS){

    for(int i=0;i<Size;i++){
        for(int j=0;j<Size;j++){
            if (GS.Board[i][j] == -1) out << " X ";
            if (GS.Board[i][j] == 0) out << "   ";
            if (GS.Board[i][j] == 1) out << " O ";
            if (j != Size -1) out << "|";
        }
        out << std::endl;
    }
    //out << "Koszt: " << GS.Cost << std::endl;
    return out;
}

template<int Size>
GameState<Size>::GameState(){
    for(int i=0;i<Size;i++){
        for(int j=0;j<Size;j++){
            Board[i][j] = 0;
        }
    }
    NextMove = -1;
    Cost = 0;
}

template<int Size>
GameState<Size>::GameState(const GameState<Size> &GS){
    for(int i=0;i<Size;i++){
        for(int j=0;j<Size;j++){
            Board[i][j] = GS.Board[i][j];
        }
    }
    NextMove = GS.NextMove;
    Cost = GS.Cost;
}



template <int Size>
void GameState<Size>::InsertChar(int x, int y){

    if (x >= Size || y >= Size || x < 0 || y < 0) throw OUTSIDE_BOARD_ERR;

    //if (type < -1 || type > 1) throw INCORRECT_TYPE_ERR;

    if (Board[x][y] != 0) throw SPACE_TAKEN_ERR;

    Board[x][y] = NextMove;
}

template<int Size>
void GameState<Size>::InsertBoard(GameState<Size> GS){
    for(int i=0;i<Size;i++){
        for(int j=0;j<Size;j++){
            Board[i][j] = GS.Board[i][j];
        }
    }
}

template <int Size>
void GameState<Size>::DeleteChar(int x, int y){

    if (x >= Size || y >= Size || x < 0 || y < 0) throw OUTSIDE_BOARD_ERR;

    //if (type < -1 || type > 1) throw INCORRECT_TYPE_ERR;

    //if (Board[x][y] != 0) throw SPACE_TAKEN_ERR;

    Board[x][y] = 0;

    //ChangeMove();
}

template <int Size>
int GameState<Size>::CheckWinner(){

    int draw=0;
    for(int i=0;i<Size;i++){
        for(int j=0;j<Size;j++){
            if(Board[i][j] == Board[i][j+1]){
                if (j+2 == Size) return Board[i][j];
                else continue;
            } else break;
        }
    }

    for(int i=0;i<Size;i++){
        for(int j=0;j<Size;j++){
            if(Board[j][i] == Board[j+1][i]){
                if (j+2 == Size) return Board[j][i];
                else continue;
            } else break;
        }
    }

    for(int i=0; i<Size;i++){
        if(Board[i][i] == Board[i+1][i+1]){
            if (i+2 == Size) return Board[i][i];
            else continue;
        } else break;
    }

    for(int i=0; i<Size;i++){
        if(Board[Size-i-1][i] == Board[Size-i-2][i+1]){
            if (i+2 == Size) return Board[i][i];
            else continue;
        } else break;
    }


    for(int i=0; i<Size;i++){
        for(int j=0; j<Size;j++){
            if(Board[i][j] == 0) return 0;
        }
    }
    
    return DRAW;
}

template<int Size>
int GameState<Size>::DetermineCost(){
    
    int arr[2*Size + 2];
    int k=0;
    int draw = 0;

    for(int i=0; i<2*Size+2;i++){
        arr[i] = 0;
    }

    for(int i=0;i<Size;i++){
        for(int j=0;j<Size;j++){
            if(arr[k] * Board[i][j] < 0){
                arr[k] = 0;
                draw++;
                break;
            }
            arr[k] += Board[i][j];
        }
        k++;
        
    }

    for(int i=0;i<Size;i++){
        for(int j=0;j<Size;j++){
            if(arr[k] * Board[j][i] < 0){
                arr[k] = 0;
                draw++;
                break;
            }
            arr[k] += Board[j][i];
        }
        k++;
    }

    for(int i=0;i<Size;i++){
        if(arr[k] * Board[i][i] < 0){
            arr[k] = 0;
            draw++;
            break;
        }
        arr[k] += Board[i][i];
    }
    k++;

    for(int i=0;i<Size;i++){
        if(arr[k] * Board[i][Size-i-1] < 0){
            arr[k] = 0;
            draw++;
            break;
        }
        arr[k] += Board[i][Size-i-1];
    }
    k++;

   // if(draw == 2*Size+2) return POTENTIAL_DRAW;
    int smallest = 0;
    int biggest = 0;

    for(int i=0; i<2*Size+2;i++){
        if(arr[i] > biggest){
            biggest = arr[i];
            continue;
        }
        if(arr[i] < smallest){
            smallest = arr[i];
            continue;
        }
    }

    if(-smallest > biggest){
        Cost = smallest;
        return smallest;
    }
    if(biggest > -smallest){
        Cost = biggest;
        return biggest;
    } 
    if(NextMove == 1){ 
        Cost = biggest;
        return biggest;
    }
    if(NextMove == -1) {
        Cost = smallest;
        return smallest;
    }
    Cost = 0;
    return 0;
}


template<int Size>
Dequeue<GameState<Size>> GameState<Size>::GeneratePossibleMoves() const{

    Dequeue<GameState<Size>> dequeue;
    GameState<Size> GS_copy(*this);

    for(int i=0;i<Size;i++){
        for(int j=0;j<Size;j++){
            try{GS_copy.InsertChar(i,j);}
            catch(const int error_type){
                continue;
            }
            GS_copy.ChangeMove();
            GS_copy.DetermineCost();
            dequeue.InsertFront(GS_copy);
            GS_copy.DeleteChar(i,j);
            GS_copy.ChangeMove();
        }
    }
    return dequeue;

}


template<int Size>
bool GameState<Size>::operator== (const GameState<Size> &GS) const{

    if(Cost != GS.Cost || NextMove != GS.NextMove) return false;

    for(int i=0;i<Size;i++){
        for(int j=0;j<Size;j++){
            if (Board[i][j] != GS.Board[i][j]) return false;
        }
    }
    return true;
}