#include <iostream>
#include <bits/stdc++.h>
#include "MST/MST.h"
#include "shortest-path/ShortestPath.h"

using namespace std;

int main() {

    cout<<"Stanislaw Kurzyp 264477\n SDiZO, Pn T? 9:15\n";              //TODO: tydzień jaki?

    ShortestPath sp = * new ShortestPath();
    MST mst = *new MST();

    int x = -1;
    while(x!=0){

        cout<<"1. Shortest Path (Dijkstra, Bellman-Ford) \n";
        cout<<"2. MST (Prim, Kruskal)\n";
        cout<<"0. Exit\n";
        cout<<"\nChoose task: \n";
        cin>>x;
        switch(x){
            default:{
                cout<<"Wrong number.\n";
                break;
            }
            case 0:{
                //EXIT
                break;
            }

            case 1:{
                //ShortestPath menu
                sp.menu_Path();
                break;
            }
            case 2:{
                // MST menu
                mst.menu_MST();
                break;
            }
            case 3:{

                break;
            }
            case 4:{

                break;
            }
        }
    }

//    sp.autoTest();
//    mst.autoTest();
//    mst.autoTest();
//mst.generateGraph(10, 0.6);

//    int tmpEdges = 4;
//    int tmpVertexes = 5;
//


//    MST mst = * new MST();
//    mst.generateGraph(5, 0.5);
//mst.generateGraphFromFile();
//    mst.printMatrix();
//    mst.printAdjacencyList();

//mst.printAdjacencyList();
//mst.printMatrix();
//    cout<<"\n\nPRIM LIST: "<<endl;
//    mst.prim_list();
//    cout<<"\n\nPRIM MATRIX: "<<endl;
//    mst.prim_matrix();
//    cout<<"\n\nKRUSKAL MATRIX: \n";
//    mst.kruskal_matrix();
//    cout<<"\n\nKRUSKAL LIST: \n";
//    mst.kruskal_list();



//    sp.generateGraph(10, 0.5);
////    //sp.generateGraphFromFile();
////    sp.generateGraph(10, 0.5);
////    sp.printMatrix();
////    sp.printAdjacencyList();
////    sp.dijkstraMatrix(5);
////    sp.dijkstraList(5);
//    sp.bellmanFordMatrix(5);
//    sp.bellmanFordList(5);
}
