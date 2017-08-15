//
//  Server.hpp
//  cgl_st2016_semestertask
//
//  Created by Utz Stauder on 26/07/16.
//  Copyright © 2016 Utz Stauder. All rights reserved.
//

#ifndef Server_hpp
#define Server_hpp

#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <map>
#include <cstring>

#include "SDL2_net/SDL_net.h"

#include "GameObject.hpp"
#include "PlayerObject.hpp"
#include "BallObject.hpp"

// struct for handling player connection info
struct connection_data{
    TCPsocket socket;
    Uint32 timeout;
    int player_id;
    bool connected;
    connection_data(TCPsocket s, Uint32 t, int id, bool c){
        socket = s;
        timeout = t;
        player_id = id;
        connected = c;
    };
};

class Server{
public:
    Server(int width, int height);
    ~Server();
    
    void ProcessEvents();
    void Update();
    void Render(float normalizedStepBetweenFrames);
    
    void Run();
    void Shutdown();
    
    inline int GetWindowWidth() { return windowWidth; }
    inline int GetWindowHeight(){ return windowHeight; }
    
private:
    SDL_Window   *window;
    SDL_Renderer *renderer;
    
    int windowWidth;
    int windowHeight;
    const float MS_PER_UPDATE = 16.66666667;  // 60fps update rate
    bool running;
    
    vector<GameObject*> gameObjects;
    BallObject* ball;
    map<int, PlayerObject*> playerObjects;
    
    // network stuff
    IPaddress ip;
    const Uint16 port = 1234;
    TCPsocket server_socket;
    
    int players_connected = 0;
    int current_playerId = 0;
    const int MAX_PLAYERS = 4;
    SDLNet_SocketSet client_sockets;
    vector<connection_data> client_data;
    
    char incoming[16];
    char outgoing[16];
    
    // UI
    TTF_Font* font;
    SDL_Color white = {255, 255, 255, 255};
    SDL_Color black = {0, 0, 0, 255};
    
    SDL_Surface* ui_background;
    int ui_background_width = 200;
    int ui_background_height = 50;
    int ui_background_x = 200;
    int ui_background_y = 10;
    SDL_Texture* ui_background_texture;
    SDL_Rect ui_background_rect;
    
    SDL_Surface* ui_text;
    int ui_text_width = 200;
    int ui_text_height = 50;
    int ui_text_x = 200;
    int ui_text_y = 10;
    SDL_Texture* ui_text_texture;
    SDL_Rect ui_text_rect;
    
    const char* ui_text_content = "SERVER";
};

#endif /* Server_hpp */
