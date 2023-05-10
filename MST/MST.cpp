//
// Created by stani on 09.05.2023.
//

#include "MST.h"
#include "../structures/Queue.h"
#include<iostream>
#include <bits/stdc++.h>

using namespace std;

void MST::generateGraph() {
    srand(time(NULL));

    adjList = new AdjNode *[numOfEdges * (numOfVertexes - 1) / 2];
    int v1, v2, weight;
    int idFromGraph, idOutside;

    graph = new int *[numOfVertexes];

    for(int i =0; i< numOfVertexes; i++){
        graph[i] = new int [numOfVertexes];             // Tworzenie dwuwymiarowej tablicy
        adjList[i] = NULL;
        for(int j =0; j< numOfVertexes; j++){
            graph [i][j] = 0;                           // ustawiam w macierzy na brak relacji pomiedzy wierzcholkami
        }
    }

    int inGraph [numOfVertexes + 1];
    int notInGraph[numOfVertexes];

    inGraph [0] = 0;
    for(int i = 0; i<numOfVertexes-1; i++){
        notInGraph[i] = i+1;
    }

    for(int i = 0; i<numOfVertexes-1; i++){
        idFromGraph = rand()%(i + 1);                       //losuje id wierzcholka istniejacego w grafie
        idOutside = rand()%(numOfVertexes - i - 1);         // losuje id wierzcholka, ktory jeszcze nie zostal dodany
        v1 = inGraph[idFromGraph];                          //
        v2 = notInGraph[idOutside];
        weight = rand()%1000000 + 1;
        notInGraph[idOutside] = 0;                          // zaznaczam, że wierzcholek jest juz w grafie
        inGraph[i + 1] = v2;                                // dopisuje go do listy wierzcholkow w grafie na koniec

        sort(notInGraph, notInGraph + numOfVertexes - i - 1, greater<int>());       // Sortowanie malejące wierzchołków tzn. uzyte beda na koncu

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
// skonczone
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
    fin >> numOfEdges >> numOfVertexes;                 // wczytuje liczbe krawedzi i wierzcholkow do pola klasy

    adjList = new AdjNode * [numOfVertexes];

    graph = new int *[numOfVertexes];

    // TWORZE STRUKTURY I WYPELNIAM JE PUSTYMI WARTOSCIAMI
    for(int i =0; i< numOfVertexes; i++){
        graph[i] = new int [numOfVertexes];             // Tworzenie dwuwymiarowej tablicy - dokladanie drugiego wymiaru
        adjList[i] = NULL;
        for(int j =0; j< numOfVertexes; j++){
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
    for(int i = 0; i < numOfVertexes; i++){
        cout << setw(6) << i;                               // drukowanie numerow kolumn
    }
//    cout<<endl;
//    cout << setw(6) << " ";
//    for(int i = 0; i < numOfVertexes; i++){
//        cout << setfill('-');                               // drukowanie numerow kolumn
//    }

    cout<<endl;

    for(int i = 0; i < numOfVertexes; i++){
        cout << setw(6) << i;                               // drukowanie numerow wierszy
        for(int j = 0; j < numOfVertexes; j++){
            cout << setw(6) << graph [i] [j];
        }
        cout<<endl;
    }

}

//git
void MST::printAdjacencyList() {

    cout<<endl<<"ADJACENCY LIST"<<endl;
    cout<< "ID_OF_VERTEX:  ID_OF_VERTEX <WEIGHT_OF_EDGE>";
    for(int i = 0; i < numOfVertexes; i++){
        cout<<endl<< i << ": ";
        p = adjList[i];
        while(p){
            cout << setw(4) << p -> neighbour << " <" << p->weight << ">, ";
            p = p -> next;
        }
    }
    cout<<endl<<endl;
}

void MST::prim_matrix(){
    // wybieram jeden wierzcholek



//  WCZYTYWANIE DO KOLEJKI Z MACIERZY
    Queue *pq = new Queue();
    for(int i = 0; i < numOfVertexes; i++){
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
    pq->print();




}