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
    cout<<"\n\nKRUSKAL: \n";
    mst.kruskal_matrix();
    cout<<"\n\nPRIM: "<<endl;
    mst.prim_matrix();
}
