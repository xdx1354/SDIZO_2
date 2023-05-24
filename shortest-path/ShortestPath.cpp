//
// Created by stani on 20.05.2023.
//

#include "ShortestPath.h"
#include "../structures/Queue.h"
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
                int n,d;
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
                    Dijkstra_matrix(startingPoint);
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
                    Dijkstra_list(startingPoint);
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
                    BellmanFord_matrix(startingPoint);
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
                    BellmanFord_list(startingPoint);
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
    numOfEdges = ((n*(n-1))/2 )*d;              // TODO: chyba bez /2 skoro skierowane krawedzi

    adjList = new AdjNode * [numOfVertices];

    graph = new int *[numOfVertices];

    /// TWORZE STRUKTURY I WYPELNIAM JE PUSTYMI WARTOSCIAMI
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

void ShortestPath::Dijkstra_list(int startingV) {

    long long* distance = new long long[numOfVertices];
    int* prev = new int[numOfVertices];
    bool* QS = new bool[numOfVertices];

    for (int i = 0; i < numOfVertices; ++i) {
        distance[i] = std::numeric_limits<long long>::max();
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
        if (distance[i] == std::numeric_limits<long long>::max()) {
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

void ShortestPath::Dijkstra_matrix(int startingV) {


    long long* distance = new long long[numOfVertices];
    int* prev = new int[numOfVertices];
    bool* QS = new bool[numOfVertices];

    for (int i = 0; i < numOfVertices; ++i) {
        distance[i] = std::numeric_limits<long long>::max();
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
        std::cout << "Shortest path from: " << startingV << " to: " << i << ": ";
        if (distance[i] == std::numeric_limits<long long>::max()) {
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

void ShortestPath::BellmanFord_matrix(int startingV) {

    long long* distance = new long long[numOfVertices];
    int* prev = new int[numOfVertices];

    for (int i = 0; i < numOfVertices; ++i) {
        distance[i] = 9999999;
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
        if (distance[i] == 9999999) {
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


void ShortestPath::BellmanFord_list(int startingV) {
    long long* distance = new long long[numOfVertices];
    int* prev = new int[numOfVertices];

    cout<<endl<<"Bellman-Ford algoritm (list)\n";

    for (int i = 0; i < numOfVertices; ++i) {
        distance[i] = 9999999;
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
        if (distance[i] == 9999999) {
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

void ShortestPath::printPath(int startingV) {

    int *S, stackCounter;

    S = new int[numOfVertices];
    stackCounter = 0;

    cout<<"Shortest paths from vertex "<<startingV<<endl;

    for(int i = 0; i<numOfVertices; i++){
        cout<< i <<": ";
        for(int j = i; j > -1; j=prev[j]){              // przechodze przez tablice poprzedników i dodaje
            S[stackCounter++] = j;                             // kolejne wierzchołki na stos
        }
        while (stackCounter){                                  // zdejmuje wierzchołki ze stosu w odwrotnej kolejności
            cout<< S[--stackCounter]<<" ";
        }
        cout<< "$"<< distance[i] << endl;
    }
}

