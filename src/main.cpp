#include "../inc/graph.h"

#include <chrono>

int main(){
 
    int x;
    int y;
    int* alpha = new int(100);
    int* beta = new int(-100);

    Vertex *V1 = new Vertex();
    Graph graph;


    std::cout << "Podaj rozmiar planszy: " << std::endl;
    std::cin >> BOARD_SIZE;


    GameState tablica;
    std::cout << tablica;
    
    while(1){
        std::cout << "Ruch gracza: ";
        if (tablica.GetNextMove() == -1) {
            std::cout << "X";
            std::cout << std::endl << "Podaj wiersz" << std::endl;
            std::cin >> x;
            std::cout << std::endl << "Podaj kolumne" << std::endl;
            std::cin >> y;

            try {tablica.MakeMove(x-1,y-1);}
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

            tablica.ChangeMove();
            tablica.DetermineCost();
        }
        else{
            std::cout << "O";
            std::cout << std::endl << "Ruch komputera: " << std::endl;
            V1 = graph.InsertVertex(tablica);
            //auto start = std::chrono::steady_clock::now(); //zacznij timer
	    graph.CreateFutureMovesTree(V1, SEARCH_DEPTH); 
            graph.Minimax(V1, alpha, beta);
            //auto end = std::chrono::steady_clock::now();  //zakoncz timer
            //std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count() << std::endl;   //mozliwosc sprawdzenia czasu trwania przeszukiwania

            tablica.InsertBoard(graph.GetMaxMove(V1)); 
            tablica.ChangeMove();      

        } 

        std::cout << tablica << std::endl;
        int result = tablica.CheckWinner();
        if (result == 1){
            std::cout << "Wygrany: Komputer " << std::endl;
            break;
        } 
        if (result == -1){
            std::cout << "Wygrany: Gracz " << std::endl;
            break;
        }
        if (result == DRAW){
            std::cout << "Remis! " << std::endl;
            break;
        }        
    }
    delete alpha;
    delete beta;
    delete V1;
}
