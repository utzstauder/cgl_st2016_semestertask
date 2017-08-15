//
//  BallObject.cpp
//  cgl_st2016_semestertask
//
//  Created by Utz Stauder on 25/09/16.
//  Copyright © 2016 Utz Stauder. All rights reserved.
//

#include "BallObject.hpp"

BallObject::BallObject(int r){
    radius = r;
    boundingBoxX = r*2;
    boundingBoxY = r*2;
    canCollide = true;
    
    collidertype = circle;
    
    position = *new Vector2(50, 50);
    direction = *new Vector2(2, 1);
    direction.Normalize();
    
    speed = initialSpeed;
}

void BallObject::Update(){
    if (speed < 0) speed = 0.0;
    
    if (position.GetX() > rendererWidth ||
        position.GetX() < 0){
        direction.SetX(direction.GetX() * -1);
    }
    
    if (position.GetY() > rendererHeight ||
        position.GetY() < 0){
        direction.SetY(direction.GetY() * -1);
    }
    
    position = position + (direction * speed);
    speed = speed + acceleration;
}

void BallObject::Collision(GameObject *target){
    if (target->CanCollide()){
        position = position + (direction * speed);
        // check if inside bounding box
        if ((position.GetX() + boundingBoxX/2) > (target->GetPosition().GetX() - target->GetBoundingBox().GetX()/2) &&
            (position.GetX() - boundingBoxX/2) < (target->GetPosition().GetX() + target->GetBoundingBox().GetX()/2) &&
            (position.GetY() + boundingBoxY/2) > (target->GetPosition().GetY() - target->GetBoundingBox().GetY()/2) &&
            (position.GetY() - boundingBoxY/2) < (target->GetPosition().GetY() + target->GetBoundingBox().GetY()/2) ){
            
            switch (target->GetColliderType()) {
                case GameObject::rectangle:{
                    printf("rectangular collision detected!\n");
                    break;
                }
                    
                case GameObject::circle:{
                    Vector2 distanceVector = target->GetPosition() - position;
                    if (distanceVector.Length() < (target->GetRadius() + radius)){
                        // collision
                            //printf("radial collision detected!\n");
                        
                        // bounce
                        direction = direction * -1;
                        direction = direction.Normalize();
                        Vector2 radiusVector = (target->GetPosition() - position);
                        radiusVector = radiusVector.Normalize() * radius;
                        
                        float angleOfEntry = (direction * radiusVector) / (direction.Length() + radiusVector.Length()) / 3.14 * 180;
                        float angleOfExit = angleOfEntry * 2;
                        
                            //printf("%f\n", angleOfEntry);
                        
                        float newDirectionX = direction.GetX() * cos(angleOfExit) - direction.GetY() * sin(angleOfExit);
                        float newDirectionY = direction.GetX() * sin(angleOfExit) + direction.GetY() * cos(angleOfExit);
                        
                        direction = *new Vector2 (newDirectionX, newDirectionY);
                        direction.Normalize();
                        speed = initialSpeed;
                        //position = position + (direction * speed);
                        
                    }
                    break;
                }
                    
                default:
                    break;
            }
        }
    }
}