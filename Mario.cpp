

#include "Mario.h"
#include <string>

Mario::Mario(){     //constructor
    numCoins = 0;
    powerLevel = 0;
    enemiesDefeated = 0;
    numLives = 0;
}

Mario::Mario(int nL){       //constructor
    numCoins = 0;
    powerLevel = 0;
    enemiesDefeated = 0;
    numLives = nL;
    fp.fileOut();
}

Mario::~Mario(){
    cout << "Mario has been deleted" << endl;
}

void Mario::coinToLife(){       //checks if mario has enough coins to get an extra life
    if(numCoins == 20){
        numLives += 1;
        numCoins = 0;
        cout << "---Mario gained an extra life---" << endl;
        cout << "num lives = " << numLives << endl;
    }
}

void Mario::enemyDefeated(){        //keeps track of how many enemies mario defeated
    enemiesDefeated++;
    enemyToLife();
}

void Mario::collectCoin(){  //adds to num coins when mario collects a coin
    cout << "==Mario collected a coin==" << endl;
    numCoins++;
    cout << "Coins: " << numCoins << endl;
    coinToLife();
}

void Mario::collectMushroom(){      //adds to power level when mario collects mushrooms
    if(powerLevel < 2){
        powerLevel += 1;
        cout << "---Mario collected a mushroom, current PL = " << powerLevel << endl;
    }else{
        cout << "Max power level reached" << endl;
    }
}

void Mario::enemyToLife(){      //checks if mario defeated enough enemies to earn another life
    cout << "--Mario defeated an enemy--" << endl;
    if(enemiesDefeated == 7){
        numLives += 1;
        enemiesDefeated = 0;
        cout << "---Mario gained an extra life---" << endl;
        cout << "num lives = " << numLives << endl;
    }
}

void Mario::death(){        //reset marios stats when he dies
    powerLevel = 0;
    numLives -= 1;
    numCoins = 0;
    enemiesDefeated = 0;
    cout << "!====Mario lost a life====!" << endl;
    cout << "++++Num Lives remaining " << numLives << endl;
    gameOver();
}

bool Mario::gameOver(){     //ends the game
    if(numLives <= 0){
        cout << "game over!" << endl;
        exit(0);
    }
}

void Mario::loss(){     //runs when mario loses and adjusts stats accordingly
    powerLevel--;
    cout << "-----mario lost a PL------" << endl;
    
    if(powerLevel <= 0){
        death();
    }else{
        cout << "---Current PL = " << powerLevel << endl;
    }
}

int Mario::getNumCoins(){   //returns numCoins
    return numCoins;
}