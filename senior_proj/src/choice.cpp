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
    if (response != "")
        textExists = true;
    else
        textExists = false;

    choiceText = response;
}

int* Choice::getChoiceBounds(){}
void Choice::setChoiceBounds(int* metrics[]){}

bool Choice::getTextExists(){return textExists;}
void Choice::setTextExists(){}


#endif