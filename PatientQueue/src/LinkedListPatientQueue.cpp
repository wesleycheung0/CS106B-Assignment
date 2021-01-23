// This is the CPP file you will edit and turn in. (TODO: Remove this comment!)

#include "LinkedListPatientQueue.h"
#include <string>
#include <vector>
#include <algorithm>

LinkedListPatientQueue::LinkedListPatientQueue() {
    front = NULL;
}

LinkedListPatientQueue::~LinkedListPatientQueue() {
    while (front != nullptr) {
        PatientNode* trash = front;
        front = front->next;
        delete trash;
    }
}

void LinkedListPatientQueue::clear() {
    while (front != nullptr) {
        PatientNode* trash = front;
        front = front->next;
        delete trash;
    }
}

string LinkedListPatientQueue::frontName() {
    return front->name;   // this is only here so it will compile
}

int LinkedListPatientQueue::frontPriority() {
    return front->priority;
}

bool LinkedListPatientQueue::isEmpty() {
    // TODO: write this function
    return (front==NULL);   // this is only here so it will compile
}

void LinkedListPatientQueue::newPatient(string name, int priority) {
    PatientNode* incoming = new PatientNode(name, priority);
    if (front == NULL ){
        front = incoming;
    }else if(front->priority>priority){
        incoming->next = front;
        front = incoming;
    }else{;
        PatientNode* pre = front;
        PatientNode* curr = front;

        while (curr->next!=nullptr && curr->next->priority<=priority){
            curr = curr->next;
        }
        incoming->next = curr->next;
        curr->next = incoming;
    }

}

string LinkedListPatientQueue::processPatient() {
    string temp = front->name;
    PatientNode* skip_node = front;
    front = skip_node->next;
    delete skip_node;
    return temp;
}

void LinkedListPatientQueue::upgradePatient(string name, int newPriority) {
    PatientNode* New_Node = front;
    while(New_Node->name!=name){
        New_Node = New_Node->next;
    }
    New_Node->priority = newPriority;
    front = New_Node;
}

string LinkedListPatientQueue::toString() {

    if (front!=nullptr){
        PatientNode* New_Node = front;
        string print;
        while (New_Node->next != nullptr){
            print += to_string(New_Node->priority) + ":" + New_Node->name;
            if (New_Node->next!=nullptr){
                print += ",";
                New_Node = New_Node->next;
            }
        }
        print += to_string(New_Node->priority) + ":" + New_Node->name;
        return "{"+print+"}";
    }else{
        return "{}";
    }
}
