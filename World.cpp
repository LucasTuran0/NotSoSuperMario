
#include "World.h"
#include <string>
using namespace std;
World::World(){

}

World::World(int s, int ml, int pc, int pm, int pg, int pk){        //constructor
    size = s;
    maxLevel = ml;
    percentCoins = pc;
    percentMushrooms = pm;
    percentGoomba = pg;
    percentKoopa = pk;
    levelNum = 0;
    srand(time(NULL));
    fp.fileOut();
}

World::~World(){            //destructor
    for(int i = 0; i < size; i++){
        delete[] world[i];
    }
    delete[] world;
    cout << "World has been deallocated" << endl;
}

void World::generate(){         //allocates the level array
    world = new char*[size];
    for(int i = 0; i < size; i++){
        world[i] = new char[size];
    }
}

void World::nextLevel(){        //moves onto the next level when called
    if(levelNum > 0) {
        for(int i = 0; i < size; i++){
        delete[] world[i]; 
        }
        delete[] world; 
        world = nullptr; 
    }
    levelNum++;
    generate();
    populate(percentCoins, percentMushrooms, percentGoomba, percentKoopa);
    if(levelNum != maxLevel+1){
        cout << "+=+=+=+=+=+=+=+=+=+=+=+=+=+Onto the next level!+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+" << endl;
        cout << "Level " << levelNum << endl;  
    }   
}

void World::print(){            //prints the current level array
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            cout << world[i][j] << ' ';
        }
        cout << endl;
    }
}

int World::locateMarioRow(){        //locates the row mario is in
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if(world[i][j] == 'H'){
                return i;
                break;
            }
        }
    }
    cout << "something went wrong in locate row" << endl;
    return -1;
}
int World::locateMarioColumn(){         //locates the column mario is in
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if(world[i][j] == 'H'){
                return j;
            }
        }
    }
    cout << "something went wrong in locate column" << endl;
    return -1;
}

bool World::interaction(int row, int column){       //decides if mario sucecfully interacted with the chosen index
    int num = rand() % 100;
    switch(world[row][column]){
        case 'x':       //nothing
        cout << "the position is empty" << endl;
        return true;
        break;

        case 'c':       //coin
        mario.collectCoin();
        return true;
        break;

        case 'm':       //mushroom
        mario.collectMushroom();
        break;

        case 'g':       //goomba
        if(num <= 80){
            cout << "Mario defeated a goomba" << endl;
            mario.enemyDefeated();
            return true;
        }else{
            cout << "Mario lost to a goomba" << endl;
            mario.loss();
            return false;
        }
        break;

        case 'k':       //koopa
        if(num <= 60){
            cout << "Mario defeated a koopa" << endl;
            mario.enemyDefeated();
            return true;
        }else{
            cout << "Mario lost to a koopa" << endl;
            mario.loss();
            return false;
        }
        break;

        case 'b':       //boss
        cout << "-- Mario found the boss -- " << endl;
        while(true){
            if(num <= 50){
                cout << "---Mario beat the boss!---" << endl;
                nextLevel();    
                return true;
                break;
            }else{
                cout << "--Mario lost to the boss...--" << endl;
                mario.loss();
                mario.loss();
                num = rand() % 100;
            }
        }
        break;

        case 'w': //warp pipe
        cout << "--Mario found a warp pipe!--" << endl;
        nextLevel();
        break;

        default:
        cout << "default case in world.interaction" << endl;
        return false;
    }
}

void World::moveCondition(int row, int column){     //moves mario if he succesfully interacted
    int tempRow = locateMarioRow();
    int tempColumn = locateMarioColumn();

    if(interaction(row, column) == true){
        world[tempRow][tempColumn] = 'x'; //old spot
        
        world[row][column] = 'H'; //new spot
    }else{
        cout << "------Mario stays still------" << endl;
    }
}


void World::marioMove(){        //decides where mario tries to move
    int direction = rand() % 4;

    int tempRow = locateMarioRow();
    int tempColumn = locateMarioColumn();

    switch(direction){  //implement interaction
        case 0:
        //move up
        if(locateMarioRow() - 1 < 0){ //idk if this works
            moveCondition(size-1, locateMarioColumn());
        }else{
            moveCondition(locateMarioRow()-1, locateMarioColumn());
        }
        cout << "------Mario moves up------" << endl;
        break;

        case 1:
        //move right
        if(locateMarioColumn() + 1 > size-1){ //idk if this works
            moveCondition(locateMarioRow(), 0);
        }else{
            moveCondition(locateMarioRow(), locateMarioColumn()+1);
        }
        cout << "------Mario moves right------" << endl;
        break;

        case 2:
        //move down
        if(locateMarioRow() + 1 > size-1){ //idk if this works
            moveCondition(0, locateMarioColumn());
        }else{
            moveCondition(locateMarioRow()+1, locateMarioColumn());
        }
        cout << "------Mario moves down------" << endl;
        break;

        case 3:
        //move left
        if(locateMarioColumn() - 1 < 0){ //idk if this works
            moveCondition(locateMarioRow(), size-1);
        }else{
            moveCondition(locateMarioRow(), locateMarioColumn()-1);
        }
        cout << "------Mario moves left------" << endl;
        break;

        default:
        //something went wrong
        cout << "something went wrong in world.move()" << endl;
    }
}

bool World::win(){          //game end (win)
    if(levelNum == maxLevel+1){
        cout << "The princess has been saved" << endl;
        exit(0);
    }
}

void World::populate(double percentCoins, double percentMushrooms, double percentGoomba, double percentKoopa){          //populates the level array
    int numRand = rand() % 100;
    int randRow = rand() % size;
    int randColumn = rand() % size;
    int area = size * size;
    double numCoins = (percentCoins/100) * area;
    double numMushrooms = (percentMushrooms/100) * area;
    double numGoomba = (percentGoomba/100) * area;
    double numKoopa = (percentKoopa/100) * area;
    double numMario = 1;
    double numBoss = 1;
    double numPipe = 1;

    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            world[i][j] = 'x';
        }
    }

    for(int i = 0; i < numCoins; i++){
        if(world[randRow][randColumn] == 'x'){
            world[randRow][randColumn] = 'c';
            randRow = rand() % size;
            randColumn = rand() % size;
        }else{
            randRow = rand() % size;
            randColumn = rand() % size;
        }
    }

    for(int i = 0; i < numMushrooms; i++){
        if(world[randRow][randColumn] == 'x'){
            world[randRow][randColumn] = 'm';
            randRow = rand() % size;
            randColumn = rand() % size;
        }else{
            randRow = rand() % size;
            randColumn = rand() % size;
        }
    }

    for(int i = 0; i < numGoomba; i++){
         if(world[randRow][randColumn] == 'x'){
            world[randRow][randColumn] = 'g';
            randRow = rand() % size;
            randColumn = rand() % size;
        }else{
            randRow = rand() % size;
            randColumn = rand() % size;
        }
    }


    for(int i = 0; i < numKoopa; i++){
        if(world[randRow][randColumn] == 'x'){
            world[randRow][randColumn] = 'k';
            randRow = rand() % size;
            randColumn = rand() % size;
        }else{
            randRow = rand() % size;
            randColumn = rand() % size;
        }
    }


    while(true && levelNum != maxLevel){
        if(world[randRow][randColumn] != 'H' && world[randRow][randColumn] != 'b'){
            world[randRow][randColumn] = 'w';
            randRow = rand() % size;
            randColumn = rand() % size;
            break;
        }else{
            randRow = rand() % size;
            randColumn = rand() % size;
        }
    }

    while(true){
        if(world[randRow][randColumn] != 'w' && world[randRow][randColumn] != 'H'){
            world[randRow][randColumn] = 'b';
            randRow = rand() % size;
            randColumn = rand() % size;
            break;
        }else{
            randRow = rand() % size;
            randColumn = rand() % size;
        }
    }

    while(true && levelNum == 1){
        if(world[randRow][randColumn] != 'w' && world[randRow][randColumn] != 'b'){
            world[randRow][randColumn] = 'H';
            randRow = rand() % size;
            randColumn = rand() % size;
            break;
        }else{
            randRow = rand() % size;
            randColumn = rand() % size;
        }   
    }
}
