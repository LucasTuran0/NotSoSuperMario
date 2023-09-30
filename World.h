
#ifndef WORLD_H
#define WORLD_H

#include "Mario.h"
#include "fileProcessor.h"


using namespace std;

class World{
    public:
    World();
    World(int size, int maxLevel, int percentCoins, int percentMushrooms, int percentGoomba, int percentKoopa);
    virtual ~World();
    void generate();
    void populate(double percentCoins, double percentMushrooms, double percentGoomba, double percentKoopa);
    void marioMove();
    int locateMarioColumn();
    int locateMarioRow();
    bool interaction(int row, int column);
    void nextLevel();
    void moveCondition(int row, int column);
    void place(int n, char c);
    bool win();
    void print();
    int levelNum;


    private:
    int size;
    int maxLevel;
    int numCoins;
    int numMushrooms;
    int numNothing;
    int numGoomba;
    int numKoopa;
    int percentCoins;
    int percentMushrooms;
    int percentGoomba;
    int percentKoopa;
    char** world;
    Mario mario;
    fileProcessor fp;

};
#endif