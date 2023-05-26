//
// Created by stani on 09.05.2023.
//

#include "MST.h"
#include "../structures/Queue.h"
#include "../util/Time.h"
#include<iostream>
#include <bits/stdc++.h>

using namespace std;

void MST::menu_MST() {

    cout<<"\n\nMENU MST\n\n";

    int x = -1;
    while(x!=0){
        cout<<"\n------------------------------------------------------\n";
        cout<<"1. Generate new random graph\n";
        cout<<"2. Generate new graph from file\n";
        cout<<"3. Test Prim algorithm (Matrix)\n";
        cout<<"4. Test Prim algorithm (Adjacency  list)\n";
        cout<<"5. Test Kruskal algorithm (Matrix)\n";
        cout<<"6. Test Kruskal algorithm (Adjacency  list)\n";
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
                cout<<"DONE";
                break;
            }
            case 2:{
                generateGraphFromFile();
                cout<<"DONE";
                break;
            }
            case 3:{
                prim_matrix();
                break;
            }
            case 4:{
                prim_list();
                break;
            }
            case 5:{
                kruskal_matrix();

                break;
            }
            case 6:{
                kruskal_list();
                break;
            }
            case 7:{
                printAdjacencyList();
                printMatrix();
                break;;
            }
        }
    }

}

void MST::generateGraph(int n, double d) {
    cout<<"\n\n";
    srand(time(NULL));
    numOfVertices = n;
    density = d;
    numOfEdges = ((n*(n-1))/2 )*d;

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

        int randWeight = rand() % 100 + 1;
        int randV1 = rand() % numOfVertices;
        int randV2 = rand() % numOfVertices;
        bool tryAgain = false;

        do {
            tryAgain = false;
            if (randV1 != randV2 && graph[randV1][randV2] == 0) {                    // losuje do czasu gdy wylosuja sie dwa rozne

                graph[randV1][randV2] = randWeight;         //wstawiam do macierzy
                graph[randV2][randV1] = randWeight;


                AdjNode *newNode1 = new AdjNode;                           // wstawiam do listy
                newNode1->weight = randWeight;
                newNode1->neighbour = randV2;
                newNode1->next = adjList[randV1];
                adjList[randV1] = newNode1;

                AdjNode *newNode2 = new AdjNode;                           // wstawiam do listy
                newNode2->weight = randWeight;
                newNode2->neighbour = randV1;
                newNode2->next = adjList[randV2];
                adjList[randV2] = newNode2;

                cout<<"\n Udalo sie. V1: "<<randV1<<" V2:"<<randV2<<" waga:"<<randWeight;

            } else {
                srand(time(NULL));
                randV1 = rand() % numOfVertices;
                randV2 = rand() % numOfVertices;
                tryAgain = true;

            }
        } while(tryAgain);                 // do skutku probuje na nowo wygenerowac krawedzi

    }
    cout<<"\n\n";

}

//git
void MST::generateGraphFromFile() {
    cout<<"\n\n";

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
    cout<<"\n\n";

}

//git
void MST::printMatrix() {

    cout<<"\n\n";
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
    cout<<"\n\n";

}

//git
void MST::printAdjacencyList() {
    cout<<"\n\n";
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
bool MST::prim_matrix(){
    cout<<"\n\n";

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
    pq->deleteFromBeginning();                                               // usuwam już dodany

    /// GŁOWNA CZEŚĆ FUNKCJI,
    for(int i = 1; i < numOfVertices - 1; i++){                             // wyszukiwanie określonej liczby krawędzi
        Queue::Node* currentNode = pq->head;
        while(currentNode != nullptr){                                      // znalezienie najmniejszej krawędzi, która nam pasuje
            parent1 = findParent(currentNode->data.v1, parent);       //szukam korzenia poddrzewa, do którego należy v1
            parent2 = findParent(currentNode->data.v2, parent);       //szukam korzenia poddrzewa, do którego należy v2

            if(parent1 != parent2 && (parent2 == permParent || parent1 == permParent )){            //sprawdza, nie ma pętli i czy krawedz jest sasiadujaca z drzewem co mam do tej pory
                cout << "Edge: " << currentNode->data.v1 << " - " << currentNode->data.v2 << ", weight: " << currentNode->data.weight <<endl;
                if(parent2 == permParent){
                    unionSets( parent1, parent2, parent);
                }
                else{
                    unionSets( parent2,parent1, parent);
                }
                break;
            }
            currentNode  = currentNode -> next;
        }
        if(currentNode == nullptr){
            cout<<"NOT ENOUGH EDGES TO CREATE MST OR SOME NODES ARE NOT CONNECTED";
            return false;
        }
        //pq->deleteFromBeginning();
    }
    cout<<"\n\n";

    delete pq;
    delete[] parent;
    return true;
}


bool MST::prim_list() {
    cout<<"\n\n";

    /// ZAMIANA LIST NA PRIORITY QUEUE
    auto *pq = new Queue();                    // tworze posortowana kolejkę krawedzi

    for(int i=0; i<numOfVertices; i++){         // iteruje po wierzchołkach

        AdjNode *firstNode = adjList[i];        // biore pierwsza krawedz

        while(firstNode != nullptr){            // petla iterujaca po wszystkich krawdziach tego wierzchołka
            Queue::Edge e{};                      // nowa krawedz do dodania do kolejki
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
    pq->deleteFromBeginning();

    /// GŁOWNA CZEŚĆ FUNKCJI,
    for(int i = 1; i < numOfVertices - 1; i++){                             // wyszukiwanie określonej liczby krawędzi
        Queue::Node* currentNode = pq->head;
        while(currentNode != nullptr){                                      // znalezienie najmniejszej krawędzi, która nam pasuje
            parent1 = findParent(currentNode->data.v1, parent);       //szukam korzenia poddrzewa, do którego należy v1
            parent2 = findParent(currentNode->data.v2, parent);       //szukam korzenia poddrzewa, do którego należy v2

            if(parent1 != parent2 && (parent2 == permParent || parent1 == permParent )){            //sprawdza, nie ma pętli i czy krawedz jest sasiadujaca z drzewem co mam do tej pory
                cout << "Edge: " << currentNode->data.v1 << " - " << currentNode->data.v2 << ", weight: " << currentNode->data.weight <<endl;
                if(parent2 == permParent){
                    unionSets( parent1, parent2, parent);
                }
                else{
                    unionSets( parent2,parent1, parent);
                }
                break;
            }
            currentNode  = currentNode -> next;
        }
        if(currentNode == nullptr){
            cout<<"NOT ENOUGH EDGES TO CREATE MST OR SOME NODES ARE NOT CONNECTED";
            return false;
        }
    }
    cout<<"\n\n";

    delete pq;
    delete[] parent;
    return true;
}


//git
bool MST::kruskal_matrix() {

    cout<<"\n\n";

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
        if(pq->head == nullptr){
            cout<<"NOT ENOUGH EDGES TO CREATE MST OR SOME NODES ARE NOT CONNECTED";
            return false;
        }
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
    cout<<"\n\n";

    delete pq;
    delete[] parent;                   // usuwam tablice, bo nie bedzie juz potrzebna
    return true;
}

//git, ale nieoptymalnie chyba
bool MST::kruskal_list() {
    cout<<"\n\n";

    auto *pq = new Queue();                    // tworze posortowana kolejkę krawedzi

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
        if(pq->head == nullptr){
            cout<<"NOT ENOUGH EDGES TO CREATE MST OR SOME NODES ARE NOT CONNECTED";
            return false;
        }
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

    cout<<"\n\n";
    delete pq;
    delete[] parent;                   // usuwam tablice, bo nie bedzie juz potrzebna
    return true;
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

void MST::autoTest() {
    string path = R"(D:\PWR\4 sem\SDIZO\Projekt2\tests\tests.txt)";
    ofstream fout(path);
    //fout.open("D:\\PWR\\4 sem\\SDIZO\\Projekt2\\tests\\tests.txt", fstream::out);
    Time time;
    int numOfTests = 10;
    cout<<"Starting test of MST";
    fout<<"----Test of MST----\n";

    for(int i = 1; i<=2; i++){
        numOfVertices = i * 10;
        double list[1] = {0.25};        ///0.5, 0.75, 0.99
        for(double elem : list){

            cout<<"\nStarting test numOfVertices = "<<numOfVertices<<", Density = "<<elem<<endl;
            fout<<"\n\nTesting with params:\nNumber of Vertices = " << numOfVertices;
            fout<<", Density = "<<elem<<"\n\n";
            generateGraph(numOfVertices, elem);                //gerowanie grafu o konkretnych parametrach

            int validTests = 0;
            long long tempTime = 0;
            for(int j=0; j<numOfTests; j++){

                time.start();
                cout<<"\n\nPrim Matrix\n";
                bool valid = prim_matrix();
                if(valid){
                    validTests++;
                }
                time.stop();
                tempTime+= time.returnTime()/numOfTests;

            }
            if(validTests == numOfTests){
                fout<<"Prim (matrix) avg time: " << tempTime<<endl;
                cout<<"Prim (matrix) avg time: " << tempTime;
            }
            else{
                fout<<"Not enough valid tests!";
                cout<<"Not enough valid tests!";
            }

            validTests = 0;
            tempTime = 0;
            for(int j=0; j<numOfTests; j++){

                time.start();
                cout<<"\n\nPrim list\n";
                bool valid = prim_list();
                if(valid){
                    validTests++;
                }
                time.stop();
                tempTime+= time.returnTime()/numOfTests;

            }
            if(validTests == numOfTests){
                fout<<"Prim (list) avg time: " << tempTime<<endl;
                cout<<"Prim (list) avg time: " << tempTime;
            }
            else{
                fout<<"Not enough valid tests!";
                cout<<"Not enough valid tests!";
            }

            validTests = 0;
            tempTime = 0;
            for(int j=0; j<numOfTests; j++){

                time.start();
                cout<<"\n\nKruskal matrix\n";
                bool valid = kruskal_matrix();
                if(valid){
                    validTests++;
                }
                time.stop();
                tempTime+= time.returnTime()/numOfTests;

            }
            if(validTests == numOfTests){
                fout<<"Kruskal (matrix) avg time: " << tempTime<<endl;
                cout<<"Kruskal (matrix) avg time: " << tempTime;
            }
            else{
                fout<<"Not enough valid tests!";
                cout<<"Not enough valid tests!";
            }


            validTests = 0;
            tempTime = 0;
            for(int j=0; j<numOfTests; j++){

                time.start();
                cout<<"\n\nKruskal list\n";
                bool valid = kruskal_list();
                if(valid){
                    validTests++;
                }
                time.stop();
                tempTime+= time.returnTime()/numOfTests;

            }
            if(validTests == numOfTests){
                fout<<"Kruskal (list) avg time: " << tempTime<<endl;
            }
            else{
                fout<<"Not enough valid tests!";
            }

        }

    }
}