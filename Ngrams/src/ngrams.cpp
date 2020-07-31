// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include "console.h"
#include "map.h"
#include "vector.h"
#include <cstdlib>

using namespace std;

void print_vector(vector <string> vec2_Print);
string random_vector(vector<string> input_vector);

int main() {
    string txt_name;
    cout<< "Input file name?";
    cin>>txt_name;

    int random_N;
    cout<<"Value of N?";
    cin>>random_N;


    int word_count;
    cout<<"# of random words to generate (0 to quit)?";
    cin>> word_count;

    map<vector<string>,vector<string>> txt_map;
    map<vector<string>,vector<string>>::iterator it;

    //Opening the txt file
    ifstream text;
    string word;
    text.open(txt_name);

    //Building the base case for the mapping files//
    //First Prefix
    vector<string> vector_N;
    for (int i=0; i<(random_N-1); i++){
        text>>word;
        vector_N.insert(vector_N.end(),word);
    }

    //First Suffix
    text>>word;
    vector<string> value;
    value.insert(value.begin(),word);
    //insert the first key and value to map
    txt_map.insert(pair<vector<string>,vector<string>>(vector_N, value));
    //Sliding window
    vector_N.erase(vector_N.begin());
    vector_N.insert(vector_N.end(),word);
    text>>word;
    while(text){

        vector<string> value;
        value.insert(value.end(),word);
        it = txt_map.find(vector_N);
        if (it!=txt_map.end()){
            vector<string> temp;
            temp = it->second;
            temp.insert(temp.end(),word);
            it->second = temp;
        }else{
           txt_map.insert(pair<vector<string>,vector<string>>(vector_N, value));
        }
        vector_N.erase(vector_N.begin());
        vector_N.insert(vector_N.end(),word);
        text>>word;

    }
    text.clear();
    text.seekg(0, ios::beg);
    text>>word;
    for (int i=0; i<random_N-1;i++){

        vector<string> value;
        value.insert(value.end(),word);
        it = txt_map.find(vector_N);
        if (it!=txt_map.end()){
            vector<string> temp;
            temp = it->second;
            temp.insert(temp.end(),word);
            it->second = temp;
        }else{
           txt_map.insert(pair<vector<string>,vector<string>>(vector_N, value));
        }
        vector_N.erase(vector_N.begin());
        vector_N.insert(vector_N.end(),word);
        text>>word;

    }
    text.close();

////Testing Map
//    for(auto it = txt_map.cbegin(); it != txt_map.cend(); ++it)
//    {
//        print_vector(it->first);
//        print_vector(it->second);
//        cout<<"\n"<<endl;
//    }




    //    Randomly pick a starting key from map

    while (word_count!=0){
        vector<string> output_vector;
        auto it_2 = txt_map.begin(); // Set the iterator to the beginning
        advance(it_2, rand() % txt_map.size());// advance the iterator by random number

        //Create a starting random key
        vector<string> random_key = it_2->first;
        //Store the starting random key to output vector
        for (int i=0; i<random_key.size();i++){
            output_vector.insert(output_vector.begin(),random_key[i]);
        }
        //Creaeting a starting random value
        string output_value;
        output_value = random_vector(it_2->second);

        //Creating sliding window
        vector<string>sliding_window;
        //Sliding
        random_key.erase(random_key.begin());
        random_key.insert(random_key.end(),output_value);
        sliding_window = random_key;
        output_vector.insert(output_vector.end(),output_value);

        int extra_word = word_count-random_N-1;
        int count = 0;
        while(count<extra_word){
            string next_value = random_vector(txt_map[sliding_window]);//
            sliding_window.erase(sliding_window.begin());
            sliding_window.insert(sliding_window.end(),next_value);
            output_vector.insert(output_vector.end(),next_value);
            count++;
        }
        print_vector(output_vector);
        cout<<"\n";
        cout<<"\n";
        cout<<"# of random words to generate (0 to quit)?";
        cin>> word_count;

    }



    return 0;
}

void print_vector(vector <string> vec2_Print){
    cout<<"...";
    for (int i=0; i<vec2_Print.size();i++){
        cout<<vec2_Print[i]<<" ";
    }
    cout<<"...";

}


string random_vector(vector<string> input_vector){
    int x = rand() % input_vector.size();
    return(input_vector[x]);
}
