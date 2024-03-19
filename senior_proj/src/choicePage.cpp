#ifdef CHOICEPAGE_H

//Constructor -- overloaded when I want to initialize
ChoicePage::ChoicePage(Player* player, LTexture* textures){
    gamer = player;
    this->textures = textures;
    storePage = -1;
}

//Destructor
ChoicePage::~ChoicePage(){
    delete gamer;
}

bool ChoicePage::loadMedia(SDL_Renderer* gRenderer, int pgNum){
    switch (pgNum){
        case GAME_PAGE_2:
            //Load the game text
            textures[0].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", WRITING);
            if (textures[0].gFont == NULL)
            {
                printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
                return false;
            }  
            if (!textures[0].loadFromRenderedText(gRenderer, GAME_PAGE_2_WORDS[0], GREY, w / 1.3))
            {
                printf( "Failed to render text texture!\n" );
                return false;
            }          

            //Instance the possible choices
            for (int i = 0; i < 3; i++){
                choice[i].text = GAME_PAGE_2_WORDS[i + 1];
                if (i == 0){
                    choice[i].courageLevel = Choices::Heroic;
                    choice[i].bounds[0][0] = 0; //Lower bound for health
                    choice[i].bounds[0][1] = 0; //Upper bound for health
                    choice[i].bounds[1][0] = -1; //Lower bound for sanity
                    choice[i].bounds[1][1] = 0; //Upper bound for sanity
                    choice[i].bounds[2][0] = 0; //Lower bound for reputation
                    choice[i].bounds[2][1] = 2; //Upper bound for reputation
                }
                else if ( i == 1){
                    choice[i].courageLevel = Choices::Cowardly;
                    choice[i].bounds[0][0] = 0; //Lower bound for health
                    choice[i].bounds[0][1] = 0; //Upper bound for health
                    choice[i].bounds[1][0] = -3; //Lower bound for sanity
                    choice[i].bounds[1][1] = -1; //Upper bound for sanity
                    choice[i].bounds[2][0] = -2; //Lower bound for reputation
                    choice[i].bounds[2][1] = 0; //Upper bound for reputation
                }
                else 
                {    
                    choice[i].courageLevel = Choices::Average;
                    choice[i].bounds[0][0] = 0; //Lower bound for health
                    choice[i].bounds[0][1] = 0; //Upper bound for health
                    choice[i].bounds[1][0] = -2; //Lower bound for sanity
                    choice[i].bounds[1][1] = 0; //Upper bound for sanity
                    choice[i].bounds[2][0] = -1; //Lower bound for reputation
                    choice[i].bounds[2][1] = 0; //Upper bound for reputation
                }
            }

            break;
        case GAME_PAGE_6:
            //Load the game text
            textures[0].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", WRITING);
            if (textures[0].gFont == NULL)
            {
                printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
                return false;
            }  
            if (!textures[0].loadFromRenderedText(gRenderer, GAME_PAGE_6_WORDS[0], GREY, w / 1.3))
            {
                printf( "Failed to render text texture!\n" );
                return false;
            }          

            //Instance the possible choices
            for (int i = 0; i < 3; i++){
                choice[i].text = GAME_PAGE_6_WORDS[i + 1];
                if (i == 0){
                    choice[i].courageLevel = Choices::Average;
                    choice[i].bounds[0][0] = -1; //Lower bound for health
                    choice[i].bounds[0][1] = 0; //Upper bound for health
                    choice[i].bounds[1][0] = -2; //Lower bound for sanity
                    choice[i].bounds[1][1] = -1; //Upper bound for sanity
                    choice[i].bounds[2][0] = -1; //Lower bound for reputation
                    choice[i].bounds[2][1] = 1; //Upper bound for reputation
                }
                else if ( i == 1){
                    choice[i].courageLevel = Choices::Heroic;
                    choice[i].bounds[0][0] = -2; //Lower bound for health
                    choice[i].bounds[0][1] = -1; //Upper bound for health
                    choice[i].bounds[1][0] = -1; //Lower bound for sanity
                    choice[i].bounds[1][1] = 1; //Upper bound for sanity
                    choice[i].bounds[2][0] = 0; //Lower bound for reputation
                    choice[i].bounds[2][1] = 2; //Upper bound for reputation
                }
                else 
                {    
                    choice[i].courageLevel = Choices::Cowardly;
                    choice[i].bounds[0][0] = -1; //Lower bound for health
                    choice[i].bounds[0][1] = 0; //Upper bound for health
                    choice[i].bounds[1][0] = -4; //Lower bound for sanity
                    choice[i].bounds[1][1] = -2; //Upper bound for sanity
                    choice[i].bounds[2][0] = -4; //Lower bound for reputation
                    choice[i].bounds[2][1] = -1; //Upper bound for reputation
                }
            }
            break;
        case GAME_PAGE_10:
            //Load the game text
            textures[0].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", WRITING);
            if (textures[0].gFont == NULL)
            {
                printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
                return false;
            }  

            if (!textures[0].loadFromRenderedText(gRenderer, GAME_PAGE_10_WORDS[0], GREY, w / 1.3))
            {
                printf( "Failed to render text texture!\n" );
                return false;
            }          
            //Instance the possible choices
            for (int i = 0; i < 3; i++){
                choice[i].text = GAME_PAGE_10_WORDS[i + 1];
                if (i == 0){
                    choice[i].courageLevel = Choices::Average;
                    choice[i].bounds[0][0] = -1; //Lower bound for health
                    choice[i].bounds[0][1] = 0; //Upper bound for health
                    choice[i].bounds[1][0] = -2; //Lower bound for sanity
                    choice[i].bounds[1][1] = 0; //Upper bound for sanity
                    choice[i].bounds[2][0] = -1; //Lower bound for reputation
                    choice[i].bounds[2][1] = 1; //Upper bound for reputation
                }
                else if ( i == 1){
                    choice[i].courageLevel = Choices::Cowardly;
                    choice[i].bounds[0][0] = 0; //Lower bound for health
                    choice[i].bounds[0][1] = 0; //Upper bound for health
                    choice[i].bounds[1][0] = -3; //Lower bound for sanity
                    choice[i].bounds[1][1] = -1; //Upper bound for sanity
                    choice[i].bounds[2][0] = -2; //Lower bound for reputation
                    choice[i].bounds[2][1] = 0; //Upper bound for reputation
                }
                else  
                {    
                    choice[i].courageLevel = Choices::Heroic;
                    choice[i].bounds[0][0] = -2; //Lower bound for health
                    choice[i].bounds[0][1] = 0; //Upper bound for health
                    choice[i].bounds[1][0] = -1; //Lower bound for sanity
                    choice[i].bounds[1][1] = 0; //Upper bound for sanity
                    choice[i].bounds[2][0] = 0; //Lower bound for reputation
                    choice[i].bounds[2][1] = 2; //Upper bound for reputation
                }
            }
            break;
        case GAME_PAGE_13:
            //Load the game text
            textures[0].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", WRITING);
            if (textures[0].gFont == NULL)
            {
                printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
                return false;
            }  

            if (!textures[0].loadFromRenderedText(gRenderer, GAME_PAGE_13_WORDS[0], GREY, w / 1.3))
            {
                printf( "Failed to render text texture!\n" );
                return false;
            }          
            //Instance the possible choices
            for (int i = 0; i < 3; i++){
                choice[i].text = GAME_PAGE_13_WORDS[i + 1];
                if (i == 0){
                    choice[i].courageLevel = Choices::Heroic;
                    choice[i].bounds[0][0] = -4; //Lower bound for health
                    choice[i].bounds[0][1] = -2; //Upper bound for health
                    choice[i].bounds[1][0] = -2; //Lower bound for sanity
                    choice[i].bounds[1][1] = 0; //Upper bound for sanity
                    choice[i].bounds[2][0] = 0; //Lower bound for reputation
                    choice[i].bounds[2][1] = 4; //Upper bound for reputation
                }
                else if ( i == 1){
                    choice[i].courageLevel = Choices::Cowardly;
                    choice[i].bounds[0][0] = 0; //Lower bound for health
                    choice[i].bounds[0][1] = 0; //Upper bound for health
                    choice[i].bounds[1][0] = -5; //Lower bound for sanity
                    choice[i].bounds[1][1] = -2; //Upper bound for sanity
                    choice[i].bounds[2][0] = -6; //Lower bound for reputation
                    choice[i].bounds[2][1] = 0; //Upper bound for reputation
                }
                else 
                {    
                    choice[i].courageLevel = Choices::Average;
                    choice[i].bounds[0][0] = -2; //Lower bound for health
                    choice[i].bounds[0][1] = 0; //Upper bound for health
                    choice[i].bounds[1][0] = -3; //Lower bound for sanity
                    choice[i].bounds[1][1] = -1; //Upper bound for sanity
                    choice[i].bounds[2][0] = -2; //Lower bound for reputation
                    choice[i].bounds[2][1] = 1; //Upper bound for reputation
                }
            }
            break;
        default:
            break;
    } //End switch

    //Only load the cowardly option on insanity = true
    if (gamer->getInsane()){
        textures[1].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", WRITING);
        if (textures[1].gFont == NULL)
        {
            printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
            return false;
        }
        //Load in the textures for rendering
        if (!textures[1].loadFromRenderedText(gRenderer, choice[chooseInsane()].text, TAN, w / 1.3))
        {
            printf( "Failed to render text texture!\n" );
            return false;
        }
    }
    //Load all other options when insanity is not true
    else{
        for (int i = 1; i < CHOICE_PAGE_TEXTURES; i++){
            textures[i].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", WRITING);
            if (textures[i].gFont == NULL)
            {
                printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
                return false;
            }
            //Load in the textures for rendering
            if (!textures[i].loadFromRenderedText(gRenderer, choice[i - 1].text, TAN, w / 1.3))
            {
                printf( "Failed to render text texture!\n" );
                return false;
            }
        }
    }

    return true;
} //End function

int ChoicePage::chooseInsane(){
    
    //Return the cowardly choice if the gamer is insane
    if (gamer->getInsane())
        for (int i = 0; i < 3; i++)
            if (choice[i].courageLevel == Choices::Cowardly)
                return i;
    return -1;
}

int ChoicePage::choicePageEvents(int currentPage, SDL_Color* textColor, SDL_Event e, SDL_Renderer* renderer){
    int newPage = currentPage;
    switch (currentPage){
        case GAME_PAGE_2:
            if (!gamer->getInsane()){
                //Iterating over choice textures    
                for (int i = 1; i < CHOICE_PAGE_TEXTURES; i++)
                {
                    int j = i - 1;
                    if (textures[i].isMouseOver(textures[i].getRect())){
                        *textColor = GREY;
                        textures[i].gFont = TTF_OpenFont("resources/Abadi_MT_Std_Bold.ttf", WRITING + 2);
                        if(e.type == SDL_MOUSEBUTTONDOWN)
                        { 
                            switch (choice[j].courageLevel){
                                case Choices::ChoiceType::Heroic: 
                                    newPage = OUTCOME_PAGE;
                                    storePage = GAME_PAGE_3_1;
                                    decision = j;
                                    //iterating over each metric with k
                                    for (int k = 0; k < 3; k++)
                                        choice[j].statChange[k] = gamer->random(choice[j].bounds[k]);
                                    
                                    //Set the new value with the change in stats
                                    gamer->setHealth(gamer->getHealth() + choice[j].statChange[0]);
                                    gamer->setSanity(gamer->getSanity() + choice[j].statChange[1]);
                                    gamer->setRep(gamer->getRep() + choice[j].statChange[2]);
                                    break;
                                case Choices::ChoiceType::Cowardly:
                                    newPage = OUTCOME_PAGE;
                                    storePage = GAME_PAGE_3_2;
                                    decision = j;

                                    //iterating over each metric with k
                                    for (int k = 0; k < 3; k++)
                                        choice[j].statChange[k] = gamer->random(choice[j].bounds[k]);
                                    
                                    //Set the new value with the change in stats
                                    gamer->setHealth(gamer->getHealth() + choice[j].statChange[0]);
                                    gamer->setSanity(gamer->getSanity() + choice[j].statChange[1]);
                                    gamer->setRep(gamer->getRep() + choice[j].statChange[2]);
                                    break;
                                case Choices::ChoiceType::Average:
                                    newPage = OUTCOME_PAGE;
                                    storePage = GAME_PAGE_3_3;
                                    decision = j;
                                    //iterating over each metric with k
                                    for (int k = 0; k < 3; k++)
                                        choice[j].statChange[k] = gamer->random(choice[j].bounds[k]);
                                    
                                    //Set the new value with the change in stats
                                    gamer->setHealth(gamer->getHealth() + choice[j].statChange[0]);
                                    gamer->setSanity(gamer->getSanity() + choice[j].statChange[1]);
                                    gamer->setRep(gamer->getRep() + choice[j].statChange[2]);                             
                                    break;
                                default:
                                    break;
                            } //End courage level switch
                        } // End Mouse button down events                  
                    } //End Mouse Over events
                    else
                    {
                        *textColor = TAN;
                        textures[i].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", WRITING);
                    }
                    textures[i].loadFromRenderedText(renderer, choice[j].text, *textColor, w/1.3);
                } //End the texture for loop
            } // End Sane events
            else{
                if (textures[1].isMouseOver(textures[1].getRect())){
                    *textColor = GREY;
                    textures[1].gFont = TTF_OpenFont("resources/Abadi_MT_Std_Bold.ttf", WRITING + 2);
                    if(e.type == SDL_MOUSEBUTTONDOWN)
                    { 
                        newPage = OUTCOME_PAGE;
                        storePage = GAME_PAGE_3_2;
                        decision = chooseInsane();
                        //iterating over each metric with k
                        for (int k = 0; k < 3; k++)
                            choice[chooseInsane()].statChange[k] = gamer->random(choice[chooseInsane()].bounds[k]);
                        
                        //Set the new value with the change in stats
                        gamer->setHealth(gamer->getHealth() + choice[chooseInsane()].statChange[0]);
                        gamer->setSanity(gamer->getSanity() + choice[chooseInsane()].statChange[1]);
                        gamer->setRep(gamer->getRep() + choice[chooseInsane()].statChange[2]);
                    }
                }
                else{
                    *textColor = TAN;
                    textures[1].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", WRITING);
                }
                textures[1].loadFromRenderedText(renderer, choice[chooseInsane()].text, *textColor, w/1.3);
            } // End insane events
            break;
        case GAME_PAGE_6:
                if (!gamer->getInsane()){
                //Iterating over choice textures    
                for (int i = 1; i < CHOICE_PAGE_TEXTURES; i++)
                {
                    int j = i - 1;
                    if (textures[i].isMouseOver(textures[i].getRect())){
                        *textColor = GREY;
                        textures[i].gFont = TTF_OpenFont("resources/Abadi_MT_Std_Bold.ttf", WRITING + 2);
                        if(e.type == SDL_MOUSEBUTTONDOWN)
                        { 
                            switch (choice[j].courageLevel){
                                case Choices::ChoiceType::Heroic: 
                                    newPage = OUTCOME_PAGE;
                                    storePage = GAME_PAGE_7_2;
                                    decision = j;
                                    //iterating over each metric with k
                                    for (int k = 0; k < 3; k++)
                                        choice[j].statChange[k] = gamer->random(choice[j].bounds[k]);
                                    
                                    //Set the new value with the change in stats
                                    gamer->setHealth(gamer->getHealth() + choice[j].statChange[0]);
                                    gamer->setSanity(gamer->getSanity() + choice[j].statChange[1]);
                                    gamer->setRep(gamer->getRep() + choice[j].statChange[2]);
                                    break;
                                case Choices::ChoiceType::Cowardly:
                                    newPage = OUTCOME_PAGE;
                                    storePage = GAME_PAGE_7_3;
                                    decision = j;

                                    //iterating over each metric with k
                                    for (int k = 0; k < 3; k++)
                                        choice[j].statChange[k] = gamer->random(choice[j].bounds[k]);
                                    
                                    //Set the new value with the change in stats
                                    gamer->setHealth(gamer->getHealth() + choice[j].statChange[0]);
                                    gamer->setSanity(gamer->getSanity() + choice[j].statChange[1]);
                                    gamer->setRep(gamer->getRep() + choice[j].statChange[2]);
                                    break;
                                case Choices::ChoiceType::Average:
                                    newPage = OUTCOME_PAGE;
                                    storePage = GAME_PAGE_7_1;
                                    decision = j;
                                    //iterating over each metric with k
                                    for (int k = 0; k < 3; k++)
                                        choice[j].statChange[k] = gamer->random(choice[j].bounds[k]);
                                    
                                    //Set the new value with the change in stats
                                    gamer->setHealth(gamer->getHealth() + choice[j].statChange[0]);
                                    gamer->setSanity(gamer->getSanity() + choice[j].statChange[1]);
                                    gamer->setRep(gamer->getRep() + choice[j].statChange[2]);                             
                                    break;
                                default:
                                    break;
                            } //End courage level switch
                        } // End Mouse button down events                  
                    } //End Mouse Over events
                    else
                    {
                        *textColor = TAN;
                        textures[i].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", WRITING);
                    }
                    textures[i].loadFromRenderedText(renderer, choice[j].text, *textColor, w/1.3);
                } //End the texture for loop
            } // End Sane events
            else{
                if (textures[1].isMouseOver(textures[1].getRect())){
                    *textColor = GREY;
                    textures[1].gFont = TTF_OpenFont("resources/Abadi_MT_Std_Bold.ttf", WRITING + 2);
                    if(e.type == SDL_MOUSEBUTTONDOWN)
                    { 
                        newPage = OUTCOME_PAGE;
                        storePage = GAME_PAGE_7_3;
                        decision = chooseInsane();
                        //iterating over each metric with k
                        for (int k = 0; k < 3; k++)
                            choice[chooseInsane()].statChange[k] = gamer->random(choice[chooseInsane()].bounds[k]);
                        
                        //Set the new value with the change in stats
                        gamer->setHealth(gamer->getHealth() + choice[chooseInsane()].statChange[0]);
                        gamer->setSanity(gamer->getSanity() + choice[chooseInsane()].statChange[1]);
                        gamer->setRep(gamer->getRep() + choice[chooseInsane()].statChange[2]);
                    }
                }
                else{
                    *textColor = TAN;
                    textures[1].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", WRITING);
                }
                textures[1].loadFromRenderedText(renderer, choice[chooseInsane()].text, *textColor, w/1.3);
            } // End insane events
            break;
        case GAME_PAGE_10:
            if (!gamer->getInsane()){
                //Iterating over choice textures    
                for (int i = 1; i < CHOICE_PAGE_TEXTURES; i++)
                {
                    int j = i - 1;
                    if (textures[i].isMouseOver(textures[i].getRect())){
                        *textColor = GREY;
                        textures[i].gFont = TTF_OpenFont("resources/Abadi_MT_Std_Bold.ttf", WRITING + 2);
                        if(e.type == SDL_MOUSEBUTTONDOWN)
                        { 
                            switch (choice[j].courageLevel){
                                case Choices::ChoiceType::Heroic: 
                                    newPage = OUTCOME_PAGE;
                                    storePage = GAME_PAGE_11_3;
                                    decision = j;
                                    //iterating over each metric with k
                                    for (int k = 0; k < 3; k++)
                                        choice[j].statChange[k] = gamer->random(choice[j].bounds[k]);
                                    
                                    //Set the new value with the change in stats
                                    gamer->setHealth(gamer->getHealth() + choice[j].statChange[0]);
                                    gamer->setSanity(gamer->getSanity() + choice[j].statChange[1]);
                                    gamer->setRep(gamer->getRep() + choice[j].statChange[2]);
                                    break;
                                case Choices::ChoiceType::Cowardly:
                                    newPage = OUTCOME_PAGE;
                                    storePage = GAME_PAGE_11_2;
                                    decision = j;

                                    //iterating over each metric with k
                                    for (int k = 0; k < 3; k++)
                                        choice[j].statChange[k] = gamer->random(choice[j].bounds[k]);
                                    
                                    //Set the new value with the change in stats
                                    gamer->setHealth(gamer->getHealth() + choice[j].statChange[0]);
                                    gamer->setSanity(gamer->getSanity() + choice[j].statChange[1]);
                                    gamer->setRep(gamer->getRep() + choice[j].statChange[2]);
                                    break;
                                case Choices::ChoiceType::Average:
                                    newPage = OUTCOME_PAGE;
                                    storePage = GAME_PAGE_11_1;
                                    decision = j;
                                    //iterating over each metric with k
                                    for (int k = 0; k < 3; k++)
                                        choice[j].statChange[k] = gamer->random(choice[j].bounds[k]);
                                    
                                    //Set the new value with the change in stats
                                    gamer->setHealth(gamer->getHealth() + choice[j].statChange[0]);
                                    gamer->setSanity(gamer->getSanity() + choice[j].statChange[1]);
                                    gamer->setRep(gamer->getRep() + choice[j].statChange[2]);                             
                                    break;
                                default:
                                    break;
                            } //End courage level switch
                        } // End Mouse button down events                  
                    } //End Mouse Over events
                    else
                    {
                        *textColor = TAN;
                        textures[i].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", WRITING);
                    }
                    textures[i].loadFromRenderedText(renderer, choice[j].text, *textColor, w/1.3);
                } //End the texture for loop
            } // End Sane events
            else{
                if (textures[1].isMouseOver(textures[1].getRect())){
                    *textColor = GREY;
                    textures[1].gFont = TTF_OpenFont("resources/Abadi_MT_Std_Bold.ttf", WRITING + 2);
                    if(e.type == SDL_MOUSEBUTTONDOWN)
                    { 
                        newPage = OUTCOME_PAGE;
                        storePage = GAME_PAGE_11_2;
                        decision = chooseInsane();
                        //iterating over each metric with k
                        for (int k = 0; k < 3; k++)
                            choice[chooseInsane()].statChange[k] = gamer->random(choice[chooseInsane()].bounds[k]);
                        
                        //Set the new value with the change in stats
                        gamer->setHealth(gamer->getHealth() + choice[chooseInsane()].statChange[0]);
                        gamer->setSanity(gamer->getSanity() + choice[chooseInsane()].statChange[1]);
                        gamer->setRep(gamer->getRep() + choice[chooseInsane()].statChange[2]);
                    }
                }
                else{
                    *textColor = TAN;
                    textures[1].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", WRITING);
                }
                textures[1].loadFromRenderedText(renderer, choice[chooseInsane()].text, *textColor, w/1.3);
            } // End insane events
            break;
        case GAME_PAGE_13:
            if (!gamer->getInsane()){
                //Iterating over choice textures    
                for (int i = 1; i < CHOICE_PAGE_TEXTURES; i++)
                {
                    int j = i - 1;
                    if (textures[i].isMouseOver(textures[i].getRect())){
                        *textColor = GREY;
                        textures[i].gFont = TTF_OpenFont("resources/Abadi_MT_Std_Bold.ttf", WRITING + 2);
                        if(e.type == SDL_MOUSEBUTTONDOWN)
                        { 
                            switch (choice[j].courageLevel){
                                case Choices::ChoiceType::Heroic: 
                                    newPage = OUTCOME_PAGE;
                                    storePage = GAME_PAGE_14_1;
                                    decision = j;
                                    //iterating over each metric with k
                                    for (int k = 0; k < 3; k++)
                                        choice[j].statChange[k] = gamer->random(choice[j].bounds[k]);
                                    
                                    //Set the new value with the change in stats
                                    gamer->setHealth(gamer->getHealth() + choice[j].statChange[0]);
                                    gamer->setSanity(gamer->getSanity() + choice[j].statChange[1]);
                                    gamer->setRep(gamer->getRep() + choice[j].statChange[2]);
                                    break;
                                case Choices::ChoiceType::Cowardly:
                                    newPage = OUTCOME_PAGE;
                                    storePage = GAME_PAGE_14_2;
                                    decision = j;

                                    //iterating over each metric with k
                                    for (int k = 0; k < 3; k++)
                                        choice[j].statChange[k] = gamer->random(choice[j].bounds[k]);
                                    
                                    //Set the new value with the change in stats
                                    gamer->setHealth(gamer->getHealth() + choice[j].statChange[0]);
                                    gamer->setSanity(gamer->getSanity() + choice[j].statChange[1]);
                                    gamer->setRep(gamer->getRep() + choice[j].statChange[2]);
                                    break;
                                case Choices::ChoiceType::Average:
                                    newPage = OUTCOME_PAGE;
                                    storePage = GAME_PAGE_14_3;
                                    decision = j;
                                    //iterating over each metric with k
                                    for (int k = 0; k < 3; k++)
                                        choice[j].statChange[k] = gamer->random(choice[j].bounds[k]);
                                    
                                    //Set the new value with the change in stats
                                    gamer->setHealth(gamer->getHealth() + choice[j].statChange[0]);
                                    gamer->setSanity(gamer->getSanity() + choice[j].statChange[1]);
                                    gamer->setRep(gamer->getRep() + choice[j].statChange[2]);                             
                                    break;
                                default:
                                    break;
                            } //End courage level switch
                        } // End Mouse button down events                  
                    } //End Mouse Over events
                    else
                    {
                        *textColor = TAN;
                        textures[i].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", WRITING);
                    }
                    textures[i].loadFromRenderedText(renderer, choice[j].text, *textColor, w/1.3);
                } //End the texture for loop
            } // End Sane events
            else{
                if (textures[1].isMouseOver(textures[1].getRect())){
                    *textColor = GREY;
                    textures[1].gFont = TTF_OpenFont("resources/Abadi_MT_Std_Bold.ttf", WRITING + 2);
                    if(e.type == SDL_MOUSEBUTTONDOWN)
                    { 
                        newPage = OUTCOME_PAGE;
                        storePage = GAME_PAGE_14_2;
                        decision = chooseInsane();
                        //iterating over each metric with k
                        for (int k = 0; k < 3; k++)
                            choice[chooseInsane()].statChange[k] = gamer->random(choice[chooseInsane()].bounds[k]);
                        
                        //Set the new value with the change in stats
                        gamer->setHealth(gamer->getHealth() + choice[chooseInsane()].statChange[0]);
                        gamer->setSanity(gamer->getSanity() + choice[chooseInsane()].statChange[1]);
                        gamer->setRep(gamer->getRep() + choice[chooseInsane()].statChange[2]);
                    }
                }
                else{
                    *textColor = TAN;
                    textures[1].gFont = TTF_OpenFont("resources/Abadi_MT_Std.ttf", WRITING);
                }
                textures[1].loadFromRenderedText(renderer, choice[chooseInsane()].text, *textColor, w/1.3);
            } // End insane events
            break;
        default:
            break;
    } //End Page number switch
    return newPage;
}

int* ChoicePage::getStatChange(){
    return choice[decision].statChange;
}

int ChoicePage::getStorePage(){
    return storePage;
}

void ChoicePage::setStorePage(int sp){
    storePage = sp;
}

int ChoicePage::getW(){return w;}
void ChoicePage::setW(int width){w = width;}
int ChoicePage::getH(){return h;}
void ChoicePage::setH(int height){h = height;}

#endif