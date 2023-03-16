/*
 * game.h
 *
 *  Created on: Nov 19, 2020
 *      Author: nkell
 */

#ifndef INC_GAME_H_
#define INC_GAME_H_

void draw_base_board();
void calibrate_sensor();
void set_cursor(int x, int y);
void move_player();
void set_cursor_on_board();
void move_player_up();
void move_player_down();
void move_player_left();
void move_player_right();
void generate_new_target_pos();
void update_board();
void clear_space();
void draw_player();
int check_for_score();
void print_stats();
void game_finished();

#endif /* INC_GAME_H_ */
