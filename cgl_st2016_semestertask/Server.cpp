//
//  Server.cpp
//  cgl_st2016_semestertask
//
//  Created by Utz Stauder on 26/07/16.
//  Copyright © 2016 Utz Stauder. All rights reserved.
//

#include "Server.hpp"

Server::Server(int width, int height){
    
    windowWidth  = width;
    windowHeight = height;
    
    // initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0){
        printf("SDL could not initialize! SDL_Error %s\n", SDL_GetError());
    } else {
        // initialize SDLnet
        if (SDLNet_Init() < 0){
            printf("SDLNet could not initilaize! SDLNet_Error %s\n", SDLNet_GetError());
        } else {
            // create window
            window = SDL_CreateWindow("Utz Stauder - Server", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
            if (window == NULL){
                printf("Window could not be created! SDL_Error %s\n", SDL_GetError());
            } else {
                //Create renderer for window
                renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
                if( renderer == NULL )
                {
                    printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                }
                
                // initialize network
                SDLNet_ResolveHost(&ip, NULL, port);
                server_socket = SDLNet_TCP_Open(&ip);
                
                // allocate socket set
                client_sockets = SDLNet_AllocSocketSet(MAX_PLAYERS);
                
                
                // create ball object
                ball = new BallObject(24);
                ball->loadTexture(renderer, "ball.png");
                ball->SetScale(*new Vector2(0.5, 0.5));
                gameObjects.push_back(ball);
                
                // create UI
                TTF_Init();
                
                ui_background = SDL_CreateRGBSurface(0, ui_background_width, ui_background_height, 32, 0, 0, 0, 0);
                ui_background_rect.x = ui_background_x;
                ui_background_rect.y = ui_background_y;
                ui_background_rect.w = ui_background_width;
                ui_background_rect.h = ui_background_height;
                SDL_FillRect(ui_background, &ui_background_rect, SDL_MapRGB(ui_background->format, 255, 255, 255));
                ui_background_texture = SDL_CreateTextureFromSurface(renderer, ui_background);
                
                font = TTF_OpenFont("font.ttf", 24);
                if (!font){
                    printf("TTF_OpenFont: %s\n", TTF_GetError());
                }
                ui_text = TTF_RenderText_Solid(font, ui_text_content, white);
                ui_text_texture = SDL_CreateTextureFromSurface(renderer, ui_text);
                ui_text_rect.x = ui_text_x;
                ui_text_rect.y = ui_text_y;
                ui_text_rect.w = ui_text_width;
                ui_text_rect.h = ui_text_height;
            }
        }
    }
}


Server::~Server(){
    Shutdown();
}


void Server::ProcessEvents(){
    SDL_Event event;
    
    while (SDL_PollEvent(&event)){
        //printf("SDL_Event: %u\n", event.type);
        switch(event.type){
            case SDL_QUIT:{
                running = false;
                
                break;
            }
                
            default: break;
        }
        for (int i = 0; i < gameObjects.size(); i++){
            gameObjects[i]->ProcessEvents(event);
        }
    }
}


void Server::Update(){
    // CORE LOOP
    
    // listen for and handle new connections
    TCPsocket new_connection = SDLNet_TCP_Accept(server_socket);
    if (new_connection){
        if (players_connected < MAX_PLAYERS){
            // add new player
            SDLNet_TCP_AddSocket(client_sockets, new_connection);
            client_data.push_back(connection_data(new_connection, SDL_GetTicks(), current_playerId, true));
            players_connected++;
            
            PlayerObject *newPlayer = new PlayerObject(17);
            newPlayer->loadTexture(renderer, "other.png");
            newPlayer->SetScale(*new Vector2(0.1, 0.1));
            playerObjects[current_playerId] = newPlayer;
            gameObjects.push_back(newPlayer);
            
            // inform connected player about self
            sprintf(outgoing, "0 %i\n", current_playerId);
            SDLNet_TCP_Send(new_connection, outgoing, 17);
            
            for (map<int, PlayerObject*>::iterator i = playerObjects.begin(); i != playerObjects.end(); ++i){
                if (i->first == current_playerId){
                    continue;
                }
                
                // inform other players about new player
                sprintf(outgoing, "2 %i\n", current_playerId);
                SDLNet_TCP_Send(client_data[i->first].socket, outgoing, 17);
                
                // inform connected player about others
                sprintf(outgoing, "2 %i\n", i->first);
                SDLNet_TCP_Send(client_data[current_playerId].socket, outgoing, 17);
            }
            
            printf("New player connected: %i\n", current_playerId);
            current_playerId++;
        } else {
            // server is full
            printf("New connection attempt but the server was full!\n");
        }
    }
    
    // receive data
    while (SDLNet_CheckSockets(client_sockets, 0) > 0){
        for (int i = 0; i < client_data.size(); i++){
            if (client_data[i].connected && SDLNet_SocketReady(client_data[i].socket)){
                client_data[i].timeout = SDL_GetTicks();
                SDLNet_TCP_Recv(client_data[i].socket, incoming, 17);
                
                //printf("Player %i: %s\n", client_data[i].player_id, incoming);
                
                // TODO: make this more flexible
                char* parse = strtok(incoming, " ");
                if (parse){
                    switch(atoi(parse)){
                        case 0:{
                            // 0 = disconnect message
                            // delete from gameObject vector
                            vector<GameObject*>::iterator it = find(gameObjects.begin(), gameObjects.end(), playerObjects[client_data[i].player_id]);
                            if (it != gameObjects.end()){
                                gameObjects.erase(it);
                            }
                            delete playerObjects[i];
                            playerObjects.erase(i);
                            
                            // inform other players
                            for (map<int, PlayerObject*>::iterator it = playerObjects.begin(); it != playerObjects.end(); ++it){
                                if (it->first == client_data[i].player_id){
                                    continue;
                                }
                                sprintf(outgoing, "3 %i\n", client_data[i].player_id);
                                SDLNet_TCP_Send(client_data[it->first].socket, outgoing, 17);
                            }
                            
                            players_connected--;
                            
                            // delete from socket info
                            SDLNet_TCP_DelSocket(client_sockets, client_data[i].socket);
                            client_data[i].connected = false;
                            //client_data.erase(client_data.begin() + i);
                            break;
                        }
                        case 1:{
                            // 1 = direction update
                            // "1 direction.x direction.y"
                            parse = strtok(NULL, " ");
                            float x = atof(parse);
                            parse = strtok(NULL, " ");
                            float y = atof(parse);
                            playerObjects[client_data[i].player_id]->SetDirection(*new Vector2(x, y));
                            break;
                        }
                        default: break;
                    }
                }
                
            }
        }
    }
    
    // collision detection
    for (int i = 0; i < gameObjects.size(); i++){
        if (gameObjects[i]->CanCollide()){
            for (int j = i; j < gameObjects.size(); j++){
                if (j == i) continue;
                if (gameObjects[j]->CanCollide()){
                    gameObjects[i]->Collision(gameObjects[j]);
                }
            }
        }
    }
    
    // update game objects
    for (int i = 0; i < gameObjects.size(); i++){
        gameObjects[i]->Update();
    }
    
    // send data
    for (map<int, PlayerObject*>::iterator i = playerObjects.begin(); i != playerObjects.end(); ++i){
        // reach every connected player
        
        // send position info
        for (map<int, PlayerObject*>::iterator j = playerObjects.begin(); j != playerObjects.end(); ++j){
            sprintf(outgoing, "1 %i %.2f %.2f\n", i->first, i->second->GetPosition().GetX(), i->second->GetPosition().GetY());
            SDLNet_TCP_Send(client_data[j->first].socket, outgoing, 17);
        }
        
        // send ball position
        sprintf(outgoing, "5 %.2f %.2f\n", ball->GetPosition().GetX(), ball->GetPosition().GetY());
        SDLNet_TCP_Send(client_data[i->first].socket, outgoing, 17);
        
        //printf("data sent: %s", outgoing);
    }

}

// normalizedStepBetweenFrames will vary from 0 (previous frame) to 0.99999999.. (just before the next frame) and is used for extrapolation
void Server::Render(float normalizedStepBetweenFrames){
    // bg color
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    
    // clear screen
    SDL_RenderClear(renderer);
    
    // show objects
    for (int i = 0; i < gameObjects.size(); i++){
        gameObjects[i]->Draw(renderer);
    }
    
    // draw ui
    SDL_RenderCopy(renderer, ui_background_texture, NULL, &ui_background_rect);
    SDL_RenderCopy(renderer, ui_text_texture, NULL, &ui_text_rect);
    
    // update screen
    SDL_RenderPresent(renderer);
}


void Server::Run(){
    // initialize game loop
    Uint32 previousTime = SDL_GetTicks();
    Uint32 lag = 0.0;
    Uint32 currentTime;
    Uint32 elapsedTime;
    
    running = true;
    
    // game loop
    while (running){
        // calculate delta time
        currentTime = SDL_GetTicks();
        elapsedTime = currentTime - previousTime;
        previousTime = currentTime;
        lag += elapsedTime;
        
        // process input
        ProcessEvents();
        
        // fixed update to keep game deterministic
        while (lag >= MS_PER_UPDATE){
            if (running){
                Update();
            }
            lag -= MS_PER_UPDATE;
        }
        
        Render(lag / MS_PER_UPDATE);
        
        //printf("fps: %.0f; dt: %.3f\n", (1000.0f / elapsedTime), (elapsedTime / 1000.0f));
    }
}


void Server::Shutdown(){
    // send shutdown message
    for (map<int, PlayerObject*>::iterator j = playerObjects.begin(); j != playerObjects.end(); ++j){
        sprintf(outgoing, "4\n");
        SDLNet_TCP_Send(client_data[j->first].socket, outgoing, 17);
    }
    
    // clean up
    playerObjects.clear();
    gameObjects.clear();
    
    // close socket
    SDLNet_TCP_Close(server_socket);
    
    // destroy renderer
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    
    // close window
    SDL_DestroyWindow(window);
    window = NULL;
    
    // shutdown sdlnet
    SDLNet_Quit();
    
    // shutdown sdl
    SDL_Quit();
}