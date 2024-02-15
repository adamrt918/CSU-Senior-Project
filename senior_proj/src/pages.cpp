#ifdef PAGES_H

Pages::Pages(){
    num = 0;
}
Pages::~Pages(){
    num = 0;
}
bool Pages::mediaLoader(int newPage){
    return true;
}

bool Pages::events(){ return true; }

#endif