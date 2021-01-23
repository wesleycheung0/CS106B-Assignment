// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.
// TODO: write comment header for this file; remove this comment

#include "trailblazer.h"
#include "queue.h"
#include "set.h"
#include "pqueue.h"
#include "point.h"
#include <vector>
#include "pqueue.h"
#include <map>
#include<unordered_set>
#include"hashmap.h"


using namespace std;

// this makes Path an alias for the type Vector<Vertex*>
typedef Vector<Vertex*> Path;


void paintVertexColor(Path);

Path dijkstrasAlgorithm_alternative(RoadGraph& graph, Vertex* start, Vertex* end, Edge* exclude);
double diffScore(Path original, Path alter);

// the minimum difference for an alternate route
const double SUFFICIENT_DIFFERENCE = 0.2;

Path breadthFirstSearch(RoadGraph& graph, Vertex* start, Vertex* end) {

    // Initiating BFS

    Queue<Vertex*> track; //Next Depth Neighbor
    Vector<Path> track_path;//Current Track storing
    track.enqueue(start);// Storing the starting Vertex
    Vector <Vertex*> history;
    history.add(start);//Marked as visited
    //Set<Vertex*> first_neightbor = graph.getNeighbors(start);//Find the neighbor of the starting vertex
    Path path;
    path.add(start);
    track_path.add(path);// Add the starting vertex to currect track
    //Main loop
    Path current_path;
    while(!track.isEmpty()){// While have not checked all the neighrbor
        Vertex* visit_vert = track.dequeue();// Dequeue the working vertex
        Set<Vertex*>neigh_visit = graph.getNeighbors(visit_vert); //Find the neighbor of the working vertex

        for (Vertex* neighbor:neigh_visit){// For all the neighbors of the working vertex
            current_path.clear();
            current_path = track_path[0];

            if (neighbor == end){// if the vertex is not equal the destination
                current_path.push_back(neighbor); // Add the ending point to the current track
                paintVertexColor(current_path);
                return current_path; // return result
            }
            if (!std::count(history.begin(),history.end(),neighbor)){
                track.enqueue(neighbor);// storing neighbor vertex as the future workng vertex
                history.add(neighbor); // marked as visited
                current_path.push_back(neighbor);// Add the current vertex to the current path
                track_path.insert(track_path.size(),current_path); // enqueue current path in the track path
        }
        }
        track_path.remove(0);
    }
    Path empty;
    return empty;
}


void paintVertexColor(Path path){

    for (Vertex* neighbor:path){
        neighbor->setColor(GREEN);
    }

}


Vector<Vertex*> reverse_path(HashMap<Vertex*, Vertex*> previous, Vertex* start, Vertex* end){
    Stack<Vertex*> result;
    result.push(end);
    Vertex* previous_v =previous[end];
    result.push(previous_v);
    while(previous_v!= start){
       Vertex* temp = previous[previous_v];
       previous_v =temp;
       result.push(previous_v);
    }
    Path Result_p;
    while(!result.isEmpty()){
       Result_p.add(result.pop());
    }
    return Result_p;
}


Path dijkstrasAlgorithm(RoadGraph& graph, Vertex* start, Vertex* end){
    HashMap<Vertex*, Vertex*> dictionary;

   // Storing starting neighboring cost
    HashMap<Vertex*, double> dictionary_cost;
    dictionary_cost[start] = 0;

    //Enqueue the starting point to pq
    PriorityQueue<Vertex*> pq;
    pq.enqueue(start,0);

    // Vertex history
    unordered_set <Vertex*> history;

//    Set<Vertex*> neighbor_start = graph.getNeighbors(start);

    Vertex* visit_neigh;
    while(!pq.isEmpty()){
        visit_neigh = pq.dequeue();//dequeue the working vertex
//        if (visit_neigh==end){
//            return reverse_path(dictionary, start, end);
//        }
        history.insert(visit_neigh);
        if (visit_neigh==end){
            break;
        }
        visit_neigh->setColor(YELLOW);
        Set<Vertex*> visit_neigh_neight = graph.getNeighbors(visit_neigh);

        for (Vertex* neigh:visit_neigh_neight){
            if (history.find(neigh)==history.end()){// TO be Delete
                    Edge* edge = graph.getEdge(visit_neigh, neigh);
                    neigh->setColor(GREEN);
                    double cost = edge->cost+dictionary_cost[visit_neigh]; // Cost to travel to the new neighbor
                    if (dictionary_cost.containsKey(neigh)){
                        if (dictionary_cost[neigh]>=cost){
                            dictionary[neigh] = visit_neigh; // if the new path has lower cost than the previous
                            pq.enqueue(neigh,cost);
                            dictionary_cost[neigh] = cost;
                        }
                    }else{
                        dictionary[neigh] = visit_neigh; // if the new path has lower cost than the previous
                        pq.enqueue(neigh,cost);
                        dictionary_cost[neigh] = cost;
                    }
                }
        }



    }
    return reverse_path(dictionary, start, end);
}


Path aStar(RoadGraph& graph, Vertex* start, Vertex* end) {
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty vector so that the overall project will compile.
    //        You should remove that code and replace it with your implementation.)
    // Storing starting neighboring cost
     HashMap<Vertex*, Vertex*> dictionary;

    // Storing starting neighboring cost
     HashMap<Vertex*, double> dictionary_cost;
     dictionary_cost[start] = 0;

     //Enqueue the starting point to pq
     PriorityQueue<Vertex*> pq;
     pq.enqueue(start,0);

     // Vertex history
     Vector <Vertex*> history;

 //    Set<Vertex*> neighbor_start = graph.getNeighbors(start);

     Vertex* visit_neigh;
     while(!pq.isEmpty()){
         visit_neigh = pq.dequeue();//dequeue the working vertex
         history.add(visit_neigh);
         if (visit_neigh==end){
             break;
         }
         visit_neigh->setColor(YELLOW);
         Set<Vertex*> visit_neigh_neight = graph.getNeighbors(visit_neigh);

 //        for (Vertex* neigh:visit_neigh_neight){
 //            Edge* edge = graph.getEdge(visit_neigh,neigh);
 //            if (find(history.begin(),history.end(), neigh)==history.end()){
 //                pq.enqueue(neigh,edge->cost);
 //            }
 //        }
         for (Vertex* neigh:visit_neigh_neight){
             if (find(history.begin(),history.end(), neigh)==history.end()){// TO be Delete
                     Edge* edge = graph.getEdge(visit_neigh, neigh);
                     neigh->setColor(GREEN);
                     double heuristic = graph.getCrowFlyDistance(neigh, end)/graph.getMaxRoadSpeed();
                     double cost = edge->cost+dictionary_cost[visit_neigh]; // Cost to travel to the new neighbor
                     if (dictionary_cost.containsKey(neigh)){
                         if (dictionary_cost[neigh]>=cost){
                             dictionary[neigh] = visit_neigh; // if the new path has lower cost than the previous
                             pq.enqueue(neigh,cost+heuristic);
                             dictionary_cost[neigh] = cost;
                         }
                     }else{
                         dictionary[neigh] = visit_neigh; // if the new path has lower cost than the previous
                         pq.enqueue(neigh,cost+heuristic);
                         dictionary_cost[neigh] = cost;
                     }
                 }
         }



     }
     return reverse_path(dictionary, start, end);
 }

Path alternativeRoute(RoadGraph& graph, Vertex* start, Vertex* end) {
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty vector so that the overall project will compile.
    //        You should remove that code and replace it with your implementation.)

    // Compute the result from BFS
    // build a alternative BFS, with include a parameter on which vertex to ignore
    //Store each vertex in the queue
    // while the queue is not empty, pop the vertex to exclude
    // find the alternative BFS route
    //calculate the difference score
    // if the score is greater than the threshold
    // store in the prioity queue

    Path original = dijkstrasAlgorithm(graph, start,end);
    PriorityQueue <Path> pq;
    for (int i=0; i<original.size()-1;i++){
        Edge* edge = graph.getEdge(original[0], original[1]);
        Path alter = dijkstrasAlgorithm_alternative(graph, start, end, edge);
        double diff_score = diffScore(original, alter);
        if (diff_score>=SUFFICIENT_DIFFERENCE){
            pq.enqueue(alter, diff_score);
        }
    }

    return pq.dequeue();
}

double diffScore(Path original, Path alter){
    int diff = 0;
    for (Vertex* neigh:original){
        if (find(alter.begin(),alter.end(), neigh)==alter.end()){
            diff++;
        }
    }
    double score = diff/original.size();
    return score;
}



// Refactor into the original def
Path dijkstrasAlgorithm_alternative(RoadGraph& graph, Vertex* start, Vertex* end, Edge* exclude){
    HashMap<Vertex*, Vertex*> dictionary;

   // Storing starting neighboring cost
    HashMap<Vertex*, double> dictionary_cost;
    dictionary_cost[start] = 0;

    //Enqueue the starting point to pq
    PriorityQueue<Vertex*> pq;
    pq.enqueue(start,0);

    // Vertex history
    Vector <Vertex*> history;

//    Set<Vertex*> neighbor_start = graph.getNeighbors(start);

    Vertex* visit_neigh;
    while(!pq.isEmpty()){
        visit_neigh = pq.dequeue();//dequeue the working vertex
//        if (visit_neigh==end){
//            return reverse_path(dictionary, start, end);
//        }
        history.add(visit_neigh);
        visit_neigh->setColor(YELLOW);
        Set<Vertex*> visit_neigh_neight = graph.getNeighbors(visit_neigh);


        for (Vertex* neigh:visit_neigh_neight){
            if (find(history.begin(),history.end(), neigh)==history.end()){// TO be Delete
                    Edge* edge = graph.getEdge(visit_neigh, neigh);
                    if (edge!=exclude){
                        neigh->setColor(GREEN);
                        double cost = edge->cost+dictionary_cost[visit_neigh]; // Cost to travel to the new neighbor
                        if (dictionary_cost.containsKey(neigh)){
                            if (dictionary_cost[neigh]>=cost){
                                dictionary[neigh] = visit_neigh; // if the new path has lower cost than the previous
                                pq.enqueue(neigh,cost);
                                dictionary_cost[neigh] = cost;
                            }
                        }else{
                            dictionary[neigh] = visit_neigh; // if the new path has lower cost than the previous
                            pq.enqueue(neigh,cost);
                            dictionary_cost[neigh] = cost;
                        }
                    }
                }
        }



    }
    return reverse_path(dictionary, start, end);
}

