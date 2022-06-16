#include "../inc/adjlistgraph.h"
#include "../inc/adjmatrixgraph.h"
//#include "../inc/gamestategraph.h"

#include <windows.h>
#include <chrono>

int main(){
 
    srand(time(NULL));
    int x;
    int y;
    int* alpha = new int(100);
    int* beta = new int(-100);
    int test;

    std::cout << "test? " << std::endl;
    std::cin >> test;



    if(test == 1){

    // std::ofstream output_file("graph.csv");
    // std::ofstream output_file("adjlistgraph.csv");
    std::ofstream output_file("adjmatgraph.csv");

            // AdjacencyListGraph<int> testgraph;
        AdjacencyMatrixGraph<int> testgraph;
        // Graph<int> testgraph;

    output_file << "gestosc,ilosc wierzcholkow,ilosc krawedzi,IncidentEdges,AreAdjacent,InsertVertex,InsertEdge,RemoveVertex,RemoveEdge" << std::endl;

    Vertex<int> *V1, *V2, *V3, *V4, *V5, *V6, *V7, *V8;
    Edge<int>* E1, *E2;
    int n = 0;
    int num_vert[5] = {24,48,100,240,480};
    int off[4] = {3,2,1,0};             //tablice off i on decyduja o gestosci grafu
    int on[4] = {1,2,3,4};              //on[0],off[0] -> 25%; num[1],num[1] -> 50%, dla 3 -> 75%, dla 4 -> 100%
    int random_int;
    float incident_edges = 0;
    float are_adjacent = 0;
    float insert_vertex = 0;
    float insert_edge = 0;
    float remove_edge = 0;
    float remove_vertex = 0;
    int num_tests = 100;
    int num_vertices;
    int num_edges;

    for(int l=0; l<4; l++){                     //różne gestosci

        for(int k=0; k<5; k++){                      //różne wielkości grafu
                incident_edges = 0;
                are_adjacent = 0;
                insert_vertex = 0;
                insert_edge = 0;
                remove_edge = 0;
                remove_vertex = 0;
                        

            for(int j=0; j<num_tests; j++){     //po 100 testów
                n=0;
                //Graph<int> testgraph = Graph<int>();
                while(n < num_vert[k]){         //pętla aż dojdziemy do danej wielkosci grafu
                    for(int i=0; i<off[l]; i++){                 
                        random_int = rand() % 10;
                        testgraph.InsertVertex(random_int);
                        //std::cout << testgraph << std::endl;

                        n++;
                        //std::cout << *testgraph.Vertices();
                    }
                    for(int i=0; i<on[l]; i++){
                        random_int = rand() % 10;
                        V1 = testgraph.InsertVertex(random_int);
                        n++;

                        Node<Vertex<int>*>* ptr = testgraph.Vertices()->GetHead();      //ostatnio dodany wierzchołek połącz z każdym innym wierzchołkiem
                        while(ptr!=NULL){
                            V2 = ptr->GetElem();
                            if( V1 != V2){
                                random_int = rand() % 10;
                                testgraph.InsertEdge(random_int, V1, V2);
                            }
                        ptr = ptr->GetNext();
                    }
                }
            }
    
            num_vertices = testgraph.NumberVertices();
            //std::cout << num_vertices << std::endl;
            num_edges = testgraph.NumberEdges();

            V1 = testgraph.Vertices()->GetRandomElem();
            V2 = testgraph.Vertices()->GetRandomElem();

            auto start = std::chrono::steady_clock::now();
            testgraph.IncidentEdges(V1);
            // std::cout << "1" << std::endl;
             auto end = std::chrono::steady_clock::now();
            incident_edges += std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();

            start = std::chrono::steady_clock::now();
            testgraph.AreAdjacent(V1, V2);
                        // std::cout << "1" << std::endl;
            end = std::chrono::steady_clock::now();
            are_adjacent += std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();

            start = std::chrono::steady_clock::now();
            V3 = testgraph.InsertVertex(1);
                        // std::cout << "1" << std::endl;
            end = std::chrono::steady_clock::now();
            insert_vertex += std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();

            start = std::chrono::steady_clock::now();
            E1 = testgraph.InsertEdge(1,V1,V3);
                        // std::cout << "1" << std::endl;
            end = std::chrono::steady_clock::now();
            insert_edge += std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();

            start = std::chrono::steady_clock::now();
            testgraph.RemoveEdge(E1);
                        std::cout << "3" << std::endl;
            end = std::chrono::steady_clock::now();
            remove_edge += std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();

            start = std::chrono::steady_clock::now();
            testgraph.RemoveVertex(V2);
                        std::cout << "2" << std::endl;
            end = std::chrono::steady_clock::now();
            remove_vertex += std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();


            testgraph.Delete();
                std::cout << "delete";
            }
            // std::cout << "przed  "  << testgraph << std::endl << std::endl ;
           //testgraph.Delete();
            // std::cout << "po     " << testgraph << std::endl << std::endl;
             
            output_file << (float)(2*num_edges)/(num_vertices*(num_vertices-1)) << "," << num_vertices << "," << num_edges << ",";
            output_file << incident_edges/num_tests << "," << are_adjacent/num_tests << "," << insert_vertex/num_tests << "," << insert_edge/num_tests << ",";
            output_file << remove_vertex/num_tests << "," << remove_edge/num_tests << std::endl;
        }
    }   
    


    } else{

    auto V1 = new Vertex<GameState>(); 
                             auto V2 = new Vertex<GameState>();  
    auto Vdelete = new Vertex<GameState>();  

    Graph<GameState> graph;
    // AdjacencyListGraph<GameState> graph;
    // AdjacencyMatrixGraph<GameState> graph;

    std::cout << "Podaj rozmiar planszy: " << std::endl;
    std::cin >> BOARD_SIZE;


    GameState tablica;

    
    while(1){
        std::cout << "Ruch gracza: " << std::endl;
        if (tablica.GetNextMove() == -1) {
            std::cout << "X";
            std::cout << std::endl << "Podaj ruch" << std::endl;

            std::cin >> x;
            std::cin >> y;
            try {tablica.MakeMove(x,y);}
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


/*             std::shared_ptr<Edge<GameState>> E;
            V1 = graph.InsertVertex(tablica);
            tablica.MakeMove(2,2);
            Vdelete = graph.InsertVertex(tablica);
            graph.InsertEdge(1, V1, Vdelete);

            V1 = graph.InsertVertex(tablica);
            tablica.MakeMove(0,0);
            V2 = graph.InsertVertex(tablica);
            graph.InsertEdge(1, V1, V2);
            
            V1= graph.InsertVertex(tablica);
            tablica.MakeMove(0,2);
            V2 = graph.InsertVertex(tablica);
            E = graph.InsertEdge(1, V1, V2); */

            
            //graph.RemoveVertex(Vdelete);
            // std::cout << graph;

            // return 0;

            //std::cout << std::endl << std::endl << std::endl << *graph.Edges();
            
            // return 0;

            auto start = std::chrono::steady_clock::now();
            graph.CreateFutureMovesTree(V1, SEARCH_DEPTH); 
                //std::cout << graph;
            graph.Minimax(V1, alpha, beta);
            auto end = std::chrono::steady_clock::now();
            std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count() << std::endl;

            tablica.InsertBoard(graph.GetMaxMove(V1)); 
            tablica.ChangeMove();   
                                                                            // graph.Delete();

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
    }
}
