#pragma once

#include<iostream>
#include "RenderWindow.hpp"


void write_history(int point, int life, int speed, float agent_pos_X, float enemy_pos_X, float obstacle1_pos_X, float obstacle2_pos_X,float obstacle1_pos_Y, float obstacle2_pos_Y){
    FILE *continue_game= fopen("data/history.txt","w");
    fprintf(continue_game,"Score: %d\n",point);
    fprintf(continue_game,"Life: %d\n",life);
    fprintf(continue_game,"Speed: %d\n",speed);
    fprintf(continue_game,"AgentPosX: %f\n",agent_pos_X);
    fprintf(continue_game,"EnemyPosX: %f\n",enemy_pos_X);
    fprintf(continue_game,"Obstacle1PosX: %f\n",obstacle1_pos_X);
    fprintf(continue_game,"Obstacle1PosY: %f\n",obstacle1_pos_Y);
    fprintf(continue_game,"Obstacle2PosX: %f\n",obstacle2_pos_X);
    fprintf(continue_game,"Obstacle2PosY: %f\n",obstacle2_pos_Y);
    fclose(continue_game);
}

void read_history(int* point, int* life, int* speed){
    char str[100];
    float enemypos, agentpos;
    float obstacle1_pos_X,obstacle2_pos_X,obstacle1_pos_Y,obstacle2_pos_Y;
    FILE *continue_game= fopen("data/history.txt","r");

    fscanf(continue_game,"%s",str);
    fscanf(continue_game,"%d",point);
    fscanf(continue_game,"%s",str);
    fscanf(continue_game,"%d",life);
    fscanf(continue_game,"%s",str);
    fscanf(continue_game,"%d",speed);
    fscanf(continue_game,"%s",str);
    fscanf(continue_game,"%f",&agentpos);
    fscanf(continue_game,"%s",str);
    fscanf(continue_game,"%f",&enemypos);
    fscanf(continue_game,"%s",str);
    fscanf(continue_game,"%f",&obstacle1_pos_X);
    fscanf(continue_game,"%f",&obstacle1_pos_Y);
    fscanf(continue_game,"%f",&obstacle2_pos_X);
    fscanf(continue_game,"%f",&obstacle2_pos_Y);

    
    if(*life==0 || (agentpos==enemypos)){
        *point = 0;
        *life = 3;
        *speed=-15;
        agentpos=200;
        enemypos=15;
        obstacle1_pos_X = 1500;
        obstacle1_pos_Y = SLIDEOBSTACLEY;
        obstacle2_pos_X = 2550;
        obstacle2_pos_Y = JUMPOBSTACLEY;
    }

    int enemy_flag=1,agent_flag=1;

    if(enemypos==15) enemy_flag=0;
    if(agentpos==200) agent_flag=0;


    for (int i = 0; i < (int)running_enemy.size(); i++)
    {
        running_enemy[i].setpos(enemypos+5*i*enemy_flag);
        running_agent[i].setpos(agentpos+5*i*agent_flag);
    }
    for (int i = 0; i < (int)jumping_agent.size(); i++)
    {
        jumping_agent[i].setpos(agentpos+5*i*agent_flag,SCREEN_HEIGHT-210-120);
    }
    for (int i = 0; i < (int)sliding_agent.size(); i++)
    {
        sliding_agent[i].setpos(agentpos+5*i*agent_flag);
    }
    
    obstacle_array[0].setpos(obstacle1_pos_X,obstacle1_pos_Y);
    obstacle_array[1].setpos(obstacle2_pos_X,obstacle2_pos_Y);
    

    fclose(continue_game);
}
