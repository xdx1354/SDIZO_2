//
// Created by stani on 09.05.2023.
//

#ifndef PROJEKT2_QUEUE_H
#define PROJEKT2_QUEUE_H


class Queue {
    Queue(int n);
    ~Queue();

    struct Edge{
        int v1, v2, weight;             // v1- starting vertex, v2- ending vertex
    };

private:
    Edge *heap;
    int pos;
public:
    void createQueue(int n);        //TODO: czy nie powinno zwracac obiektu?
    void deleteQueue();
    Edge root();
    void insert(Edge e);
    void deleteFromBeginning();
};




#endif //PROJEKT2_QUEUE_H
