#ifdef WINDOW_H

Window::Window(){
}
Window::~Window(){}

bool Window::initWindow(){
        
    if (SDL_GetCurrentDisplayMode(0, &dimensions) != 0)
    {
        printf("Unable to get display mode: %s", SDL_GetError());
        return false;
    }
    return true;
}

int Window::w(){
    return dimensions.w;
}
int Window::h(){
    return dimensions.h;
}

#endif