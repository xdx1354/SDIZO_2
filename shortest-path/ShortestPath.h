//
// Created by stani on 20.05.2023.
//

#ifndef PROJEKT2_SHORTESTPATH_H
#define PROJEKT2_SHORTESTPATH_H


class ShortestPath {
public:

    struct AdjNode{
        AdjNode *next;
        int neighbour;
        int weight;
    };



    AdjNode **adjList;
    AdjNode *p;                   //temp list ??

    int **graph;
    int numOfEdges, numOfVertices, pos;
    int weight;
    double density;
    int *prev;                          // tablica poprzedników
    long long *distance;                // tablica z kosztami dojscia do poszczegolnych wierzchołków

    void menu_Path();
    void autoTest();
    void generateGraphFromFile();
    void generateGraph(int n, double d);

    void printMatrix();
    void printAdjacencyList();
    void printPath(int startingV);

    void dijkstraMatrix(int startingV);
    void dijkstraList(int startingV);

    void bellmanFordMatrix(int startingV);
    void bellmanFordList(int startingV);
};


#endif //PROJEKT2_SHORTESTPATH_H
