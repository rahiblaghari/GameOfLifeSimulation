// Author:     Rahib R Laghari
// Course:     CS1337.010
// Date:       5/7/2021
// Assignment: EC4 - Conway's game of life
// Compiler:   Visual Studio Code

// Description:
// This program plays a simulation of life that will show generating pixels being "life"
// according to the rules in the instructions, and dying by rules too.
// This will be shown in . (dead) and O (live), and create a unique pattern.

// Change log:
// 5/7 - initialized arrays, got it to run for feeding in a percent and got an output, ended with contents in
// get next array bool
// 5/8 - finished the loop, got it to refresh and made it more organized into functions for entering percent
// 5/9 - fixed and setup the simulation for an input file, changed some O and 0 in the file and added sizeX and
// sizeY so it would change size based on input file, with maximum size of 50x50

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

void createListCells(int percentLive, bool liveCellsArray[51][51], char currentCells[51][51]){
    percentLive *= 25;
    int i,j = 0;
    int percCheck = 0;
    while (j<50){
        liveCellsArray[i][j] = rand()%2;
        if(liveCellsArray[i][j]){
            currentCells[i][j] = 'O';
            percCheck += 1;
            if(percCheck>percentLive){
                while(j<50){
                    while(i<50){
                        i++;
                        currentCells[i][j] = '.';
                        liveCellsArray[i][j] = 0;
                        //cout << currentCells[i][j];
                    }
                //cout << endl;
                i = -1;
                j++;
                }
                
            }

        }
        else{
            currentCells[i][j] = '.';
        }
        //cout << currentCells[i][j];
        i++;
        if(i%50 == 0 || i > 49){
            j++;
            //cout << endl;
            i = 0;
        }
    }
}

void readInFile(string inputFileName, bool liveCellsArray[51][51], char currentCells[51][51], int &sizeX, int &sizeY){
    ifstream inFile (inputFileName);
    string failedAttempt;
    string line;
    int failedPercent;
    int i,j = 0;
    char getFirstVal;
    if(inFile){
        while(!(inFile.eof())){
            getFirstVal = inFile.peek();
            getline(inFile, line);
            while (getFirstVal == '#' || getFirstVal == '\13' || getFirstVal == '\n'){
                cout << line << endl;
                getline(inFile, line);
                getFirstVal = inFile.peek();
            }
            for(int index = 0; index < line.length(); index++){
                currentCells[i][j] = line[index];
                if(currentCells[i][j] == 'O'){
                    //cout << currentCells[i][j];
                    liveCellsArray[i][j] = 1;
                }
                else{
                    //cout << currentCells[i][j];
                    liveCellsArray[i][j] = 0;
                }
                i++;
                //cout << j << " " << i << endl;
                if (i%line.length() == 0){
                    j++;
                    i = 0;
                }
                sizeX = line.length();
            }
            sizeY++;
            //cout << sizeX << " " << sizeY << endl;
            //cout << endl;
        }
    }
    else{
        cout << "File was unable to open, Do you want to try another input file name: ";
        cin >> failedAttempt;
        if (failedAttempt == "yes" || failedAttempt == "y" || failedAttempt == "Yes"){
            cout << "And what will be this file name: ";
            cin >> failedAttempt;
            readInFile(failedAttempt, liveCellsArray, currentCells, sizeX, sizeY);
        }
        else{
            sizeX = 50;
            sizeY = 50;
            cout << "What percent of the cells would you desire be live: ";
            cin >> failedPercent;
            createListCells(failedPercent, liveCellsArray, currentCells);
        }
    }
    // cout << "X: " << sizeX << endl;
    // cout << "Y: " << sizeY << endl;
}

void refresh(){
    for(int x = 0; x < 100000000; x++){

    }
    system("clear");
}

void printAndSave(char currentCells[51][51], char prevCells[51][51], int sizeX, int sizeY){
    for(int j = 0; j<sizeY; j++){
       for(int i = 0; i<sizeX; i++){
           cout << currentCells[i][j];
           prevCells[i][j] = currentCells[i][j];
       }
       cout << endl;
    }
}

void getNextArrayBool(char prevCells[51][51], bool liveCells[51][51], int sizeX, int sizeY){
    int counter = 0;
    for(int j = 0; j<sizeY;j++){
        for(int i = 0; i<sizeX; i++){
            //cout << i <<  " " << j << endl;
            if(i>0 && j>0){
                if(prevCells[i-1][j-1] == 'O'){
                    counter ++;
                }
            }
            if(i>0){
                if(prevCells[i-1][j] == 'O'){
                    counter ++;
                }
            }
            if(i>0 && j<sizeY){
                if(prevCells[i-1][j+1] == 'O'){
                    counter ++;
                }
            }
            if(j>0){
                if(prevCells[i][j-1] == 'O'){
                    counter ++;
                }
            }
            if(j<sizeY){
                if(prevCells[i][j+1] == 'O'){
                    counter ++;
                }
            }
            if(i<sizeX && j<sizeY){
                if(prevCells[i+1][j+1] == 'O'){
                    counter ++;
                }
            }
            if(i<sizeX){
                if(prevCells[i+1][j] == 'O'){
                    counter ++;
                }
            }
            if(i<sizeX && j>0){
                if(prevCells[i+1][j-1] == 'O'){
                    counter ++;
                }
            }
            //////////////
            if(counter<2 || counter >3){
                liveCells[i][j] = 0;
            }
            else if (counter == 2){
                // no change
            }
            else {//counter == 3
                liveCells[i][j] = 1;
            }
            counter = 0;
        }
    }
}

void updateCurrentCells(char currentCells[51][51], bool liveCells[51][51], int sizeX, int sizeY){
    for(int j = 0; j<sizeY; j++){
       for(int i = 0; i<sizeX; i++){
           if(liveCells[i][j] == 0){
               currentCells[i][j] = '.';
           }
           else{
               currentCells[i][j] = 'O';
           }
       }
    }
}

int main(){
// create storage for bool values, which the char will read from to create 'O' and '.'
    char currentCells[51][51];
    char prevCells[51][51];
    bool liveCells[51][51];
// create output arrays to store the live and dead cells and initialize them if path is taken
// if path isn't taken, ask for the input file to insert into array
    string FileQ;
    string inputFile;
    string lin;
    int sizeX = 0;
    int sizeY = 0;
    int percentLive;
    cout << "Do you have an input file you would want used as basis for: ";
    cin >> FileQ;
    if (FileQ == "yes" || FileQ == "y" || FileQ == "Yes"){
        cout << "What is the name of this file: ";
        cin >> inputFile;
        readInFile(inputFile, liveCells, currentCells, sizeX, sizeY);
    }
    else if (FileQ == "no" || FileQ == "n" || FileQ == "No"){
        cout << "What percent of the cells would you desire be live: ";
        cin >> percentLive;
        sizeX = 50;
        sizeY = 50;
        createListCells(percentLive, liveCells, currentCells);
    }
    // print cells, then save the newer cells into a table for previous cells
    printAndSave(currentCells, prevCells, sizeX, sizeY);
    //use prev cells to find next live cells (translation to 1s and 0s)
    // for(int j = 0; j<sizeY; j++){
    //    for(int i = 0; i<sizeX; i++){
    //        cout << liveCells[i][j];
    //    }
    //    cout << endl;
    // }
    getNextArrayBool(prevCells, liveCells, sizeX, sizeY);
    cout << "This is the initial picture of dead and live cells, hit enter to run the simulation";
    cin.ignore();
    getline(cin, lin);
    //cin >> line;
    // use new live cells to find the current cells (translation to .s and 0s), and repeat the cycle
    updateCurrentCells(currentCells, liveCells, sizeX, sizeY);
    while(1){
        // print cells, then save the newer cells into a table for previous cells
        printAndSave(currentCells, prevCells, sizeX, sizeY);
        //use prev cells to find next live cells (translation to 1s and 0s)
        getNextArrayBool(prevCells, liveCells, sizeX, sizeY);
        // use new live cells to find the current cells (translation to .s and 0s), and repeat the cycle
        updateCurrentCells(currentCells, liveCells, sizeX, sizeY);
        refresh();
    }
}