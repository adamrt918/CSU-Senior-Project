#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <random>

using namespace std;


// Class to hold the individual events for different pages 
class Player
{
    public:
    Player();
    ~Player();
    
    int random(int lowerBound, int upperBound);
    int chooseSanity(int lowerBound, int upperBound);
    int chooseRep(int lowerBound, int upperBound);



    int getHealth();
    void setHealth(int num);

    int getSanity();
    void setSanity(int num);

    int getRep();
    void setRep(int num);

    random_device getRd();
    random_device setRd();

    bool getInsane();
    void setInsane(bool sane);

    bool getDead();
    void setDead(bool death);

    private:
        int health;
        int sanity;
        int reputation;

        //Distribution variable
        uniform_int_distribution<int> roll;

        //Random device to use for the seed.
        int rd;
        
        //Twister for random number seed
        mt19937_64 seed;

        bool insane;
        bool dead;
};

#include "player.cpp"
#endif