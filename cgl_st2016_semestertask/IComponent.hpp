//
//  IComponent.hpp
//  cgl_st2016_semestertask
//
//  Created by Utz Stauder on 26/07/16.
//  Copyright © 2016 Utz Stauder. All rights reserved.
//

#ifndef IComponent_hpp
#define IComponent_hpp

#include <stdio.h>

class IComponent{
public:
    virtual ~IComponent() {};
    virtual void Update() = 0;
};

#endif /* IComponent_hpp */
