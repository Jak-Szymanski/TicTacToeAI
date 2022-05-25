#include "field.h"
#include "graph.h"

int main(){

    typedef Graph<4> Graph4;

    GameState<4> tablica;
    int x;
    int y;
   
    Graph4 graph;
    tablica.InsertChar(0,0);
    
    while(1){
        std::cout << "Ruch gracza: " << std::endl;
        if (tablica.NextMove == -1) std::cout << "X";
        else std::cout << "O";
        
        std::cout << std::endl << "Podaj ruch" << std::endl;
        std::cin >> x;
        if(x == 10){
           //std::cout << graph << std::endl;
        } else {
        std::cin >> y;


        try {tablica.InsertChar(x,y);}
        catch (const int error_type){
            if (error_type == SPACE_TAKEN_ERR){
                std::cout << "Pole zajete, sprobuj jeszcze raz" << std::endl;
                continue;
            } 
            if(error_type == OUTSIDE_BOARD_ERR){
                std::cout << "Niepoprawne pole, sprobuj jeszcze raz" << std::endl;
                continue;
            }
        }

        graph.InsertVertex(tablica);
        std::cout << tablica << std::endl;
        if (tablica.CheckWinner() != 0){
            std::cout << "Wygrany!!! " << tablica.CheckWinner() << std::endl;
        }
        std::cout << "Koszt: " << tablica.DetermineCost() << std::endl;
        std::cout << std::endl;
        
        }
    }
}