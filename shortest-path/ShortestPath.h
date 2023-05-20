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
    int density;
    int *prev;                          // tablica poprzedników
    long long *distance;                // tablica z kosztami dojscia do poszczegolnych wierzchołków

    void menu_Path();
    void generateGraphFromFile();
    void generateGraph();

    void printMatrix();
    void printAdjacencyList();
    void printPath(int startingV);

    void Dijkstra_matrix(int startingV);
    void Dijkstra_list(int startingV);

    void BellmanFord_matrix(int startingV);
    void BellmanFord_list(int startingV);
};


#endif //PROJEKT2_SHORTESTPATH_H
