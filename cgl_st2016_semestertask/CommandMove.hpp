//
//  CommandMove.hpp
//  cgl_st2016_semestertask
//
//  Created by Utz Stauder on 26/07/16.
//  Copyright © 2016 Utz Stauder. All rights reserved.
//

#ifndef CommandMove_hpp
#define CommandMove_hpp

#include "ICommand.hpp"

class CommandMove: public ICommand{
public:
    CommandMove();
    ~CommandMove();
    virtual void Execute();
    
private:
    GameObject* gameObject;
    //Vector2 direction;
};

#endif /* CommandMove_hpp */
