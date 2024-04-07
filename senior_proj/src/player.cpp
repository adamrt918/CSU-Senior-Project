#ifdef PLAYER_H

Player::Player()
{
    health = 10;
    sanity = 20;
    reputation = 10;
    
    //Seed the twister
    seed.seed(random_device{}());
}

Player::~Player(){}

int Player::random(int* bounds){
    roll = uniform_int_distribution<int>(bounds[0], bounds[1]);
    return roll(seed);
}

bool Player::checkDeath(){
    if (health < 1)
        return true;
    return false;
}

bool Player::checkInsanity(){
    if (sanity < 1)
        return true;    
    return false;
}

void Player::resetStats(){
    health = 10;
    sanity = 20;
    reputation = 10;
}

int Player::getHealth(){ return health;}
void Player::setHealth(int num){
    if (num >= 0)
        health = num;
    else 
        health = 0;
}

int Player::getSanity(){return sanity; }
void Player::setSanity(int num){
    if (num >= 0)
        sanity = num;
    else 
        sanity = 0;
}

int Player::getRep(){return reputation;}
void Player::setRep(int num){
    if (num >= 0)
        reputation = num;
    else 
        reputation = 0;
}


#endif