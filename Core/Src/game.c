/*
 * game.c
 *
 *  Created on: Nov 19, 2020
 *      Author: nkell
 */
#include "game.h"
#include "variables.h"
#include "stdio.h"
#include "usart.h"
#include "string.h"
#include "stm32l476g_discovery_gyroscope.h"
#include "rng.h"
#include "math.h"
#include "stdlib.h"

void draw_base_board(){
	sprintf(buffer, "\033[2J\033[H");
	HAL_UART_Transmit(&huart2, (uint8_t *)buffer, strlen(buffer), 10000);


	for(int i = 1;i < 23;i++){
		set_cursor(1, i);
		sprintf(buffer, "│");
		HAL_UART_Transmit(&huart2, (uint8_t *)buffer, strlen(buffer), 10000);
	}

	for(int i = 1;i < 23;i++){
		set_cursor(42, i);
		sprintf(buffer, "│");
		HAL_UART_Transmit(&huart2, (uint8_t *)buffer, strlen(buffer), 10000);
	}

	for(int i = 1;i < 43;i++){
		set_cursor(i, 1);
		sprintf(buffer, "─");
		HAL_UART_Transmit(&huart2, (uint8_t *)buffer, strlen(buffer), 10000);
	}

	for(int i = 1;i < 43;i++){
		set_cursor(i, 22);
		sprintf(buffer, "─");
		HAL_UART_Transmit(&huart2, (uint8_t *)buffer, strlen(buffer), 10000);
	}

	sprintf(buffer, "\033[1;1H┌\033[22;1H└\033[1;42H┐\033[22;42H┘");
	HAL_UART_Transmit(&huart2, (uint8_t *)buffer, strlen(buffer), 10000);

}


void calibrate_sensor(){
	for(int i = 0;i<100000;i++){
		// get a new reading
		BSP_GYRO_GetXYZ(velocity);
		totals[0] += velocity[0];
		totals[1] += velocity[1];
		totals[2] += velocity[2];
	}
	xBase = totals[0]/100000;
	yBase = totals[1]/100000;
	zBase = totals[2]/100000;
}

void set_cursor(int x, int y){
	sprintf(buffer, "\033[%d;%dH",y,x);
	HAL_UART_Transmit(&huart2, (uint8_t *)buffer, strlen(buffer), 10000);
}


void move_player(){
  	if((fabs(velocity[0]-xBase) > THRESHOLDX)){
		if(velocity[0] > 0){
			move_player_down();
		}

		if(velocity[0] < 0){
			move_player_up();
		}
  	}
  	if((fabs(velocity[2]-zBase) > THRESHOLDY)){
		if(velocity[2] > 0){
			move_player_left();
		}

		if(velocity[2] < 0){
			move_player_right();
		}
  	}
}


void set_cursor_on_board(int x, int y){
	sprintf(buffer, "\033[%d;%dH",y+2,x+2);
	HAL_UART_Transmit(&huart2, (uint8_t *)buffer, strlen(buffer), 10000);
}


void move_player_up(){//+x
	if(player.y > 0){
		//old_player.y = player.y;
		player.y--;
	}
}


void move_player_down(){//-x
	if(player.y < 19){
		//old_player.y = player.y;
		player.y++;
	}
}


void move_player_left(){//-z
	if(player.x > 0){
		//old_player.x = player.x;
		player.x--;
	}
}


void move_player_right(){//+z
	if(player.x < 39){
		//old_player.x = player.x;
		player.x++;
	}
}


void generate_new_target_pos(){
	uint32_t rand1, rand2;
	set_cursor_on_board(target.x, target.y);
	clear_space();
	HAL_RNG_GenerateRandomNumber(&hrng, &rand1);
	HAL_RNG_GenerateRandomNumber(&hrng, &rand2);
	target.x = (rand1 % 40);
	target.y = (rand2 % 20);
	set_cursor_on_board(target.x, target.y);
	sprintf(buffer, "X");
	HAL_UART_Transmit(&huart2, (uint8_t *)buffer, strlen(buffer), 10000);
}


void update_board(){
	set_cursor_on_board(old_player.x, old_player.y);
	clear_space();
	set_cursor_on_board(player.x, player.y);
	draw_player();
}


void clear_space(){
	sprintf(buffer, " ");
	HAL_UART_Transmit(&huart2, (uint8_t *)buffer, strlen(buffer), 10000);
}


void draw_player(){
	sprintf(buffer, "O\033[H");
	HAL_UART_Transmit(&huart2, (uint8_t *)buffer, strlen(buffer), 10000);

}


int check_for_score(){
	if((abs(player.x - target.x) <= 1) && (abs(player.y - target.y) <= 1)){
		score++;
		return 1;
	}
	else{
		return 0;
	}

}


void print_stats(){
	set_cursor(0, 23);
	sprintf(buffer, "Round: %d | Time: %.2fsec | Score: %d | Level: %d", rounds, ((float)level[level_num]/(float)1000000), score, level_num);
	HAL_UART_Transmit(&huart2, (uint8_t *)buffer, strlen(buffer), 10000);
}


void game_finished(){
	set_cursor(15, 11);
	sprintf(buffer, "Game Completed");
	HAL_UART_Transmit(&huart2, (uint8_t *)buffer, strlen(buffer), 10000);
}
