//
//  GameObject.cpp
//  cgl_st2016_semestertask
//
//  Created by Utz Stauder on 26/07/16.
//  Copyright © 2016 Utz Stauder. All rights reserved.
//

#include "GameObject.hpp"

GameObject::GameObject(){

}

GameObject::~GameObject(){
    SDL_DestroyTexture(texture);
}

void GameObject::ProcessEvents(SDL_Event event){

}

void GameObject::Update(){

}

void GameObject::Draw(SDL_Renderer *renderer){
    if (SDL_GetRendererOutputSize(renderer, &rendererWidth, &rendererHeight) == 0){
        destR.x = position.GetX() - (textureWidth * scale.GetX()) / 2;
        destR.y = position.GetY() - (textureHeight * scale.GetY()) / 2;
        destR.w = textureWidth * scale.GetX();
        destR.h = textureHeight * scale.GetY();
        SDL_RenderCopy(renderer, texture, &srcR, &destR);
    } else {
        SDL_RenderCopy(renderer, texture, &srcR, NULL);
    }
    
}

// checks for and handles collision with target gameobject
void GameObject::Collision(GameObject *target){
    
}

// loads a texture from designated path
void GameObject::loadTexture(SDL_Renderer *renderer, std::string path){
    //The final texture
    texture = NULL;
    
    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        texture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if( texture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }
        
        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }
    
    // query texture info
    if (SDL_QueryTexture(texture, &textureFormat, &textureAccess, &textureWidth, &textureHeight) == 0){
        printf("%s (%i x %i) loaded successfully!\n", path.c_str(), textureWidth, textureHeight);
        
        srcR.x = 0;
        srcR.y = 0;
        srcR.w = textureWidth;
        srcR.h = textureHeight;
    }
    
    
    
}