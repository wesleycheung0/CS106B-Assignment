// This is a .h file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#ifndef _boggle_h
#define _boggle_h

#include <iostream>
#include <string>
#include "lexicon.h"
#include <vector>
#include "grid.h"
using namespace std;

class Boggle {
public:
    Boggle(Lexicon& dictionary, string boardText = "");
    char getLetter(int row, int col);
    bool checkWord(string word);
    bool humanWordSearch(string word);
    Set<string> computerWordSearch();
    int getScoreHuman();
    int getScoreComputer();

    // TODO: add any other member functions/variables necessary
    bool humanWordSearchHelper(string word, Grid<bool>, int row, int col);
    string get_Board();
    Grid<char> randomBoard(string* cubes);
    friend ostream& operator<<(ostream& out, Boggle& boggle);
    bool checkLetterInput (string& letter);
    void printWordScore();
    void wordAppend(string& new_word);
private:
    // TODO: add any other member functions/variables necessary
    string random_letter;
    Grid<char>final_letter;
    vector<string> words;
    Lexicon word_dictionary;
    int human_score;
    int computer_score;
    void computerWordSearchHelper(int row, int col, Grid<bool>&checked, string word, vector<string> &word_list);



};

#endif // _boggle_h
