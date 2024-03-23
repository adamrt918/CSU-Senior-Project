#ifdef TIMER_H

Timer::Timer(){    
    seconds = 10;
    outOfTime = false;
}

Timer::~Timer(){

}

bool Timer::loadTimer(SDL_Renderer* gRenderer){
    if (!timerTexture.loadFromFile("resources/timer_numbers.png", gRenderer)) {   
        cout << "Failed to load timer texture" << endl;
        return false;
    }
    else {
        for (int i = 0; i < 11; i++) {
            timerSprites[i].x = i * 105;
            timerSprites[i].y = 0;
            timerSprites[i].w = 105;
            timerSprites[i].h = timerTexture.getHeight();
        }
        timerSprites[10].w = 210;
    }
    seconds = 10;
    outOfTime = false;
    return true;
}

void Timer::timerEvents(){
    deltaTime = SDL_GetTicks() - startTime;
    if (deltaTime >= countdownInterval && seconds >= 1)
    {
        seconds--;
        startTime = SDL_GetTicks();
    }
    else if (seconds < 1)
        outOfTime = true;

}

LTexture* Timer::getTimerTexture(){return &timerTexture;}
SDL_Rect* Timer::getTimerSprites(){return timerSprites;}
void Timer::setSeconds(int count){ seconds = count; }
int Timer::getSeconds(){return seconds;}
bool Timer::isOut(){
    if (seconds > 0)
        outOfTime = false;
    else
        outOfTime = true;
    return outOfTime;
}

#endif