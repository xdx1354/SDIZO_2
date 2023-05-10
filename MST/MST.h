//
// Created by stani on 09.05.2023.
//

#ifndef PROJEKT2_MST_H
#define PROJEKT2_MST_H


class MST {
public:

    struct AdjNode{
        AdjNode *next;
        int neighbour;
        int weight;
    };

    struct Edge{
        int v1, v2, weight;             // v1- starting vertex, v2- ending vertex
        Edge *next = nullptr;
    };


    AdjNode **adjList;
    AdjNode *p;                   //temp list ??

    int **graph;
    int numOfEdges, numOfVertexes, pos;
    int weight;
    int density;


    void menu_MST();
    void generateGraphFromFile();
    void generateGraph();

    void printMatrix();
    void printAdjacencyList();
    void printMST();

    void prim_matrix();
    void prim_list();

    void kruskal_matrix();
    void kruskal_list();

    //TODO: to nie wszystkie potrzebne funkcje


};


#endif //PROJEKT2_MST_H
