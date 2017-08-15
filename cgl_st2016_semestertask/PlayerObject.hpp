//
//  PlayerObject.hpp
//  cgl_st2016_semestertask
//
//  Created by Utz Stauder on 23/09/16.
//  Copyright © 2016 Utz Stauder. All rights reserved.
//

#ifndef PlayerObject_hpp
#define PlayerObject_hpp

#include <stdio.h>

#include "GameObject.hpp"

class PlayerObject : public GameObject{
public:
    PlayerObject();
    PlayerObject(int r);
    ~PlayerObject();
    
    virtual void ProcessEvents(SDL_Event event);
    virtual void Update();
    
    virtual void Collision(GameObject *target);
    
    inline void SetDirection(Vector2 newDirection){ direction = newDirection; };
    inline void SetRadius(float newRadius){ radius = newRadius; };
    
private:
    enum Directions{
        key_up      = 119,
        key_down    = 115,
        key_left    = 97,
        key_right   = 100,
    };
    
    float speed = 10.0;
};

#endif /* PlayerObject_hpp */
