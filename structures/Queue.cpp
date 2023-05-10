//
// Created by stani on 09.05.2023.
//

#include <iostream>
#include "Queue.h"

using namespace  std;

Queue::~Queue(){                        //Destructor

}


void Queue::insert(Edge data) {
    Node* newNode = new Node;
    newNode->data = data;
    newNode->next = nullptr;

    // If the queue is empty or the new edge has lower weight than the head node
    if (head == nullptr || data.weight < head->data.weight) {
        newNode->next = head;
        head = newNode;
    } else {
        Node* temp = head;
        // Find the appropriate position to insert the new edge
        while (temp->next != nullptr && temp->next->data.weight <= data.weight) {
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
    }
}

void Queue::print(){
    cout<<endl;
    if (head == nullptr) {
        cout << "Priority Queue is empty." << endl;
        return;
    }

    Node* temp = head;
    while (temp != nullptr) {
        cout << "v1: " << temp->data.v1 << ", v2: " << temp->data.v2 << ", Weight: " << temp->data.weight << endl;
        temp = temp->next;
    }
}

void Queue::deleteFromBeginning() {
    if(head != NULL){
        Node* temp = head;
        Edge data = head ->data;
        head = head -> next;
        delete temp;
    }
}