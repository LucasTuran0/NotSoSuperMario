
#ifndef MARIO_H
#define MARIO_H

#include <string>
#include <iostream>
#include <cstdlib>
#include "fileProcessor.h"
using namespace std;

class Mario{
    public:
    Mario();
    Mario(int numLives);
    virtual ~Mario();
    void coinToLife();  //not sure if this is needed 
    void collectCoin();
    void enemyDefeated();
    void collectMushroom();
    void enemyToLife(); //not sure if this is needed 
    void death();
    void loss();
    bool gameOver();
    int numLives;
    int getNumCoins();
    int powerLevel;



    private:
    int enemiesDefeated;
    int numCoins;
    fileProcessor fp;
    
};

#endif