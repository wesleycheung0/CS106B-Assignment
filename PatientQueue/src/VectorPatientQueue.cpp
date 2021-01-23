
#include "VectorPatientQueue.h"
#include<vector>
#include <algorithm>


// Constructor
VectorPatientQueue::VectorPatientQueue() {
    struct patient_Vector{
        int priority;
        string name;
    };
    vector<patient_Vector> vector_Queue;
}

// Destructor
VectorPatientQueue::~VectorPatientQueue() {

}

// Remove all element
void VectorPatientQueue::clear() {
   vector_Queue.clear();
}


// Return the name of the most urgent
string VectorPatientQueue::frontName() {
    if (vector_Queue.empty()){
        throw "Empty Queue";
    }

    int index = 0;
    int min = INT_FAST16_MAX;
    int min_index = 0;
    for (auto it=vector_Queue.begin(); it!=vector_Queue.end();++it){
        int curr_priority = it->priority;
        if (curr_priority<min){
            min = curr_priority;
            min_index = index;
        }
        index++;
    }

    string frontName = (vector_Queue.begin()+min_index)->name;
    return frontName;   // this is only here so it will compile
    }

// Return the most urgent patient
int VectorPatientQueue::frontPriority() {

    if (vector_Queue.empty()){
        throw "Empty Queue";
    }

    int index = 0;
    int min = INT_FAST16_MAX;
    int min_index = 0;
    for (auto it=vector_Queue.begin(); it!=vector_Queue.end();++it){
        int curr_priority = it->priority;
        if (curr_priority<min){
            min = curr_priority;
            min_index = index;
        }
        index++;
    }

    int frontPriority = (vector_Queue.begin()+min_index)->priority;
    return frontPriority;
}

bool VectorPatientQueue::isEmpty() {
    // TODO: write this function
    return (vector_Queue.empty());   // this is only here so it will compile
}

void VectorPatientQueue::newPatient(string name, int priority) {
    //Add the given person into the queue
    if (VectorPatientQueue::isEmpty()){
        vector_Queue.push_back(patient_Vector());
        vector_Queue[0].name = name;
        vector_Queue[0].priority = priority;

    }
    else{
        vector_Queue.push_back({priority,name});
    }
}

//Return and remove the most urgent patient
string VectorPatientQueue::processPatient() {
    int index = 0;
    int min = INT_FAST16_MAX;
    int min_index = 0;
    for (auto it=vector_Queue.begin(); it!=vector_Queue.end();++it){
        int curr_priority = it->priority;
        if (curr_priority<min){
            min = curr_priority;
            min_index = index;
        }
        index++;
    }

    string patient = (vector_Queue.begin()+min_index)->name;
    vector_Queue.erase(vector_Queue.begin()+min_index);
    return patient;
    
    
}

void VectorPatientQueue::upgradePatient(string name, int newPriority) {
    // Upgrade existing patient with new priority
    for (auto&i : vector_Queue){
        if (i.name==name){
            i.priority=newPriority;
        }
    }
}

string VectorPatientQueue::toString() {
    string vector_string = "{";
    vector<patient_Vector>:: iterator it;
    for (it = vector_Queue.begin(); it !=vector_Queue.end(); ++it){
        vector_string += to_string(it->priority);
        vector_string+=":";
        vector_string += it->name;
        if (it+1!=vector_Queue.end()){
            vector_string+=",";
        }
    }
    vector_string += "}";

    return vector_string; // this is only here so it will compile
}
