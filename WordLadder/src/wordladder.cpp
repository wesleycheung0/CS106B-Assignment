// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include "console.h"
#include "stack.h"
#include "vector.h"
#include "lexicon.h"
#include "queue.h"


using namespace std;

Lexicon getFileContent(string fileName, Lexicon & vecOfStrs);
vector<string> neighbors_find(string &word, Lexicon dictionary);
int bfs(Queue<Vector<string>> word_load, Lexicon dictionary, string word_1, string word_2);

int main() {

    cout<<"Welcome to CS 106B Word Ladder.\n"
          "Please give me two English words, and I will change the \n"
          "first into the second by changing one letter at a time.\n\n";

    string dictionary_Name;
    cout << "Dictionary file name? ";
    cin >> dictionary_Name;

    Lexicon english(dictionary_Name);
    bool pass = false;

    string word_1;
    string word_2;

    while (true){

        while (pass==false){
            // Word 1 Input
            cout << "Word #1 (or Enter to quit):";
            cin >> word_1;
            if (word_1=="q"){
                goto stop;
            }
            //Word 2 Input
            cout << "Word #2 (or Enter to quit):";
            cin >> word_2;

            if (word_2=="q"){
                goto stop;
            }
            if (!english.contains(word_1) | !english.contains(word_2)){
                cout<< "The two words must be found in the dictionary.\n\n";
            }
            else if (word_1.length()!=word_2.length()){
                cout<< "The two words must be the same length.\n\n";
            }
            else if (word_1==word_2){
                cout<< "The two words must be differenets.\n\n";
            }

            else {
                pass=true;
            }
        }

        Queue<Vector<string>> word_load;
        vector<string> base;
        base.insert(base.begin(), word_1);
        word_load.enqueue(base);
        bfs(word_load, english, word_1, word_2);

        //reset
        pass = false;
    }

    stop:
    cout<< "Have a Nice Day!";
    return 0;
}


int bfs(Queue<Vector<string>> word_load, Lexicon dictionary, string word_1, string word_2){
    // Roadmap is the node that you must passed to get to the destination nodes
    Vector<string> roadmap;
    Lexicon history;// History of all node that have visited
    history.add(word_1);// Adding the starting node to the history
    string alphabet = "abcdefghijklmnoqprstuvwxyz";

    while(!word_load.isEmpty()){
        //Roadmap equals to the dequeue
        roadmap = word_load.dequeue();
        //curr_word refers to the last nodes on the road mapthat we are search for its neightbors
        string curr_word = roadmap[roadmap.size()-1];
        //Creating its neightbors
        for (int j=0; j<26;j++){
            for (int i=0; i < curr_word.length(); i++){
                string word_temp = curr_word;
                word_temp[i] = alphabet[j];
                // If this nodes has not been visited and in the dictionary
                if (!history.contains(word_temp) && (dictionary.contains(word_temp))){
                    if(word_temp == word_2){
                        cout<<"Hooray! we have found a solution: \n";
                        for (int i=0; i<roadmap.size();i++){
                        cout<<roadmap[i]<<" ";
                        }
                        cout<< word_2<<endl;
                        cout<<"\n";
                        return 0;

                    }else{
                        //Creating a copy of roadmap
                        Vector<string> roadmap_copy = roadmap;
                        //Creating a new roadmap with this nodes
                        roadmap_copy.add(word_temp);
                        // Mark this nodes is been visited
                        history.add(word_temp);
                        //Put this the roadmap in to queue
                        word_load.enqueue(roadmap_copy);
                        }
                    }
            }
        }
    }
    cout<<"No Solution\n\n";
    return 1;
}


