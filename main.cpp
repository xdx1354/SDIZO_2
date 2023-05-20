#include <iostream>
#include <bits/stdc++.h>
#include "MST/MST.h"
#include "shortest-path/ShortestPath.h"

using namespace std;

int main() {

//    int tmpEdges = 4;
//    int tmpVertexes = 5;
//


    MST mst = * new MST();
    mst.generateGraph(10, 0.99);
//    mst.generateGraphFromFile();
//    mst.printMatrix();
//    mst.printAdjacencyList();
//    cout<<"\n\nKRUSKAL MATRIX: \n";
//    mst.kruskal_matrix();
//    cout<<"\n\nKRUSKAL LIST: \n";
//    mst.kruskal_list();
//    cout<<"\n\nPRIM LIST: "<<endl;
//    mst.prim_list();
//    cout<<"\n\nPRIM MATRIX: "<<endl;
//    mst.prim_matrix();

//    ShortestPath sp = * new ShortestPath();
//    //sp.generateGraphFromFile();
//    sp.generateGraph(10, 0.5);
//    sp.printMatrix();
//    sp.printAdjacencyList();
//    sp.Dijkstra_matrix(5);
//    sp.Dijkstra_list(5);
//    sp.BellmanFord_matrix(5);
//    sp.BellmanFord_list(5);
}
