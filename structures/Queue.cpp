//
// Created by stani on 09.05.2023.
//

#include "Queue.h"

using namespace  std;

Queue::Queue(int n){                    //Constructor
    heap = new Edge[n];
    pos = 0;
}

Queue::~Queue(){                        //Destructor
    delete []heap;
}

void Queue::createQueue(int n) {

}

void Queue::insert(Edge e) {
    int i, j;
    i = pos++;
    j = ( i - 1 ) / 2;
    while( i>0 && heap[j].weight > e.weight){
        heap[i] = heap[j];
        i = j;
        j = ( i - 1 ) / 2;
    }


}