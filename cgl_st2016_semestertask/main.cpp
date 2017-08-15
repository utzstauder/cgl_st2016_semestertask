//
//  main.cpp
//  cgl_st2016_semestertask
//
//  Created by Utz Stauder on 26/07/16.
//  Copyright © 2016 Utz Stauder. All rights reserved.
//

#include "Server.hpp"

const int WINDOW_WIDTH  = 1024;
const int WINDOW_HEIGHT = 576;

using namespace std;

int main(int argc, const char * argv[]) {
    // initialize system
    Server *server = new Server(WINDOW_WIDTH, WINDOW_HEIGHT);
    
    // run the game loop
    server->Run();
    
    // clear memory
    delete server;
    
    // quit the application
    return 0;
}
