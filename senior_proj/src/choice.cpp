#ifdef CHOICE_H

Choice::Choice(){
    choiceType = -1;
    textExists = false;
}
Choice::Choice(int type, string text, int* b[]){
    choiceType = type;
    choiceText = text;
    textExists = true;
}
Choice::~Choice(){}

int Choice::getChoiceType(){}
void Choice::setChoiceType(int type){}

string Choice::getChoiceText(){}
void Choice::setChoiceText(string response){
    if (response == "")
        textExists = false;
    else
        textExists = true;
    choiceText = response;
}

int* Choice::getChoiceBounds(){}
void Choice::setChoiceBounds(int metrics[][2]){
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 2; j++)
            choiceBounds[i][j] = metrics[i][j];
}

bool Choice::getTextExists(){return textExists;}
void Choice::setTextExists(){}


#endif