//
//  GameObject.hpp
//  cgl_st2016_semestertask
//
//  Created by Utz Stauder on 26/07/16.
//  Copyright © 2016 Utz Stauder. All rights reserved.
//

#ifndef GameObject_hpp
#define GameObject_hpp

#include <stdio.h>
#include <string>
#include <memory>

using namespace std;

class GameObject : public std::enable_shared_from_this<GameObject>{
public:
    // always use smart pointers
    typedef std::shared_ptr<GameObject> Pointer;
    typedef std::weak_ptr<GameObject>   WeakPointer;
    
    GameObject();
    ~GameObject();
    
private:
    string test = "hallo";
    
};

#endif /* GameObject_hpp */
