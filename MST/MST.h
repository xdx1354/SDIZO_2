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



    AdjNode **adjList;
    AdjNode *p;                   //temp list ??

    int **graph;
    int numOfEdges, numOfVertices, pos;
    int weight;
    double density;


    void menu_MST();
    void generateGraphFromFile();
    void generateGraph(int n, double d);

    void printMatrix();
    void printAdjacencyList();
    void printMST();

    bool prim_matrix();
    bool prim_list();

    bool kruskal_matrix();
    bool kruskal_list();

    int findParent(int, int*);
    void unionSets(int, int, int*);
    void autoTest();



};


#endif //PROJEKT2_MST_H
