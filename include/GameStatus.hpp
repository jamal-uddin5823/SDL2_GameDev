#pragma once

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_timer.h>
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_mixer.h>

#include<iostream>
#include<string>


#include "Sprites.hpp"
#include "Music.hpp"
#include "Fileio.hpp"
#include "Mouse.hpp"
#include "Gamefuncs.hpp"


/*===============================================*/
bool continue_flag=NEW_GAME;
// int game_status=WELCOME_SCREEN;
/*===============================================*/


extern int count, count_down_flag;
int count = 3;
int count_down_flag=0; //to count number of frames shown in a second
bool extra_time_taken = false;


void start_screen(){
    window.render(firstpage);
    first_page_time++;
    if(first_page_time>=first_page_change){
        game_status=MAIN_MENU;
    }
}



void main_menu(){
    int mouse_x, mouse_y;
    SDL_GetMouseState(&mouse_x,&mouse_y);
    if(mouse_x>=button_arr[BUTTONX] && mouse_x<=button_arr[BUTTONX]+BUTTON_WIDTH && mouse_y>=button_arr[NEW_GAMEBUTTONY] && mouse_y<=button_arr[NEW_GAMEBUTTONY]+BUTTON_HEIGHT)
        window.render(new_game);
    else if(mouse_x>=button_arr[BUTTONX] && mouse_x<=button_arr[BUTTONX]+BUTTON_WIDTH && mouse_y>=button_arr[LOAD_GAMEBUTTONY] && mouse_y<=button_arr[LOAD_GAMEBUTTONY]+BUTTON_HEIGHT)
        window.render(load_game);
    else if(mouse_x>=button_arr[BUTTONX] && mouse_x<=button_arr[BUTTONX]+BUTTON_WIDTH && mouse_y>=button_arr[HIGHSCOREBUTTONY] && mouse_y<=button_arr[HIGHSCOREBUTTONY]+BUTTON_HEIGHT)
        window.render(main_menu_high_score);
    else if(mouse_x>=button_arr[BUTTONX] && mouse_x<=button_arr[BUTTONX]+BUTTON_WIDTH && mouse_y>=button_arr[OPTIONSBUTTONY] && mouse_y<=button_arr[OPTIONSBUTTONY]+BUTTON_HEIGHT)
        window.render(main_menu_options);
    else if(mouse_x>=button_arr[BUTTONX] && mouse_x<=button_arr[BUTTONX]+BUTTON_WIDTH && mouse_y>=button_arr[EXITBUTTONY] && mouse_y<=button_arr[EXITBUTTONY]+BUTTON_HEIGHT)
        window.render(exit_game);
    
    else
        window.render(menu);
}




void countdown(){
    // std::cout<<game_status<<'\n';
    read_history(&score,&prev_score,&life,&OBSTACLE_SPEED,&life_present_prev,&game_status);
    if(game_status==NEWGAMEPLAY){
        score=0,life=3;
        obstacle_array[0].setpos(1500,600);
        obstacle_array[1].setpos(2250,600);  
    }

    if(!gameStarted){
        extra_time = SDL_GetTicks()/1000;
        gameStarted = true;
    }
    score-=extra_time-3;
    if(score<0) score=0;

    window.render(countdownEntity);
    render_countdown_agent();
    render_ground();
    
    window.lives_show(life);
    window.score_show(score,initial_score+prev_score);

    window.render(obstacle_array[0]);
    window.render(obstacle_array[1]);
    render_countdown_enemy();


    std::string s=std::__cxx11::to_string(count);
    int text_w,text_h;
    SDL_Texture* texture = window.Textload(s,"fonts/Antonio-Bold.ttf",100,255,0,0,&text_w,&text_h);
    Entity time = Entity(Vector2f(640,480),texture,text_w,text_h,0,0);

    window.render(time);

    count_down_flag++;

    if(count_down_flag>=45){
        count_down_flag=0;
        count--;
    }

}

bool firstgameplay_loop = true;

bool game(bool& gameRunning){
    // if(!extra_time_taken){
    //     score
    // }

    window.clearScreen();
    window.changeRenderColor(255,255,255,255);
    
    background_scroll();


    select_agent_frame();

    music(agent_frame_select_flag);


    render_agent();

    if(!paused_flag)render_obstacle();
    else{
        window.render(obstacle_array[0]);
        window.render(obstacle_array[1]);

        std::string s="Press Esc to continue";
        int text_w,text_h;
        SDL_Texture* texture = window.Textload(s,"fonts/Antonio-Bold.ttf",50,255,0,0,&text_w,&text_h);
        Entity message = Entity(Vector2f(450,480),texture,text_w,text_h,0,0);

        window.render(message);
    }
    render_lifeline();
    render_coin();
    render_freerun();

    render_enemy();


    if(!paused_flag)agent_frame_no++;
    if(!paused_flag)enemy_frame_no++;

    if(!paused_flag)update_agent_pos();

    render_ground();
    

    reset_frame_no();

    collision_checker(gameRunning);

    score = generate_score();
    window.lives_show(life);
    if(gameRunning==false){
        write_history(score,life,OBSTACLE_SPEED,running_agent[enemy_frame_no/running_agent.size()].getpos().x,running_enemy[enemy_frame_no/running_enemy.size()].getpos().x,obstacle_array[0],obstacle_array[1],lifeline);
        highscorewrite();
    }

    return gameRunning;
}
















