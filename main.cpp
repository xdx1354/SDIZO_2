#include <iostream>
#include <bits/stdc++.h>
#include "MST/MST.h"

using namespace std;

int main() {

//    int tmpEdges = 4;
//    int tmpVertexes = 5;
//


    MST mst = * new MST();
    mst.generateGraphFromFile();
    mst.printMatrix();
//    mst.printAdjacencyList();
//    mst.prim_matrix();
    mst.kruskal_matrix();
}
