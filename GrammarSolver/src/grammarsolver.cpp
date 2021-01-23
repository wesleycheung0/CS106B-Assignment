/*
 * File: grammarsolver.cpp
 * --------------------------
 * Name:
 * Section leader:
 * This file contains grammar generating code for CS106B.
 */

#include "grammarsolver.h"
#include "strlib.h"
#include "simpio.h"
#include <string>
#include <vector>
#include <map>

using namespace std;

vector<string> vectorOfVector2Vector(vector<vector<string>> vecvec);
vector <string> grammarGenerateHelper(map<string,vector<string>> gram,vector<string> output);
vector<string> vectorOfVector2Vector(vector<vector<string>> vecvec);
vector<string> selectNextLevel(vector<string> input);
string condensed_vector(vector<string> input);
bool checkKeyNotInMap(map<string,vector<string>> gram, vector<string> input);


/**
 * Generates grammar for a given symbol a certain number of times given
 * a BNF input file.
 *
 * This will be called by grammarmain.cpp.
 *
 * @param input - Input stream of BNF file.
 * @param symbol - Symbol to generate
 * @param times - Number of times grammar is generated
 * @return Vector of strings of size times with random generations of symbol
 */
Vector<string> grammarGenerate(istream& input, string symbol, int times) {
    map<string,vector<string>> grammar;
    string line;
    map<string,vector<string>>::iterator it = grammar.begin();
    while (getline(input, line)){
        vector<string> key = stringSplit(line, "::=");
        grammar.insert(it, pair<string,vector<string>> (key[0], {key[1]}));
    }
    Vector <string> output;
    for (int i=0; i<times;i++){
        vector<string> temp = grammarGenerateHelper(grammar, {symbol});
        output.insert(i, condensed_vector(temp));
    }

    return output;
}

// The helper function
vector <string> grammarGenerateHelper(map<string,vector<string>> gram,vector<string> output){
    //Base Case (if the output vector does not contains any key value from the map)
    if (checkKeyNotInMap(gram, output)){
        return output;
    }else{

        // Using Randomselection to generate a vector that after random selection and without "|"
        vector<vector<string>> temp_vec;

        //Using for loop to find level+1 nodes
        for (int i=0; i<output.size(); i++){
            vector <string> temp;
            if(gram.find(output[i])!=gram.end()){
                temp = gram[output[i]];
                temp_vec.insert(temp_vec.end(),temp);
            }else{
                temp_vec.insert(temp_vec.end(),{output[i]});
            }
        }

        // Vectorize vector of vector
        output = vectorOfVector2Vector(temp_vec); // Transfor vector of vector to vector
        output = selectNextLevel(output);
        return grammarGenerateHelper(gram, output) ;
    }
}




//Return a string that is condensed form of vector string

string condensed_vector(vector<string> input){
    string output_s;

    for (int i=0; i<input.size()-1; i++){
        output_s+=input[i]+" ";
    }
    output_s+=input[input.size()-1];
    return output_s;
}



//Check whether the output vector contains key in the map
bool checkKeyNotInMap(map<string,vector<string>> gram, vector<string> input){
    for(int i=0; i<input.size(); i++){
        if(input[i].find("<")!=string::npos){
            return false;
            break;
        }
    }
    return true;

}

// Return a vector of string from vector of vector of string
vector<string> vectorOfVector2Vector(vector<vector<string>> vecvec){
    vector<string> vec;
    for(auto && v : vecvec){
      vec.insert(vec.end(), v.begin(), v.end());
    }
    return vec;
}

// Return a vector of the symbol/ word for next level
vector<string> selectNextLevel(vector<string> input){
    vector<vector<string>> temp;
    for (int i=0; i<input.size(); i++){

        if (input[i].find("|")!=string::npos){
            // Split by "|"

            vector <string> temp = stringSplit(input[i], "|");
            string temp_2 = temp[rand() % temp.size()];

            //store the random selected string back to the original vector
            input[i] = temp_2;
        }

        if(input[i].find(" ")!=string::npos){
            temp.insert(temp.begin()+i,stringSplit(input[i], " "));
        }else{
            temp.insert(temp.begin()+i,{input[i]});
        }
    }
    vector<string> temp_2 = vectorOfVector2Vector(temp);
    return temp_2;
}
