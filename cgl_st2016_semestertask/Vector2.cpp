//
//  Vector2.cpp
//  cgl_st2016_semestertask
//
//  Created by Utz Stauder on 28/07/16.
//  Copyright © 2016 Utz Stauder. All rights reserved.
//

#include "Vector2.hpp"

Vector2::Vector2(float x, float y){
    this->x = x;
    this->y = y;
}

Vector2::~Vector2(){
    //printf("Vector2 destructor called.\n");
}

const Vector2 &Vector2::zero  = Vector2(    0,     0);
const Vector2 &Vector2::one   = Vector2( 1.0f,  1.0f);
const Vector2 &Vector2::left  = Vector2(-1.0f,     0);
const Vector2 &Vector2::right = Vector2( 1.0f,     0);
const Vector2 &Vector2::up    = Vector2(    0,  1.0f);
const Vector2 &Vector2::down  = Vector2(    0, -1.0f);


void Vector2::Set(float x, float y){
    this->x = x;
    this->y = y;
}

void Vector2::SetX(float x){
    this->x = x;
}

void Vector2::SetY(float y){
    this->y = y;
}


const float Vector2::Length(){
    return sqrt((x * x) + (y * y));
}

const float Vector2::LengthSquared(){
    return ((x * x) + (y * y));
}


const float Vector2::Distance(const Vector2 &v1, const Vector2 &v2){
    return sqrt(((v1.x - v2.x) * (v1.x - v2.x)) + ((v1.y - v2.y) * (v1.y - v2.y)));
};

const float Vector2::DistanceSquared(const Vector2 &v1, const Vector2 &v2){
    return ((v1.x - v2.x) * (v1.x - v2.x)) + ((v1.y - v2.y) * (v1.y - v2.y));
};


Vector2 &Vector2::Normalize(){
    if (Length() != 0){
        float length = Length();
        x /= length;
        y /= length;
        return *this;
    }
    
    x = 0;
    y = 0;
    return *this;
}