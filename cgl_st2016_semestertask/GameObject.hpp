//
//  GameObject.hpp
//  cgl_st2016_semestertask
//
//  Created by Utz Stauder on 26/07/16.
//  Copyright © 2016 Utz Stauder. All rights reserved.
//

#ifndef GameObject_hpp
#define GameObject_hpp

#include <stdio.h>
#include <string>
#include <tgmath.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

#include "Vector2.hpp"

using namespace std;

class GameObject{
public:
    enum Collider{
        rectangle,
        circle,
    };
    
    GameObject();
    ~GameObject();
    
    inline std::string GetTag(){ return tag; };
    
    virtual void ProcessEvents(SDL_Event event);
    virtual void Update();
    virtual void Draw(SDL_Renderer *renderer);
    
    virtual void Collision(GameObject *target);
    inline bool CanCollide(){ return canCollide; };
    inline Collider GetColliderType(){ return collidertype; };
    inline Vector2 GetBoundingBox(){ return *new Vector2(boundingBoxX, boundingBoxY); };
    inline int GetRadius(){ return radius; };
    
    inline Vector2 GetPosition(){ return position; };
    inline Vector2 GetDirection(){ return direction; };
    //void SetPosition(Vector2 targetPosition){position = targetPosition;};
    void SetScale(Vector2 targetScale){ scale = targetScale; };
    
    void loadTexture(SDL_Renderer *renderer, std::string path);
    
protected:
    
    std::string tag;
    
    Collider collidertype;
    int boundingBoxX;
    int boundingBoxY;
    int radius;
    
    Vector2 position = Vector2::zero;
    Vector2 direction = Vector2::zero;
    Vector2 scale = Vector2::one;
    
    bool canCollide;
    
    SDL_Texture *texture;
    Uint32 textureFormat;
    int textureAccess;
    int textureWidth;
    int textureHeight;
    
    int rendererWidth;
    int rendererHeight;
    
    SDL_Rect srcR;
    SDL_Rect destR;
    
};

#endif /* GameObject_hpp */
