//
//  main.cpp
//  cgl_st2016_semestertask
//
//  Created by Utz Stauder on 26/07/16.
//  Copyright © 2016 Utz Stauder. All rights reserved.
//

#include "System.hpp"

const int WINDOW_WIDTH  = 1280;
const int WINDOW_HEIGHT = 720;

using namespace std;

int main(int argc, const char * argv[]) {
    
    // initialize system
    System::Pointer system = make_shared<System>(WINDOW_WIDTH, WINDOW_HEIGHT);
    
    // run the game loop
    system->Run();
    
    // quit the application
    return 0;
}
