//
//  PlayerObject.cpp
//  cgl_st2016_semestertask
//
//  Created by Utz Stauder on 23/09/16.
//  Copyright © 2016 Utz Stauder. All rights reserved.
//

#include "PlayerObject.hpp"

PlayerObject::PlayerObject(){

}

PlayerObject::PlayerObject(int r){
    radius = r;
    boundingBoxX = r*2;
    boundingBoxY = r*2;
    canCollide = true;
    
    collidertype = circle;
}

PlayerObject::~PlayerObject(){

}

void PlayerObject::ProcessEvents(SDL_Event event){
    
}

// checks for and handles collision with target gameobject
void PlayerObject::Collision(GameObject *target){
    if (target->CanCollide()){
        // check if inside bounding box
        if ((position.GetX() + boundingBoxX/2) >= (target->GetPosition().GetX() - boundingBoxX/2) &&
            (position.GetX() - boundingBoxX/2) <= (target->GetPosition().GetX() + boundingBoxX/2) &&
            (position.GetY() + boundingBoxY/2) >= (target->GetPosition().GetY() - boundingBoxY/2) &&
            (position.GetY() - boundingBoxY/2) <= (target->GetPosition().GetY() + boundingBoxY/2) ){
            
            //printf("Collision detected!\n");
            
            switch (target->GetColliderType()) {
                case GameObject::rectangle:{
                    if (direction.GetX() > 0){
                        // going right
                    }
                    break;
                }
                    
                case GameObject::circle:{
                    break;
                }
                    
                default:
                    break;
            }
        }
    }
}

void PlayerObject::Update(){
    position = position + (direction * speed);
    
    if (position.GetX() < 0) position.SetX(0);
    if (position.GetX() > rendererWidth) position.SetX(rendererWidth);
    if (position.GetY() < 0) position.SetY(0);
    if (position.GetY() > rendererHeight) position.SetY(rendererHeight);
}
