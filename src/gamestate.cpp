#include "../inc/gamestate.h"

int BOARD_SIZE;

std::ostream &operator << (std::ostream &out, const GameState& GS){

    for(int i=0;i<BOARD_SIZE;i++){
        for(int j=0;j<BOARD_SIZE;j++){
            if (GS.Board[i][j] == -1) out << " X ";
            if (GS.Board[i][j] == 0) out << "   ";
            if (GS.Board[i][j] == 1) out << " O ";
            if (j != BOARD_SIZE -1) out << "|";
        }
        out << std::endl;
    }
    return out;
}


GameState::GameState(){

    Board.resize(BOARD_SIZE, std::vector<int>(BOARD_SIZE,0));
    NextMove = -1;
    Cost = 0;
}



GameState::GameState(const GameState &GS){

    Board.resize(BOARD_SIZE, std::vector<int>(BOARD_SIZE,0));
    for(int i=0;i<BOARD_SIZE;i++){
        for(int j=0;j<BOARD_SIZE;j++){
            Board[i][j] = GS.Board[i][j];
        }
    }

    NextMove = GS.NextMove;
    Cost = GS.Cost;
}


void GameState::InsertChar(int x, int y){

    if (x >= BOARD_SIZE || y >= BOARD_SIZE || x < 0 || y < 0) throw OUTSIDE_BOARD_ERR;

    if (Board[x][y] != 0) throw SPACE_TAKEN_ERR;

    Board[x][y] = NextMove;
}


void GameState::InsertBoard(GameState GS){
    for(int i=0;i<BOARD_SIZE;i++){
        for(int j=0;j<BOARD_SIZE;j++){
            Board[i][j] = GS.Board[i][j];
        }
    }
}


void GameState::DeleteChar(int x, int y){

    if (x >= BOARD_SIZE || y >= BOARD_SIZE || x < 0 || y < 0) throw OUTSIDE_BOARD_ERR;

    Board[x][y] = 0;
}


int GameState::CheckWinner(){

    for(int i=0;i<BOARD_SIZE;i++){
        for(int j=0;j<BOARD_SIZE;j++){
            if(Board[i][j] == Board[i][j+1]){
                if (j+2 == BOARD_SIZE) return Board[i][j];
                else continue;
            } else break;
        }
    }

    for(int i=0;i<BOARD_SIZE;i++){
        for(int j=0;j<BOARD_SIZE;j++){
            if(Board[j][i] == Board[j+1][i]){
                if (j+2 == BOARD_SIZE) return Board[j][i];
                else continue;
            } else break;
        }
    }

    for(int i=0; i<BOARD_SIZE;i++){
        if(Board[i][i] == Board[i+1][i+1]){
            if (i+2 == BOARD_SIZE) return Board[i][i];
            else continue;
        } else break;
    }

    for(int i=0; i<BOARD_SIZE;i++){
        if(Board[BOARD_SIZE-i-1][i] == Board[BOARD_SIZE-i-2][i+1]){
            if (i+2 == BOARD_SIZE) return Board[i][i];
            else continue;
        } else break;
    }


    for(int i=0; i<BOARD_SIZE;i++){
        for(int j=0; j<BOARD_SIZE;j++){
            if(Board[i][j] == 0) return 0;
        }
    }
    
    return DRAW;
}


int GameState::DetermineCost(){
    
    int* arr = new int[2*BOARD_SIZE + 2];
    int k=0;
    int draw = 0;

    for(int i=0; i<2*BOARD_SIZE+2;i++){
        arr[i] = 0;
    }

    for(int i=0;i<BOARD_SIZE;i++){
        for(int j=0;j<BOARD_SIZE;j++){
            if(arr[k] * Board[i][j] < 0){
                arr[k] = 0;
                draw++;
                break;
            }
            arr[k] += Board[i][j];
        }
        k++;
        
    }

    for(int i=0;i<BOARD_SIZE;i++){
        for(int j=0;j<BOARD_SIZE;j++){
            if(arr[k] * Board[j][i] < 0){
                arr[k] = 0;
                draw++;
                break;
            }
            arr[k] += Board[j][i];
        }
        k++;
    }

    for(int i=0;i<BOARD_SIZE;i++){
        if(arr[k] * Board[i][i] < 0){
            arr[k] = 0;
            draw++;
            break;
        }
        arr[k] += Board[i][i];
    }
    k++;

    for(int i=0;i<BOARD_SIZE;i++){
        if(arr[k] * Board[i][BOARD_SIZE-i-1] < 0){
            arr[k] = 0;
            draw++;
            break;
        }
        arr[k] += Board[i][BOARD_SIZE-i-1];
    }
    k++;

    int smallest = 0;
    int biggest = 0;

    for(int i=0; i<2*BOARD_SIZE+2;i++){
        if(arr[i] > biggest){
            biggest = arr[i];
            continue;
        }
        if(arr[i] < smallest){
            smallest = arr[i];
            continue;
        }
    }

    delete[] arr;

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



Dequeue<GameState> GameState::GeneratePossibleMoves() const{

    Dequeue<GameState> dequeue;  
    GameState GS_copy(*this);


    for(int i=0;i<BOARD_SIZE;i++){
        for(int j=0;j<BOARD_SIZE;j++){
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



bool GameState::operator== (const GameState &GS) const{

    if(Cost != GS.Cost || NextMove != GS.NextMove) return false;

    for(int i=0;i<BOARD_SIZE;i++){
        for(int j=0;j<BOARD_SIZE;j++){
            if (Board[i][j] != GS.Board[i][j]) return false;
        }
    }
    return true;
}