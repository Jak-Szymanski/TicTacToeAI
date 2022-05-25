#pragma once
#include <iostream>

#define OUTSIDE_BOARD_ERR 1
#define INCORRECT_TYPE_ERR 2
#define SPACE_TAKEN_ERR 3

template<int Size>
class GameState{

    public:

        int Board[Size][Size];

        int Cost;

        int NextMove;

    //public:

        GameState();

        void InsertChar(int x, int y);

        int CheckWinner();

        //void DisplayBoard();

        int DetermineCost();
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
    return out;
}

template<int Size>
GameState<Size>::GameState(){
    for(int i=0;i<Size;i++){
        for(int j=0;j<Size;j++){
            Board[i][j] = 0;
        }
    }
    NextMove = 1;
}



template <int Size>
void GameState<Size>::InsertChar(int x, int y){

    if (x >= Size || y >= Size || x < 0 || y < 0) throw OUTSIDE_BOARD_ERR;

    //if (type < -1 || type > 1) throw INCORRECT_TYPE_ERR;

    if (Board[x][y] != 0) throw SPACE_TAKEN_ERR;

    Board[x][y] = NextMove;

    NextMove = -NextMove;
}

template <int Size>
int GameState<Size>::CheckWinner(){

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
        if(Board[i][Size-i-1] == Board[i-1][Size-i]){
            if (i+2 == Size) return Board[i][i];
            else continue;
        } else break;
    }
    return 0;
}

template<int Size>
int GameState<Size>::DetermineCost(){
    
    int arr[2*Size + 2];
    int k=0;

    for(int i=0; i<2*Size+2;i++){
        arr[i] = 0;
    }

    for(int i=0;i<Size;i++){
        for(int j=0;j<Size;j++){
            if(arr[k] * Board[i][j] < 0){
                arr[k] = 0;
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
                break;
            }
            arr[k] += Board[j][i];
        }
        k++;
    }

    for(int i=0;i<Size;i++){
        if(arr[k] * Board[i][i] < 0){
            arr[k] = 0;
            break;
        }
        arr[k] += Board[i][i];
    }
    k++;

    for(int i=0;i<Size;i++){
        if(arr[k] * Board[i][Size-i-1] < 0){
            arr[k] = 0;
            break;
        }
        arr[k] += Board[i][Size-i-1];
    }
    k++;

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

    if(-smallest > biggest) return smallest;
    if(biggest > -smallest) return biggest;
    if(NextMove == 1) return biggest;
    if(NextMove == -1) return smallest;
    return 0;
}


/* template <int Size>
void GameState<Size>::DisplayBoard(){

    for(int i=0;i<Size;i++){
        for(int j=0;j<Size;j++){
            if (Board[i][j] == -1) std::cout << " X ";
            if (Board[i][j] == 0) std::cout << "   ";
            if (Board[i][j] == 1) std::cout << " O ";
            if (j != Size -1) std::cout << "|";
        }
        std::cout << std::endl;
    }
} */