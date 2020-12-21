// The main file of game of life

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "console.h"
#include "filelib.h"
#include "gwindow.h"
#include "simpio.h"
#include "strlib.h"
#include "lifegui.h"
#include "grid.h"
using namespace std;


Grid<char> grid_generation(Grid<char>&old_grid, int x, int y, string wrap);
void print_grid(Grid<char> input_grid);
int find_sum_neighbor(Grid<char> &old_grid, int r, int c, int x, int y, string wrap);

int main() {
    // Game Title and Introduction
    cout << "Welcome to the CS 106B Game of Life," << endl;
    cout << "a simulation of the lifecycle of a bacteria colony" << endl;
    cout << "Cells (X) live and die by the folliwung rules:" << endl;
    cout << "- A cell with 1 or fewer neighbors dies." << endl;
    cout << "- Locations with 2 neighbors remain stable." << endl;
    cout << "- Locations with 3 neighbors will create life." << endl;
    cout << "- A cell with 4 or more neighbors dies." << endl;

    // Importing file
    string file_name;
    string wrap_bool;
    file_name = getLine(" Grid input file name?"); // Alternative using cin from istream
    wrap_bool = getLine(" Should the simulation wrap around the grid (y/n)");

    ifstream txt_file;
    txt_file.open(file_name);

    // Check if file exist
    if(txt_file.fail()){
        cout << " Error Reading Txt File" <<endl;
    }

    // Creating Grid
    int x, y;
    txt_file >> x;// Number of Row
    txt_file >> y;// Number of Columns
    Grid<char> grid(x, y);

    // Storing Grid
    char token;
    for (int r = 0; r< x; r++){
        for (int c =0; c< y; c++){
            txt_file >> token;
            grid[r][c] = token;
        }
    }
    string input;
    print_grid(grid);
    cout<< "\r" <<endl;

    //
    while (input != "q"){
        input = getLine("a)nimate, t)ick, q)uit?");
        if (input == "a"){
            string frame;
            int frame_i;
            frame = getLine("How many frames?");
            frame_i = stringToInteger(frame);
            for (int i=0; i<frame_i+1;i++){
                grid = grid_generation(grid,x, y, wrap_bool);
                print_grid(grid);
                pause(500);
                clearConsole();
            }

        }
        else if(input == "t"){
            grid = grid_generation(grid,x, y, wrap_bool);
            print_grid(grid);
        }
        else if (input == "q"){
        }
        else{
            cout << " Invalid Error"<< endl;
        }
    }
    cout << "Have a nice Life!" << endl;
    return 0;
}



void print_grid(Grid<char> input_grid){
    int x;
    int y;
    x = input_grid.numRows();
    y = input_grid.numCols();

    for (int r = 0; r< x; r++){
        for (int c =0; c< y; c++){
            cout<<input_grid[r][c]<<"";
        }
        cout<< "\r" <<endl;
    }
}


// Generating the new grid based on old grid
Grid<char> grid_generation(Grid<char>&old_grid, int x, int y, string wrap){

    Grid<char> new_grid(x, y);
    for (int r = 0; r<x; r++){
        for (int c =0; c<y; c++){
            int sum_neightbor = find_sum_neighbor(old_grid, r, c, x, y, wrap);
            if (sum_neightbor<2 || sum_neightbor>3){
               new_grid.set(r,c,'-');
            }
            else if (sum_neightbor == 2){
               new_grid.set(r,c, old_grid.get(r,c));
            }
            else{
               new_grid.set(r,c,'X');
            }
        }
    }

    return new_grid;
}

// Finding the sum of neighbor of the given grid location
int find_sum_neighbor(Grid<char> &old_grid, int r, int c, int x, int y, string wrap){
    int sum_neightbor = 0;
    for (int n=r-1;n<r+2; n++){
        for (int k=c-1; k<c+2; k++){
            if (wrap =="y"){
                if (n==r && k==c){}
                else if(!old_grid.inBounds(n,k)){
                        int n_new;
                        int k_new;
                        n_new = (n+x) % x;
                        k_new = (k+y) % y;
                        if (old_grid.get(n_new,k_new) == 'X'){
                            sum_neightbor++;
                    }
                }
                 else if (old_grid.inBounds(n,k) && old_grid.get(n,k) == 'X'){
                        sum_neightbor++;
                 }
            }

            else{
                if (n==r && k==c){}
                else if(old_grid.inBounds(n,k) && old_grid.get(n,k) == 'X'){
                        sum_neightbor++;
            }
            }
    }
    }
    return sum_neightbor;
}

