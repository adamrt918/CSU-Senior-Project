#ifdef PAGES_H

Pages::Pages(int pages, int textures, string word[]){
    pageNum = pages;
    textureNum = textures;
    for (int i = 0; i < textureNum; i++)
        words.push_back(word[i]);
}

Pages::~Pages(){}
bool Pages::mediaLoader(int newPage){
    return true;
}

bool Pages::events(){ return true; }

void Pages::setPageNum(int pages){pageNum = pages;}
int Pages::getPageNum(){return pageNum;}

void Pages::setTextureNum(int textures){textureNum = textures;}
int Pages::getTextureNum(){return textureNum;}

void Pages::setWords(string word){}
//     for (int i = 0; i < textureNum; i++)
//         words[i].pushback(word);
// }
// vector<string> Pages::getWords(){return words.begin();}


#endif