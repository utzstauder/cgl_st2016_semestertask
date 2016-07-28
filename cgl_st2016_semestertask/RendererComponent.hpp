//
//  RendererComponent.hpp
//  cgl_st2016_semestertask
//
//  Created by Utz Stauder on 28/07/16.
//  Copyright © 2016 Utz Stauder. All rights reserved.
//

#ifndef RendererComponent_hpp
#define RendererComponent_hpp

#include <SDL2/SDL.h>
#include "IComponent.hpp"

class RendererComponent : public IComponent{
public:
    RendererComponent();
    ~RendererComponent();
    virtual void Update();
    
private:
    SDL_Texture *texture;
    bool visible;
};

#endif /* RendererComponent_hpp */
