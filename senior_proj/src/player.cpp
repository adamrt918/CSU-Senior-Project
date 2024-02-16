#ifdef PLAYER_H

Player::Player()
{
     health = 10;
     sanity = 20;
     reputation = 10;
}

Player::~Player(){}

    int Player::getHealth(){ return health;}
    void Player::setHealth(){}

    int Player::getSanity(){return sanity; }
    void Player::setSanity(){}

    int Player::getRep(){return reputation;}
    void Player::setRep(){}

#endif