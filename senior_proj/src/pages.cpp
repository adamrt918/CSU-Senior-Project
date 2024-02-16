#ifdef PAGES_H

Pages::Pages(const int pages, const int textures, const string word[]){
    pageNum = pages;
    textureNum = textures;
    words = word;
}

Pages::~Pages(){
    pageNum = NULL;
    textureNum = NULL;
    
}
bool Pages::mediaLoader(int newPage){
    return true;
}

bool Pages::events(){ return true; }

void Pages::setPageNum(int pages){pageNum = pages;}
int Pages::getPageNum(){return pageNum;}

void Pages::setTextureNum(int textures;){textureNum = textures;}
int Pages::getTextureNum(){return textureNum;}

void Pages::setWords(string word){
    for (int i = 0; i < textureNum; i++)
        words.pushback(word);
}
vector<string> Pages::getWords(){return words.begin();}


#endif