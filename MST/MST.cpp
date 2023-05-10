//
// Created by stani on 09.05.2023.
//

#include "MST.h"
#include "../structures/Queue.h"
#include<iostream>
#include <bits/stdc++.h>

using namespace std;

//TODO:
void MST::generateGraph() {
    srand(time(NULL));

    adjList = new AdjNode *[numOfEdges * (numOfVertices - 1) / 2];
    int v1, v2, weight;
    int idFromGraph, idOutside;

    graph = new int *[numOfVertices];

    for(int i =0; i < numOfVertices; i++){
        graph[i] = new int [numOfVertices];             // Tworzenie dwuwymiarowej tablicy
        adjList[i] = NULL;
        for(int j =0; j < numOfVertices; j++){
            graph [i][j] = 0;                           // ustawiam w macierzy na brak relacji pomiedzy wierzcholkami
        }
    }

    int inGraph [numOfVertices + 1];
    int notInGraph[numOfVertices];

    inGraph [0] = 0;
    for(int i = 0; i < numOfVertices - 1; i++){
        notInGraph[i] = i+1;
    }

    for(int i = 0; i < numOfVertices - 1; i++){
        idFromGraph = rand()%(i + 1);                       //losuje id wierzcholka istniejacego w grafie
        idOutside = rand()%(numOfVertices - i - 1);         // losuje id wierzcholka, ktory jeszcze nie zostal dodany
        v1 = inGraph[idFromGraph];                          //
        v2 = notInGraph[idOutside];
        weight = rand()%1000000 + 1;
        notInGraph[idOutside] = 0;                          // zaznaczam, że wierzcholek jest juz w grafie
        inGraph[i + 1] = v2;                                // dopisuje go do listy wierzcholkow w grafie na koniec

        sort(notInGraph, notInGraph + numOfVertices - i - 1, greater<int>());       // Sortowanie malejące wierzchołków tzn. uzyte beda na koncu

        graph[v1][v2] = weight;
        graph[v2][v1] = weight;                             // dopisywanie wagi do macierzy sąsiedzctw

        p = new AdjNode;                              //dopisywanie v1
        p -> neighbour = v2;
        p -> next = adjList[v1];
        p -> weight = weight;
        adjList[v1] = p;

        p = new AdjNode;                              //dopisywanie v1
        p -> neighbour = v1;
        p -> next = adjList[v2];
        p -> weight = weight;
        adjList[v2] = p;
    }

    // TODO: dokonczyc i przeanalizowac dzialanie algorytmu

}

//git
void MST::generateGraphFromFile() {

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

        p = new AdjNode;                          // analogicznie tworze relacje dla v2
        p -> neighbour = v1;
        p -> next = adjList[v2];
        p -> weight = weight;
        adjList[v2] = p;

        // wpisuje wage w pola macierzy sasiedzctw
        graph[v1][v2] = weight;
        graph[v2][v1] = weight;

    }
}

//git
void MST::printMatrix() {

    cout<<endl<<"ADJACENCY MATRIX"<<endl;
    cout << setw(6) << " ";
    for(int i = 0; i < numOfVertices; i++){
        cout << setw(6) << i;                               // drukowanie numerow kolumn
    }
//    cout<<endl;
//    cout << setw(6) << " ";
//    for(int i = 0; i < numOfVertices; i++){
//        cout << setfill('-');                               // drukowanie numerow kolumn
//    }

    cout<<endl;

    for(int i = 0; i < numOfVertices; i++){
        cout << setw(6) << i;                               // drukowanie numerow wierszy
        for(int j = 0; j < numOfVertices; j++){
            cout << setw(6) << graph [i] [j];
        }
        cout<<endl;
    }

}

//git
void MST::printAdjacencyList() {

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

//git
void MST::prim_matrix(){

///  WCZYTYWANIE DO KOLEJKI Z MACIERZY
    Queue *pq = new Queue();
    for(int i = 0; i < numOfVertices; i++){
        for(int j = 0; j < i; j++){
            if(graph[i][j] != 0){
                Queue::Edge temp;
                temp.v1 = i;
                temp.v2 = j;
                temp.weight = graph[i][j];
                pq->insert(temp);
            }
        }
    }
/// PRZYGOTOWYWANIE TABLICY DO SPRAWDZANIA PĘTLI W GRAFIE - DISJOINT SETS
    int* parent = new int[numOfVertices];
    fill(parent, parent + numOfVertices, -1);

/// WYBIERANIE POCZĄTKOWEGO WIERZCHOŁKA OD KTÓREGO ZACZYNA SIE ALGORYTM (NA BAZIE KRAWĘDZI O NAJMNIEJSZEJ WADZE)
    Queue::Node* firstNode = pq->head;                                       // losowa krawędzi
    int parent1 = findParent(firstNode->data.v1, parent);              // szukam korzenia poddrzewa, do którego należy v1
    int parent2 = findParent(firstNode->data.v2, parent);              // szukam korzenia poddrzewa, do którego należy v2
    unionSets(parent1, parent2, parent);                              // pierwszy set, parent2 będzie rodzicem całości
    int permParent = parent2;                                                // permParent to rodzic naszego poddrzewa rozpinającego
    cout << "Edge: " << firstNode->data.v1 << " - " << firstNode->data.v2 << ", weight: " << firstNode->data.weight <<endl;

    /// GŁOWNA CZEŚĆ FUNKCJI,
    for(int i = 1; i < numOfVertices - 1; i++){                             // wyszukiwanie określonej liczby krawędzi
        Queue::Node* currentNode = pq->head;
        while(currentNode != nullptr){                                      // znalezienie najmniejszej krawędzi, która nam pasuje
            parent1 = findParent(currentNode->data.v1, parent);       //szukam korzenia poddrzewa, do którego należy v1
            parent2 = findParent(currentNode->data.v2, parent);       //szukam korzenia poddrzewa, do którego należy v2

            if(parent1 != parent2 && (parent2 == permParent || parent1 == permParent )){            //sprawdza, nie ma pętli i czy krawedz jest sasiadujaca z drzewem co mam do tej pory
                cout << "Edge: " << currentNode->data.v1 << " - " << currentNode->data.v2 << ", weight: " << currentNode->data.weight <<endl;
                unionSets( parent1, parent2, parent);
                break;
            }
            currentNode  = currentNode -> next;
        }
    }
    delete[] parent;
}

//TODO:
void MST::prim_list() {

    // Zamiana listy na kolejkę, reszta analogicznie
}

//git
void MST::kruskal_matrix() {


    Queue *pq = new Queue();                    // tworze posortowana kolejkę krawedzi
    for(int i = 0; i < numOfVertices; i++){
        for(int j = 0; j < i; j++){
            if(graph[i][j] != 0){
                Queue::Edge temp;
                temp.v1 = i;
                temp.v2 = j;
                temp.weight = graph[i][j];
                pq->insert(temp);
            }
        }
    }


    int* parent = new int[numOfVertices];
    fill(parent, parent + numOfVertices, -1);     //wypełaniam tablice -1 tzn ze dany wierzcholek jest
                                                                 // korzeniem poddrzewa (poki co)
    // GLOWNY ALGORYTM
    int edgeCount = 0;
    while(edgeCount < numOfVertices - 1){
        Queue::Edge currentEdge = pq -> head -> data;           // pobieram krawedz o najmniejszej wadze
        pq -> deleteFromBeginning();                            // usuwam ja z kolejki

        int parent1 = findParent(currentEdge.v1, parent);       //szukam korzenia poddrzewa, do którego należy v1
        int parent2 = findParent(currentEdge.v2, parent);       //szukam korzenia poddrzewa, do którego należy v2

        if(parent1 != parent2){
            cout << "Edge: " << currentEdge.v1 << " - " << currentEdge.v2 << ", weight: " << currentEdge. weight <<endl;
            unionSets( parent1, parent2, parent);
            edgeCount++;
        }
    }

    delete[] parent;                   // usuwam tablice, bo nie bedzie juz potrzebna
}

//TODO:
void MST::kruskal_list() {

    Queue *pq = new Queue();                    // tworze posortowana kolejkę krawedzi

    for(int i=0; i<numOfVertices; i++){         // iteruje po wierzchołkach
        AdjNode *firstNode = adjList[i];        // biore pierwsza krawedz
        while(firstNode != nullptr){            // petla iterujaca po wszystkich krawdziach tego wierzchołka
            Queue::Edge e;                      // nowa krawedz do dodania do kolejki
            e.v1 = i;
            e.v2 = firstNode -> neighbour;
            e.weight = firstNode -> weight;

            Queue::Node *tmp = pq -> head;      // zmienna pomocnicza do przeszukiwania kolejki
            bool present = false;
            while(tmp != nullptr){              //przesukuje kolejke by sprawdzic czy nie mam tej krawedzi, ale w druga strone
                if((tmp->data.v2 == e.v2 && tmp->data.v1 == e.v1)||(tmp->data.v2 == e.v1 && tmp->data.v1 == e.v2)){
                    present = true;             // jesli jest juz to wychodzimy
                    break;
                }
                tmp = tmp -> next;              // przechodze do kolejnego elementu kolejki
            }
            if(!present){
                pq->insert(e);                  // jesli nie ma to dodajemy
            }
            firstNode = firstNode -> next;      // i przechodzimy do kolejnej krawedzi dla tego wierzcholka
        }
    }

    int* parent = new int[numOfVertices];
    fill(parent, parent + numOfVertices, -1);     //wypełaniam tablice -1 tzn ze dany wierzcholek jest
    // korzeniem poddrzewa (poki co)
    // GLOWNY ALGORYTM
    int edgeCount = 0;
    while(edgeCount < numOfVertices - 1){
        Queue::Edge currentEdge = pq -> head -> data;           // pobieram krawedz o najmniejszej wadze
        pq -> deleteFromBeginning();                            // usuwam ja z kolejki

        int parent1 = findParent(currentEdge.v1, parent);       //szukam korzenia poddrzewa, do którego należy v1
        int parent2 = findParent(currentEdge.v2, parent);       //szukam korzenia poddrzewa, do którego należy v2

        if(parent1 != parent2){
            cout << "Edge: " << currentEdge.v1 << " - " << currentEdge.v2 << ", weight: " << currentEdge. weight <<endl;
            unionSets( parent1, parent2, parent);
            edgeCount++;
        }
    }

    delete[] parent;                   // usuwam tablice, bo nie bedzie juz potrzebna
}



/*
UTIL FUNCTIONS
*/

int MST::findParent(int vertex, int* parent){                //rekurencyjne wyszukiwanie korznienia dzrzewa
    if( parent [vertex] == -1 )
        return  vertex;
    return findParent(parent[vertex], parent);
}

void MST::unionSets(int v1, int v2, int* parent){            //laczenie dwóch poddrzew
    int parent1 = findParent(v1, parent);
    int parent2 = findParent(v2, parent);
    parent[parent1] = parent2;                      //przypisanie korzenia jednego poddrzewa do drugiego
}