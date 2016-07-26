//
//  System.cpp
//  cgl_st2016_semestertask
//
//  Created by Utz Stauder on 26/07/16.
//  Copyright © 2016 Utz Stauder. All rights reserved.
//

#include "System.hpp"

System::System(int width, int height){
    
    windowWidth  = width;
    windowHeight = height;
    
    // initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0){
        printf("SDL could not initialize! SDL_Error %s\n", SDL_GetError());
    } else {
        // create window
        window = SDL_CreateWindow("Utz Stauder", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
        if (window == NULL){
            printf("Window could not be created! SDL_Error %s\n", SDL_GetError());
        } else {
            // get surface
            windowSurface = SDL_GetWindowSurface(window);
        }
    }
}


System::~System(){
    Shutdown();
}


void System::ProcessEvents(){
    SDL_Event event;
    
    while (SDL_PollEvent(&event)){
        printf("SDL_Event: %u\n", event.type);
        switch(event.type){
            case SDL_QUIT:{
                running = false;
                
                break;
            }
            
            default: break;
        }
    }
}


void System::Update(){
    
}

// normalizedStepBetweenFrames will vary from 0 (previous frame) to 0.99999999.. (just before the next frame) and is used for extrapolation
void System::Render(Uint32 normalizedStepBetweenFrames){
    // clear screen
    
    // show background
    SDL_FillRect(windowSurface, NULL, SDL_MapRGB(windowSurface->format, 0xFF, 0xFF, 0xFF));
    
    // show objects
    
    // update screen
    SDL_UpdateWindowSurface(window);
}


void System::Run(){
    // initialize game loop
    Uint32 previousTime = SDL_GetTicks();
    Uint32 lag = 0.0;
    Uint32 currentTime;
    Uint32 elapsedTime;
    
    running = true;
    
    // game loop
    while (running){
        // calculate delta time
        currentTime = SDL_GetTicks();
        elapsedTime = currentTime - previousTime;
        previousTime = currentTime;
        lag += elapsedTime;
        
        // process input
        ProcessEvents();
        
        // fixed update to keep game deterministic
        while (lag >= MS_PER_UPDATE){
            Update();
            lag -= MS_PER_UPDATE;
        }
        
        Render(lag / MS_PER_UPDATE);
    }
}


void System::Shutdown(){
    // close window
    SDL_DestroyWindow(window);
    
    // shutdown sdl
    SDL_Quit();
}