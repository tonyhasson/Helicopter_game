#pragma once
#include "helicopter.h"
#include <queue>
#include <stdlib.h>
#include <time.h>  





//struct of obstacles
struct obstacles
{
	/*RectangleShape* upper_obs;
	RectangleShape* lower_obs;*/

	//new structure

	object upper_obs;
	object lower_obs;
};


class game
{
	
public:
	game();
	game(helicopter*, RenderWindow*);
	~game();
	void update_game();
	void gameloop();
	bool collision();
	//queue functions
	void update_queue();
	void draw_queue();//might not be able to take into queue/obstacles class because of window
	void create_queue_obj();
	void create_random(float*, float*);
	

private:
	bool lose;
	helicopter* heli;//helicopter
	RenderWindow* window;//screen
	//queue variables
	queue<obstacles*> obs_queue;//queue containing all the obstacles
	Vector2f queue_offset;//how much each obstacles moves each iteration
	float queue_gap_counter;//counting how much the gap between two obstacles is right now
	float queue_gap_max;//when queue_gap_counter reaches this max,create a new obstacle
	
};

