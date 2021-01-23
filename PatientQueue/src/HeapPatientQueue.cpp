// heappatientqueue.cpp
// THIS IS AN EXTENSION AND NOT REQUIRED FOR THE ASSIGNMENT
// This is the CPP file you will edit and turn in. (TODO: Remove this comment!)

#include "HeapPatientQueue.h"

// Constructor
HeapPatientQueue::HeapPatientQueue() {
    struct patient_Vector{
        int priority;
        string name;
    };
    vector<patient_Vector> heap_Queue;
}

// Destructor
HeapPatientQueue::~HeapPatientQueue() {

}

// Clear the patient queue
void HeapPatientQueue::clear() {
    heap_Queue.clear();
}

// return the patient's name on the first spot on the queue
string HeapPatientQueue::frontName() {
    if (heap_Queue.empty()){
        throw "Empty Queue";
    }
    return heap_Queue[1].name;
}

// return the patient's priority on the first spot on the queue
int HeapPatientQueue::frontPriority() {
    if (heap_Queue.empty()){
        throw "Empty Queue";
    }
    return heap_Queue[1].priority;
}

// return if the queue is empty
bool HeapPatientQueue::isEmpty() {

    return heap_Queue.empty();   // this is only here so it will compile
}

void HeapPatientQueue::newPatient(string name, int priority) {
    struct patient_Vector next = {priority, name};
    heap_Queue.insert(heap_Queue.end(), next);
    int start_index = heap_Queue.size()-1;

    // Bubble Up
    while ((ceil(start_index/2.0)-1)>=0){
        int compare_priority = heap_Queue[ceil(start_index/2.0)-1].priority;
        int starting_priority = heap_Queue[start_index].priority;
        if (compare_priority>starting_priority){
            struct patient_Vector temp = heap_Queue[ceil(start_index/2.0)-1];
            heap_Queue[ceil(start_index/2.0)-1] = heap_Queue[start_index];
            heap_Queue[start_index] = temp;
        }
        start_index = ceil(start_index/2.0)-1;
    }
}

string HeapPatientQueue::processPatient() {
    string frontname = heap_Queue[0].name;
    int last_index = heap_Queue.size()-1;
    heap_Queue[0] = heap_Queue[last_index]; // move the last index to the front
    heap_Queue.erase(heap_Queue.end());// erase the last index

    //Bubble down
    int start_index = 0;
    while (start_index*2+1<=last_index){
        int starting_priority = heap_Queue[start_index].priority;
        int compare_priority1 = heap_Queue[start_index*2+1].priority;
        int compare_priority2 = heap_Queue[start_index*2+2].priority;

        if (starting_priority>compare_priority1 || starting_priority>compare_priority1 ){
            if (compare_priority1>compare_priority2){
                patient_Vector temp = heap_Queue[start_index];
                heap_Queue[start_index] = heap_Queue[start_index*2+1];
                heap_Queue[start_index*2+1] = temp;
            }else{
                patient_Vector temp = heap_Queue[start_index];
                heap_Queue[start_index] = heap_Queue[start_index*2+2];
                heap_Queue[start_index*2+2] = temp;
            }
        }
        if (compare_priority1>compare_priority2){
            start_index = start_index*2+1;
        }else{
            start_index = start_index*2+2;
        }
    }


    return frontname;   // this is only here so it will compile
}

void HeapPatientQueue::upgradePatient(string name, int newPriority) {
    // TODO: write this function
}

string HeapPatientQueue::toString() {
    string heap_string = "{";
    vector<patient_Vector>:: iterator it;
    for (it = heap_Queue.begin(); it !=heap_Queue.end(); ++it){
        heap_string += to_string(it->priority);
        heap_string+=":";
        heap_string += it->name;
        if (it+1!=heap_Queue.end()){
            heap_string+=",";
        }
    }
    heap_string += "}";

    return heap_string;
}
