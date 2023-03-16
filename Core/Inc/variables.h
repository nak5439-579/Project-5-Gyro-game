/*
 * variables.h
 *
 *  Created on: Nov 19, 2020
 *      Author: nkell
 */

#ifndef INC_VARIABLES_H_
#define INC_VARIABLES_H_

#define THRESHOLDX 5000
#define THRESHOLDY 10000
#define LEVEL_1_TIME 10000000
#define LEVEL_2_TIME 6666666
#define LEVEL_3_TIME 4444444
#define LEVEL_4_TIME 2962962
#define LEVEL_5_TIME 1975308
#define LEVEL_6_TIME 1313872
extern int level[];
typedef struct{
	int x;
	int y;
} position;

extern char buffer[100];
extern int xBase, yBase, zBase;
extern int score, rounds, level_num;
extern float velocity[3];  // storage for angular velocity measurements (x,y,z) from L3GD20
extern float angle[3];    	// storage for integrated angles
extern float totals[3];
extern position target;
extern position player;
extern position old_player;


#endif /* INC_VARIABLES_H_ */
