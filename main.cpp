#include "World.h"

#include <fstream>
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {

    int numLives;
    int size;
    int maxLevel;
    int percentCoins;
    int percentMushrooms;
    int percentGoomba;
    int percentKoopa;
    
    ifstream inputFile("input.txt");
    
    if(!inputFile) {
        cerr << "Unable to open file input.txt";
        return 1;
    }
    
    inputFile >> maxLevel >> size >> numLives >> percentCoins >> percentMushrooms >> percentGoomba >> percentKoopa; //takes in input from input file
    inputFile.close();

    World world(size, maxLevel, percentCoins, percentMushrooms, percentGoomba, percentKoopa);   //initializes world

    
    Mario mario(numLives);  //initializes mario

    fileProcessor fp;
    fp.fileOut();       //redirects cout into txt file

    world.nextLevel();
    cout<< "starting world" << endl;
    world.print();

    int i = 0;
    while(true){        //game loop
       cout << "move " << i << endl;
       cout << "Level number: " << world.levelNum << endl;
       cout << "Mario position " << world.locateMarioRow() << ", " << world.locateMarioColumn() << endl;
        world.marioMove();
        world.print();
        world.win();
        cout << "Num lives: " << numLives << endl;
        cout << "----------------" << endl; 
        i++;
    }
}
