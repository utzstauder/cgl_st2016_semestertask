//
//  TransformComponent.cpp
//  cgl_st2016_semestertask
//
//  Created by Utz Stauder on 28/07/16.
//  Copyright © 2016 Utz Stauder. All rights reserved.
//

#include "TransformComponent.hpp"

TransformComponent::TransformComponent(const Vector2 &p, const Vector2 &s, float r){
    SetPosition(p);
    SetScale(s);
    SetRotation(r);
}

TransformComponent::~TransformComponent(){

}

void TransformComponent::Update(){
    
}


void TransformComponent::SetPosition(float x, float y){
    SetPosition(Vector2(x, y));
}

void TransformComponent::SetPosition(const Vector2 &v){
    position = v;
}

void TransformComponent::Move(const Vector2 &v){
    SetPosition(position + v);
}


void TransformComponent::SetScale(float x, float y){
    SetScale(Vector2(x, y));
}

void TransformComponent::SetScale(const Vector2 &v){
    scale = v;
}

void TransformComponent::Scale(const Vector2 &v){
    SetScale(scale * v);
}

void TransformComponent::Scale(float s){
    SetScale(scale * s);
}



void TransformComponent::SetRotation(float r){
    rotation = r - (( (int)r / 360) * 360.0f);
}

void TransformComponent::Rotate(float r){
    SetRotation(rotation + r);
}

