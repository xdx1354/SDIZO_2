//
// Created by stani on 09.05.2023.
//

#ifndef PROJEKT2_QUEUE_H
#define PROJEKT2_QUEUE_H


class Queue {
    ~Queue();






public:
    struct Edge{
        int v1, v2, weight;             // v1- starting vertex, v2- ending vertex
        Edge *next = nullptr;
    };

    struct Node {
        Edge data;
        Node* next;
    };

    Node* head;


    void insert(Edge e);
    void deleteFromBeginning();
    void print();

    Queue(){
        head = nullptr;
    };

};




#endif //PROJEKT2_QUEUE_H
