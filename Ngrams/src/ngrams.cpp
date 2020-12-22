// Random Writer

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
void n_grams_map(string word, map<vector<string>,vector<string>>::iterator it,
                 map<vector<string>,vector<string>> &txt_map,
                 vector<string>&vector_N);

// Main function of N-Grams
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
    txt_map.insert({vector_N, value});

    /*Sliding window
     * ( Erasing first words and add next word at the end)
     * */
    vector_N.erase(vector_N.begin());
    vector_N.insert(vector_N.end(),word);
    text>>word;

    // Reading the text
    while(text){
        n_grams_map(word, it, txt_map, vector_N);
        text>>word;
    }
    text.clear();
    text.seekg(0, ios::beg); //  beginning of the document
    text>>word;

    // Sliding the window back to the beginning of the text
    for (int i=0; i<random_N-1;i++){
        n_grams_map(word, it, txt_map, vector_N);
        text>>word;
    }
    text.close();


    // Generating Random Text

    while (word_count!=0){

        // Initization
        vector<string> output_vector;
        auto it_2 = txt_map.begin(); // Set the iterator to the beginning
        advance(it_2, rand() % txt_map.size());// advance the iterator by random number
        vector<string>sliding_window;

        //Create a starting random key
        vector<string> random_key = it_2->first;

        //Store the starting random key to output vector
        for (int i=0; i<random_key.size();i++){
            output_vector.insert(output_vector.end(),random_key[i]);
        }

        //Creaeting a starting random value
        string output_value;
        output_value = random_vector(it_2->second); // randomly select a word from vector
        output_vector.insert(output_vector.end(),output_value);

        //Creating sliding window
        random_key.erase(random_key.begin());// remove the first word
        random_key.insert(random_key.end(),output_value); // add the last key to the window
        sliding_window = random_key;

        int extra_word = word_count-random_N-1;
        int count = 0;

        while(count<extra_word){
            string next_value = random_vector(txt_map[sliding_window]);//return the random word from the map using the sliding window
            sliding_window.erase(sliding_window.begin());
            sliding_window.insert(sliding_window.end(),next_value); // Generate new sliding window
            output_vector.insert(output_vector.end(),next_value); // Insert next value into the output vector
            count++;
        }
        print_vector(output_vector);
        cout<<"\n";
        cout<<"\n";
        cout<<"# of random words to generate (0 to quit) ?";
        cin>> word_count;
    }
    
    printf("Thank you for using!");

    return 0;
}


/** n_grams_map is a function to build N-Grams Map taking next word from document
and current vector and to store in the map */
void n_grams_map(string word, map<vector<string>,vector<string>>::iterator it,
                 map<vector<string>,vector<string>> &txt_map,
                 vector<string>&vector_N){

    vector<string> value;
    value.insert(value.end(),word);
    it = txt_map.find(vector_N);

    // If there is a existing record in the map
    if (it!=txt_map.end()){
        vector<string> temp;
        temp = it->second;
        temp.insert(temp.end(),word);
        it->second = temp;
    // Add a record to the map if there is no record
    }else{
       txt_map.insert(pair<vector<string>,vector<string>>(vector_N, value));
    }
    // Sliding window
    vector_N.erase(vector_N.begin());
    vector_N.insert(vector_N.end(),word);

}

// A function to print result vector
void print_vector(vector <string> vec2_Print){
    cout<<"...";
    for (int i=0; i<vec2_Print.size();i++){
        cout<<vec2_Print[i]<<" ";
    }
    cout<<"...";

}

// A function to generate a random word from a string vector
string random_vector(vector<string> input_vector){
    int x = rand() % input_vector.size();
    return(input_vector[x]);
}
