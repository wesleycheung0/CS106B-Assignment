// This is a .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: Human score is three when initialized
// TODO: Missing ": {}" after "Your word"
// TODO: Missing : after "Your score"
// TODO:


// No representation exposure
// Do all Console I/O

#include <iostream>
#include "Boggle.h"
#include "shuffle.h"
#include <array>
#include <string>
#include "grid.h"
#include <algorithm>

using namespace std;

// letters on all 6 sides of every cube
static string CUBES[16] = {
    "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
    "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
    "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
    "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

// letters on every cube in 5x5 "Big Boggle" version (extension)
static string BIG_BOGGLE_CUBES[25] = {
   "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
   "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
   "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
   "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
   "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};



Boggle::Boggle(Lexicon& dictionary, string boardText) {
    // TODO: implement
    // To initialize the boggle board with the given dictionary and board Text
    // if the string is empty generate a random text
    // Case insensitive

    word_dictionary = dictionary;
    human_score = 0;
    Grid<char>final_letter(4,4);
    if (boardText == ""){
        Boggle::final_letter = randomBoard(CUBES);
    }else{
        Grid<char>temp(4,4);
        for (int i=0; i<4;i++){
            for (int j=0; j<4; j++){
                temp[i][j] = toupper(boardText[i*4+j]);
            }
        }
        Boggle::final_letter = temp;
    }

    // To Validate the non-random letter input


}

char Boggle::getLetter(int row, int col) {

    //Missing exception
    if (!final_letter.inBounds(row, col)){
            throw invalid_argument("Input Out of Bound");
}
    return Boggle::final_letter[row][col];
}

bool Boggle::checkWord(string word) {
    // TODO: implement
    //Check Word:1. In the dictionary , 2. length >=4 3. has not been found yet
    // case insentitive
    //

    if (word.size()>3 && word_dictionary.contains(word) && humanWordSearch(word) ){
        human_score+=word.size()-3;
        return true;
    }
    return false;
}

bool Boggle::humanWordSearch(string word) {
    // Recursive Tracking
    // Animated Search with 100ms delay
    // case insensitive

    Grid<bool> checked(4, 4);
    checked.fill(false);

    for (int i=0; i<final_letter.numRows();i++){
        for (int j=0; j<final_letter.numCols();j++){
            if (final_letter[i][j] == word[0]){
                if (Boggle::humanWordSearchHelper(word.substr(1), checked, i, j)){
                    return true;
            }
        }
        }
    }
    return false;   // remove this
}

bool Boggle::humanWordSearchHelper(string word, Grid<bool> checked, int row, int col){
    // if word is empty, the input word exists
    if (word.empty()){
        return true;
    }

    // Check all the neightbor if the next char exists
    for (int row_i=-1; row_i<2; row_i++){
        for (int row_j=-1; row_j<2; row_j++){
            if (final_letter.inBounds(row+row_i,col+row_j) &&
                    final_letter[row+row_i][col+row_j] == word[0] &&
                    checked[row+row_i][col+row_j] !=1){
                checked[row+row_i][col+row_j] = true;
                if (humanWordSearchHelper(word.substr(1), checked, row+row_i,col+row_j)){
                    return true;
                }
                //Backtrack
                checked[row+row_i][col+row_j] = false;
            }
        }
    }
    return false;
    }

// Return the score of human
int Boggle::getScoreHuman() {


    return human_score;
}

Set<string> Boggle::computerWordSearch() {

    Set<string> result;

    for (int i=0; i<final_letter.numRows();i++){
        for (int j=0; j<final_letter.numCols();j++){
            string word;
            vector<string> word_list;
            Grid<bool> checked(4, 4);
            checked.fill(false);
            checked[i][j]=true;
            computerWordSearchHelper(i, j, checked, word+=final_letter[i][j], word_list);
            for (int i=0; i<word_list.size();i++){
                result.insert(word_list[i]);
                computer_score+=word_list[i].size()-3; // score equals to word length minus 3
            }
        }
    }
    return result;

}

void Boggle::computerWordSearchHelper(int row, int col, Grid<bool>&checked, string word, vector<string> &word_list){
    if (!word_dictionary.containsPrefix(word)){
        return;
    }

    if (word_dictionary.contains(word) && word.size()>3 && find(word_list.begin(), word_list.end(), word)==word_list.end()){
        word_list.insert(word_list.begin(), word);
    }
    // for every neighbor of the given word

    for (int row_i=-1; row_i<2; row_i++){
        for (int col_j=-1; col_j<2; col_j++){

            // recursion word selection not following the word position ( randomly)
            if (final_letter.inBounds(row_i+row, col_j+col) && checked[row_i+row][col_j+col]!=true){
                word+=final_letter[row_i+row][col_j+col];
                checked[row_i+row][col_j+col] =true;
                computerWordSearchHelper(row_i+row, col_j+col, checked, word, word_list);

                // Backtracking
                checked[row_i+row][col_j+col] =false;
                word = word.substr(0, word.size()-1);
            }

        }
    }
    return;
}



int Boggle::getScoreComputer() {

    return computer_score;   // remove this
}

// To generate random board from the string input
Grid<char> Boggle::randomBoard(string *cubes) {
    Grid<char> random_letter(4,4);
    srand(time(NULL));
    int count = 0;
    for (int i=0; i<4;i++){
        for (int j=0; j<4; j++){
            random_letter[i][j] = cubes[count][rand() % 6];
            count++;
        }
    }
    return random_letter;
}

string Boggle::get_Board(){
    return Boggle::final_letter.toString();
}


ostream& operator<<(ostream& out, Boggle& boggle) {
    // TODO: implement
    // It should print a 4x4 grid of character representing the board
    // Only works for regular size board
        out<<boggle.final_letter.toString2D();
        out<<"\n";
    return out;
}

// To validate the letter input for the non-random letter board
bool Boggle::checkLetterInput (string& letter){
    if (letter.length() == 16){
        for (int i =0; i<16; i++){
            if (letter[i]>='a' && letter[i]<='Z'){
                return true;
            }
        }
    }return false;
}

void Boggle::wordAppend(string& new_word){
        words.insert(words.end(),new_word);
    }

void Boggle::printWordScore(){ // TODO: The word prints without  {}:
    cout<<"Your words ("<<words.size()<<"): {";
    for (int i=0; i<words.size();i++){
        if (i!=words.size()-1){
            cout<<"\""<<words[i]<<"\", ";
        }else{
            cout<<"\""<<words[words.size()]<<"}"<<endl;
        }
    }
    if (words.size()==0){
        cout<<"}\n";
    }
    cout<<"Your score: "<<Boggle::getScoreHuman()<<endl;
}

