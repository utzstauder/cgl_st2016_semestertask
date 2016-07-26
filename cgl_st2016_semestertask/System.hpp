//
//  System.hpp
//  cgl_st2016_semestertask
//
//  Created by Utz Stauder on 26/07/16.
//  Copyright © 2016 Utz Stauder. All rights reserved.
//

#ifndef System_hpp
#define System_hpp

#include <SDL2/SDL.h>
#include <stdio.h>
#include <memory>

class System : public std::enable_shared_from_this<System>{
public:
    // always use smart pointers
    typedef std::shared_ptr<System> Pointer;
    typedef std::weak_ptr<System>   WeakPointer;
    
    System(int width, int height);
    ~System();
    
    void ProcessEvents();
    void Update();
    void Render(Uint32 normalizedStepBetweenFrames);
    
    void Run();
    void Shutdown();
    
    inline int GetWindowWidth() { return windowWidth; }
    inline int GetWindowHeight(){ return windowHeight; }
    
private:
    SDL_Window   *window;
    SDL_Surface  *windowSurface;
    SDL_Renderer *renderer;
    
    int windowWidth;
    int windowHeight;
    
    const float MS_PER_UPDATE = 16.6666666667;  // 60fps update rate
    
    bool running;
};

#endif /* System_hpp */
