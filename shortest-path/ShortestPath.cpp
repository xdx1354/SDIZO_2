//
// Created by stani on 20.05.2023.
//

#include "ShortestPath.h"
#include "../structures/Queue.h"
#include "../util/Time.h"
#include<iostream>
#include <bits/stdc++.h>
using namespace std;


void ShortestPath::menu_Path() {

    cout<<"\nSHORTEST PATH\n";

    int x = -1;
    while(x!=0){
        cout<<"\n----------------------------------------------------\n";
        cout<<"1. Generate new random graph\n";
        cout<<"2. Generate new graph from file\n";
        cout<<"3. Test Dijkstra algorithm (Matrix)\n";
        cout<<"4. Test Dijkstra algorithm (Adjacency  list)\n";
        cout<<"5. Test Bellman-Ford algorithm (Matrix)\n";
        cout<<"6. Test Bellman-Ford algorithm (Adjacency  list)\n";
        cout<<"7. Print graph (as matrix and as adjacency list)\n";
        cout<<"0. Exit\n";
        cout<<"\nChoose task: \n";
        cin>>x;
        switch(x){
            default:{
                cout<<"Wrong number.\n";
                break;
            }
            case 0:{
                //eXIT

                break;
            }

            case 1:{
                int n;
                double d;
                cout<<"\nChoose number of vertices in graph: ";
                cin>>n;
                cout<<"\nChoose density of graph: ";
                cin>>d;
                generateGraph(n,d);
                break;
            }
            case 2:{
                generateGraphFromFile();
                cout<<"DONE";
                break;
            }
            case 3:{
                int startingPoint;
                cout<<"Choose starting vertex between 0 and " << numOfVertices-1 <<":";
                cin>>startingPoint;

                if(startingPoint<0 or startingPoint>numOfVertices-1){
                    cout<<"\nWrong parameter!!\n";
                }
                else{
                    dijkstraMatrix(startingPoint);
                }
                break;
            }
            case 4:{

                int startingPoint;
                cout<<"Choose starting vertex between 0 and " << numOfVertices-1 <<":";
                cin>>startingPoint;

                if(startingPoint<0 or startingPoint>numOfVertices-1){
                    cout<<"\nWrong parameter!!\n";
                }
                else{
                    dijkstraList(startingPoint);
                }
                break;

                break;
            }
            case 5:{
                int startingPoint;
                cout<<"Choose starting vertex between 0 and " << numOfVertices-1 <<":";
                cin>>startingPoint;

                if(startingPoint<0 or startingPoint>numOfVertices-1){
                    cout<<"\nWrong parameter!!\n";
                }
                else{
                    bellmanFordMatrix(startingPoint);
                }
                break;
                break;
            }
            case 6:{
                int startingPoint;
                cout<<"Choose starting vertex between 0 and " << numOfVertices-1 <<":";
                cin>>startingPoint;

                if(startingPoint<0 or startingPoint>numOfVertices-1){
                    cout<<"\nWrong parameter!!\n";
                }
                else{
                    bellmanFordList(startingPoint);
                }
                break;
                break;
            }
            case 7:{
                printAdjacencyList();
                printMatrix();
                break;
            }
        }
    }
}

void ShortestPath::generateGraphFromFile() {

        string fileName;

        cout<<"Prosze podac nazwe pliku: ";
        cin>>fileName;
        if( fileName[fileName.size()-1] != 't' or fileName[fileName.size()-2] != 'x' or fileName [fileName.size()-1] != 't' ){
            fileName = fileName + ".txt";
        }
        //NADPISUJE FILENAME DO TESTÓW!!!
        fileName = R"(D:\PWR\4 sem\SDIZO\Projekt2\dane.txt)";

        ifstream fin;

        fin.open(fileName.c_str(), ios::in);        // TODO: sprawdzic jak dziala dokladnie ten tryb
        fin >> numOfEdges >> numOfVertices;                 // wczytuje liczbe krawedzi i wierzcholkow do pola klasy

        adjList = new AdjNode * [numOfVertices];

        graph = new int *[numOfVertices];

        // TWORZE STRUKTURY I WYPELNIAM JE PUSTYMI WARTOSCIAMI
        for(int i =0; i < numOfVertices; i++){
            graph[i] = new int [numOfVertices];             // Tworzenie dwuwymiarowej tablicy - dokladanie drugiego wymiaru
            adjList[i] = NULL;
            for(int j =0; j < numOfVertices; j++){
                graph [i][j] = 0;                           // ustawiam w macierzy na brak relacji pomiedzy wierzcholkami
            }
        }

        // POBIERAM DANE Z PLIKU I WPISUJE DO STRUKTUR
        int v1, v2, weight;                                 // v1 - poczatkowy wierch, v2 - koncowy, weight - waga krawedzi


        for(int i = 0; i < numOfEdges; i++){
            fin >> v1 >> v2 >> weight;

            p = new AdjNode;                          // nowy element listy sasiadow - wierzcholek v1
            p -> neighbour = v2;                            // jego sasiadame jest wierzcholek v2
            p -> next = adjList[v1];                     // nastepny po nim jest ten element co byl pierwszy dotychczas
            p -> weight = weight;                           // ustawiam wage
            adjList [v1] = p;                            // wstawiam na pierwsze miejsce tzn, ze w adjList[] bedzie teraz wskaznik na niego

            // wpisuje wage w pola macierzy sasiedzctw
            graph[v1][v2] = weight;
        }
}

void ShortestPath::generateGraph(int n, double d) {
    if (d > 1 or d <= 0 or n<=0 ){
        cout<<"\n WRONG PARAMETERS!!";
        return;
    }
    cout<<"\nGenerating graph with "<<n<<" vertices and density" << d <<endl;
    srand(time(NULL));
    numOfVertices = n;
    density = d;
    numOfEdges = (n*(n-1))*d;
    int maxEdges = n*(n-1);

    adjList = new AdjNode * [numOfVertices];

    graph = new int *[numOfVertices];

/*    /// TWORZE STRUKTURY I WYPELNIAM JE PUSTYMI WARTOSCIAMI
    for(int i =0; i < numOfVertices; i++){
        graph[i] = new int [numOfVertices];             // Tworzenie dwuwymiarowej tablicy - dokladanie drugiego wymiaru
        adjList[i] = NULL;
        for(int j =0; j < numOfVertices; j++){
            graph [i][j] = 0;                           // ustawiam w macierzy na brak relacji pomiedzy wierzcholkami
        }
    }

    for(int i=0; i<numOfEdges; i++){

        int randWeight = rand() % 100000 + 1;
        int randV1 = rand() % numOfVertices;
        int randV2 = rand() % numOfVertices;
        bool tryAgain = false;

        do {
            tryAgain = false;
            if (randV1 != randV2 && graph[randV1][randV2] == 0) {                    // losuje do czasu gdy wylosuja sie dwa rozne

                graph[randV1][randV2] = randWeight;         //wstawiam do macierzy

                AdjNode *newNode = new AdjNode;                           // wstawiam do listy
                newNode->weight = randWeight;
                newNode->neighbour = randV2;
                newNode->next = adjList[randV1];
                adjList[randV1] = newNode;
                cout<<"\n Added:   V1: "<<randV1<<" V2:"<<randV2<<" weight:"<<randWeight;

            } else {
                srand(time(NULL));
                randV1 = rand() % numOfVertices;
                randV2 = rand() % numOfVertices;
                tryAgain = true;

            }
        } while(tryAgain);                 // do skutku probuje na nowo wygenerowac krawedzi

    }*/


    if(d>0.5){

        /// TWORZE STRUKTURY I WYPELNIAM JE PUSTYMI WARTOSCIAMI
        for(int i =0; i < numOfVertices; i++){
            graph[i] = new int [numOfVertices];             // Tworzenie dwuwymiarowej tablicy - dokladanie drugiego wymiaru
            adjList[i] = NULL;
            for(int j =0; j < numOfVertices; j++){
                if(i == j){
                    graph[i][j] = 0;                       // ustawiam na przekotnej brak relaci by wykluczyc petle
                }
                else{
                    graph [i][j] = -1;                           // ustawiam resztę pol macierzy na -1, by odróżnić je od braku relacji (infinity)
                }
            }
        }

        //cout<<"Po wstawieniu -1: ";
        //printMatrix();

        /// LOSUJE "PUSTE KRAWEDZI" I WSTAWIAM TAM INFINITY
        cout<<maxEdges <<" "<< numOfEdges;
        for(int i = 0; i < maxEdges-numOfEdges; i++) {
            int randV1 = rand() % numOfVertices;
            int randV2 = rand() % numOfVertices;
            bool tryAgain = false;
            do {
                tryAgain = false;
                if (randV1 != randV2 &&
                    graph[randV1][randV2] == -1) {                    // losuje do czasu gdy wylosuja sie dwa rozne

                    graph[randV1][randV2] = 0;

                    cout << "\n Udalo sie wstawic zero V1: " << randV1 << " V2:" << randV2;

                } else {
                    srand(time(NULL));
                    randV1 = rand() % numOfVertices;
                    randV2 = rand() % numOfVertices;
                    tryAgain = true;

                }
            } while (tryAgain);                 // do skutku probuje na nowo wygenerowac krawedzi
        }

        //cout<<"Po wstawieniu zer: ";
        //printMatrix();

        /// po wstawieniu wszystkich "braków krawedzi" wstawiam losowe krawedzi
        for(int x = 0; x<numOfVertices; x++){
            for(int y = 0; y<numOfVertices; y++){

                int randWeight = rand() % 100 + 1;

                if(graph[x][y] != 0){         // jesli dana krawedz nie jest okreslona jako pusta
                    graph[x][y] = randWeight;                                   // to tworzę tą relację

                    AdjNode *newNode1 = new AdjNode;                           // wstawiam do listy
                    newNode1->weight = randWeight;
                    newNode1->neighbour = y;
                    newNode1->next = adjList[x];
                    adjList[x] = newNode1;


                    cout<<"\n Wstawiono V1: "<<x<<" V2:"<<y<<" waga:"<<randWeight;
                }
            }


        }

    }
    else{

        /// TWORZE STRUKTURY I WYPELNIAM JE PUSTYMI WARTOSCIAMI
        for(int i =0; i < numOfVertices; i++){
            graph[i] = new int [numOfVertices];             // Tworzenie dwuwymiarowej tablicy - dokladanie drugiego wymiaru
            adjList[i] = NULL;
            for(int j =0; j < numOfVertices; j++){
                graph [i][j] = 0;                           // ustawiam w macierzy na brak relacji pomiedzy wierzcholkami
            }
        }

        // generowanie grafu dla d<=0.5
        for(int i=0; i<numOfEdges; i++){

            int randWeight = rand() % 100 + 1;
            int randV1 = rand() % numOfVertices;
            int randV2 = rand() % numOfVertices;
            bool tryAgain = false;

            do {
                tryAgain = false;
                if (randV1 != randV2 && graph[randV1][randV2] == 0) {                    // losuje do czasu gdy wylosuja sie dwa rozne

                    graph[randV1][randV2] = randWeight;         //wstawiam do macierzy



                    AdjNode *newNode1 = new AdjNode;                           // wstawiam do listy
                    newNode1->weight = randWeight;
                    newNode1->neighbour = randV2;
                    newNode1->next = adjList[randV1];
                    adjList[randV1] = newNode1;

                    cout<<"\n Wstawiono. V1: "<<randV1<<" V2:"<<randV2<<" waga:"<<randWeight;

                } else {
                    srand(time(NULL));
                    randV1 = rand() % numOfVertices;
                    randV2 = rand() % numOfVertices;
                    tryAgain = true;

                }
            } while(tryAgain);                 // do skutku probuje na nowo wygenerowac krawedzi

        }

    }


}

void ShortestPath::printAdjacencyList() {

    cout<<endl<<"ADJACENCY LIST"<<endl;
    cout<< "ID_OF_VERTEX:  ID_OF_VERTEX <WEIGHT_OF_EDGE>";
    for(int i = 0; i < numOfVertices; i++){
        cout<<endl<< i << ": ";
        p = adjList[i];
        while(p){
            cout << setw(4) << p -> neighbour << " <" << p->weight << ">, ";
            p = p -> next;
        }
    }
    cout<<endl<<endl;
}

void ShortestPath::printMatrix() {

    cout<<endl<<"ADJACENCY MATRIX"<<endl;
    cout << setw(6) << " ";
    for(int i = 0; i < numOfVertices; i++){
        cout << setw(6) << i;                               // drukowanie numerow kolumn
    }

    cout<<endl;

    for(int i = 0; i < numOfVertices; i++){
        cout << setw(6) << i;                               // drukowanie numerow wierszy
        for(int j = 0; j < numOfVertices; j++){
            cout << setw(6) << graph [i] [j];
        }
        cout<<endl;
    }
    cout<<endl<<endl;

}

void ShortestPath::dijkstraList(int startingV) {

    long long* distance = new long long[numOfVertices];
    int* prev = new int[numOfVertices];
    bool* QS = new bool[numOfVertices];

    for (int i = 0; i < numOfVertices; ++i) {
        distance[i] = 99999999999999;
        prev[i] = -1;
        QS[i] = false;
    }

    distance[startingV] = 0;

    for (int i = 0; i < numOfVertices; ++i) {
        int u = -1;
        for (int j = 0; j < numOfVertices; ++j) {
            if (!QS[j] && (u == -1 || distance[j] < distance[u])) {
                u = j;
            }
        }

        QS[u] = true;

        for (int v = 0; v < numOfVertices; ++v) {

            AdjNode *firstNode = adjList[u];        // biore pierwsza krawedz
            while(firstNode != nullptr && firstNode->neighbour != v ) {            // petla iterujaca po wszystkich krawdziach tego wierzchołka
                firstNode = firstNode->next;
            }
            if(firstNode != nullptr){           // jesli znaleziono taka krawedz
                if (!QS[v] && (distance[v] > distance[u] + firstNode->weight)) {
                    distance[v] = distance[u] + firstNode->weight;
                    prev[v] = u;
                }
            }
        }
    }

    cout<<endl<<endl;
    for (int i = 0; i < numOfVertices; ++i) {
        std::cout << "Shortest path from: " << startingV << " to: " << i << ": ";
        if (distance[i] == 99999999999999) {
            std::cout << "NO PATH" << std::endl;
        } else {
            std::cout << distance[i] << " (previous: ";
            int current = i;
            while (current != -1) {
                std::cout << current << " ";
                current = prev[current];
            }
            std::cout << ")" << std::endl;
        }
    }
    cout<<"\n\n";
    delete[] distance;
    delete[] prev;
    delete[] QS;


}

void ShortestPath::dijkstraMatrix(int startingV) {


    long long* distance = new long long[numOfVertices];
    int* prev = new int[numOfVertices];
    bool* QS = new bool[numOfVertices];

    for (int i = 0; i < numOfVertices; ++i) {
        distance[i] = 99999999999999;
        prev[i] = -1;
        QS[i] = false;
    }

    distance[startingV] = 0;

    for (int i = 0; i < numOfVertices; ++i) {
        int u = -1;
        for (int j = 0; j < numOfVertices; ++j) {
            if (!QS[j] && (u == -1 || distance[j] < distance[u])) {
                u = j;
            }
        }

        QS[u] = true;

        for (int v = 0; v < numOfVertices; ++v) {
            if (graph[u][v] != 0 && !QS[v] && (distance[v] > distance[u] + graph[u][v])) {
                distance[v] = distance[u] + graph[u][v];
                prev[v] = u;
            }
        }
    }

    cout<<endl<<endl;

    // Wyświetlenie najkrótszych ścieżek
    for (int i = 0; i < numOfVertices; ++i) {
        cout << "Shortest path from: " << startingV << " to: " << i << ": ";
        if (distance[i] == 99999999999999) {
            std::cout << "NO PATH" << endl;
        } else {
            cout << distance[i] << " (previous: ";
            int current = i;
            while (current != -1) {
                std::cout << current << " ";
                current = prev[current];
            }
            cout << ")" << endl;
        }
    }
    cout<<"\n\n";
    delete[] distance;
    delete[] prev;
    delete[] QS;


}

void ShortestPath::bellmanFordMatrix(int startingV) {

    long long* distance = new long long[numOfVertices];
    int* prev = new int[numOfVertices];

    for (int i = 0; i < numOfVertices; ++i) {
        distance[i] = 99999999999999;
        prev[i] = -1;
    }

    distance[startingV] = 0;

    for (int i = 1; i < numOfVertices; i++) {

        for (int u = 0; u < numOfVertices; u++) {
            for (int v = 0; v < numOfVertices; v++) {
                if (graph[u][v] != 0 && distance[v] > distance[u] + graph[u][v]) {
                    distance[v] = distance[u] + graph[u][v];
                    // cout<<"dystans dla: " <<v<<" to teraz " <<distance[v]<<endl;
                    prev[v] = u;
                }
            }
        }
    }


    cout<<endl<<endl;

    for (int i = 0; i < numOfVertices; ++i) {
        std::cout << "Shortest path from: " << startingV << " to: " << i << ": ";
        if (distance[i] == 99999999999999) {
            std::cout << "NO PATH" << std::endl;
        } else {
            std::cout << distance[i] << " (previous: ";
            int current = i;
            while (current != -1) {
                std::cout << current << " ";
                current = prev[current];
            }
            std::cout << ")" << std::endl;
        }
    }

    delete[] distance;
    delete[] prev;
}


void ShortestPath::bellmanFordList(int startingV) {
    long long* distance = new long long[numOfVertices];
    int* prev = new int[numOfVertices];

    cout<<endl<<"Bellman-Ford algoritm (list)\n";

    for (int i = 0; i < numOfVertices; ++i) {
        distance[i] = 99999999999999;
        prev[i] = -1;
    }

    distance[startingV] = 0;

    for (int i = 1; i < numOfVertices; i++) {
        for (int u = 0; u < numOfVertices; u++) {
            for (int v = 0; v < numOfVertices; v++) {

                AdjNode *firstNode = adjList[u];        // biore pierwsza krawedz
                while (firstNode != nullptr && firstNode->neighbour !=
                                               v) {            // petla iterujaca po wszystkich krawdziach tego wierzchołka
                    firstNode = firstNode->next;
                }
                if (firstNode != nullptr) {           // jesli znaleziono taka krawedz
                    if ((distance[v] > distance[u] + firstNode->weight)) {
                        distance[v] = distance[u] + firstNode->weight;
                        prev[v] = u;
                    }
                }
            }
        }
    }


    cout<<endl<<endl;

    for (int i = 0; i < numOfVertices; ++i) {
        std::cout << "Shortest path from: " << startingV << " to: " << i << ": ";
        if (distance[i] == 99999999999999) {
            std::cout << "NO PATH" << std::endl;
        } else {
            std::cout << distance[i] << " (previous: ";
            int current = i;
            while (current != -1) {
                std::cout << current << " ";
                current = prev[current];
            }
            std::cout << ")" << std::endl;
        }
    }
    cout<<"\n\n";
    delete[] distance;
    delete[] prev;


}



/// UTIL FUNCTIONS

void ShortestPath::autoTest() {
    string path = R"(D:\PWR\4 sem\SDIZO\Projekt2\tests\tests2.txt)";
    ofstream fout(path);
    Time myTime;
    srand(time(NULL));
    int numOfTests = 10;
    cout<<"Starting test of Shortest Path";
    fout<<"----Test of Shortest Path----\n";
    fout<<"Dijkstra_matrix Dijkstra_list BF_matrix BF_list\n";

    for(int i = 2; i<=10; i = i+2){
        numOfVertices = i * 10;
        double list[4] = {0.25, 0.5, 0.75,0.99};        ///0.5, 0.75, 0.99
        for(double elem : list){

            cout<<"\nStarting test numOfVertices = "<<numOfVertices<<", Density = "<<elem<<endl;
            fout<<"\n\nTesting with params:\nNumber of Vertices = " << numOfVertices;
            fout<<", Density = "<<elem<<"\n\n";
            generateGraph(numOfVertices, elem);                //gerowanie grafu o konkretnych parametrach

            long long tempTime = 0;
            for(int j=0; j<numOfTests; j++){

                int startingV = rand()%numOfVertices+1;
                myTime.start();
                cout<<"\n\nDijkstra Matrix\n";
                dijkstraMatrix(startingV);
                myTime.stop();
                tempTime+= myTime.returnTime() / numOfTests;

            }
//            fout<<"Dijkstra (matrix) avg myTime: " << tempTime<<endl;
            fout<<tempTime<<" ";
            cout<<"Dijkstra (matrix) avg myTime: " << tempTime<<endl;



            tempTime = 0;
            for(int j=0; j<numOfTests; j++){

                int startingV = rand()%numOfVertices+1;
                myTime.start();
                cout<<"\n\nDijkstra list\n";
                dijkstraList(startingV);
                myTime.stop();
                tempTime+= myTime.returnTime() / numOfTests;

            }
//            fout<<"Dijkstra (list) avg myTime: " << tempTime<<endl;
            fout<<tempTime<<" ";
            cout<<"Dijkstra (list) avg myTime: " << tempTime<<endl;

            tempTime = 0;
            for(int j=0; j<numOfTests; j++){

                int startingV = rand()%numOfVertices+1;
                myTime.start();
                cout<<"\n\nBellman-Ford matrix\n";
                bellmanFordMatrix(startingV);
                myTime.stop();
                tempTime+= myTime.returnTime() / numOfTests;

            }
//            fout<<"Bellman-Ford (matrix) avg myTime: " << tempTime<<endl;
            fout<<tempTime<<" ";
            cout<<"Bellman-Ford (matrix) avg myTime: " << tempTime<<endl;


            tempTime = 0;
            for(int j=0; j<numOfTests; j++){

                int startingV = rand()%numOfVertices+1;
                myTime.start();
                cout<<"\n\nBellman-Ford list\n";
                bellmanFordList(startingV);
                myTime.stop();
                tempTime+= myTime.returnTime() / numOfTests;

            }
//            fout<<"Bellman-Ford (list) avg myTime: " << tempTime<<endl;
            fout<<tempTime<<endl;
            cout<<"Bellman-Ford (list) avg myTime: " << tempTime<<endl;


        }

    }


}
