// This is a .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

/* DutyL
1. Interactive with GUI
2. Call function from boggle class
*/

#include "lexicon.h"
#include <string>
#include "simpio.h"
#include "Boggle.h"
#include "console.h"


using namespace std;
void wordsScore();

void playOneGame(Lexicon& dictionary) {
    string letter_board = "";
    if (!getYesOrNo("Do you want to generate a random board")){
        //Missing Exception
         letter_board = getLine("Type the 16 letters to appear on the board:");
    }
    //Initiate the Boggle
    Boggle game(dictionary, letter_board);

    clearConsole();
    cout<<"It's your turn!"<<endl;
    cout<<game<<endl;

    game.printWordScore();

    string line = getLine("Type a word (or Enter to stop): ");
//    cin.ignore();
    clearConsole();
    while(line!=""){
        if (line.empty()) break;
        line = toUpperCase(line);
        clearConsole();
        //Add word validation
        while(!game.checkWord(line)){
            cout<<"You must enter an unfound 4+ letter word from the dictionary."<<endl;
            cout<<game;
            game.printWordScore();
            line = getLine("Type a word (or Enter to stop): ");
            clearConsole();
        }

        if (game.checkWord(line)){
            game.wordAppend(line);
            cout<<"You found a new word! "<<line<<endl;
            cout<<game;
            game.printWordScore();
            line = getLine("Type a word (or Enter to stop): ");
        }
    }
    clearConsole();
    cout<<"It's my turn! \n";
    Set<string> computer_word = game.computerWordSearch();
    const auto separator = ",";
    const auto* sep = "";
    cout<<"My words ("<<computer_word.size()<<"): {";
    for (auto word:computer_word){
        cout << sep << word;
        sep = separator;
    }
    cout<<"}\nMy Score: "<< game.getScoreComputer()<<"\n";
    cout<<"Ha ha ha, I destroyed you. Better luck next time, puny human!\n\n";
}
