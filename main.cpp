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
    mst.printAdjacencyList();
    cout<<"\n\nKRUSKAL MATRIX: \n";
    mst.kruskal_matrix();
    cout<<"\n\nKRUSKAL LIST: \n";
    mst.kruskal_list();
    cout<<"\n\nPRIM LIST: "<<endl;
    mst.prim_list();
    cout<<"\n\nPRIM MATRIX: "<<endl;
    mst.prim_matrix();
}
