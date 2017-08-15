//
//  BallObject.hpp
//  cgl_st2016_semestertask
//
//  Created by Utz Stauder on 25/09/16.
//  Copyright © 2016 Utz Stauder. All rights reserved.
//

#ifndef BallObject_hpp
#define BallObject_hpp

#include <stdio.h>

#include "GameObject.hpp"

class BallObject : public GameObject{
public:
    BallObject();
    BallObject(int r);
    ~BallObject();
    
    //virtual void ProcessEvents(SDL_Event event);
    virtual void Update();
    
    virtual void Collision(GameObject *target);
    
    //void SetDirection(Vector2 newDirection){ direction = newDirection; };
    
private:
    Vector2 direction = Vector2::zero;
    const float initialSpeed = 10.0;
    float speed = 0.0;
    float acceleration = -0.03;
};

#endif /* BallObject_hpp */
