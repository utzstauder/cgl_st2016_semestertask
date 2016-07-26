//
//  ICommand.hpp
//  cgl_st2016_semestertask
//
//  Created by Utz Stauder on 26/07/16.
//  Copyright © 2016 Utz Stauder. All rights reserved.
//

#ifndef ICommand_hpp
#define ICommand_hpp

#include "GameObject.hpp"

class ICommand{
public:
    virtual ~ICommand();
    virtual void Execute();
};

#endif /* ICommand_hpp */
