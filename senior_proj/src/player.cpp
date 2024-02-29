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

int Player::random(int lowerBound, int upperBound){
    roll = uniform_int_distribution<int>(lowerBound, upperBound);
    return roll(seed);
}

int Player::getHealth(){ return health;}
void Player::setHealth(int num){health = num;}

int Player::getSanity(){return sanity; }
void Player::setSanity(int num){sanity = num;}

int Player::getRep(){return reputation;}
void Player::setRep(int num){reputation = num;}

bool Player::getInsane(){return insane;}
void Player::setInsane(bool sane){insane = sane;
cout << "insane = " << sane << endl;
}

bool Player::getDead(){return dead;}
void Player::setDead(bool death){dead = death;}

#endif