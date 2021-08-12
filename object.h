#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string.h>
using namespace std;
using namespace sf;
#define BOTTOM 800
#define TOP 0
#define L_SIDE 0
#define R_SIDE 1200





class object
{
	public:
		object();
		object(RectangleShape*, Vector2f);
		~object();
		RectangleShape my_shape();
		RectangleShape* my_shape_ptr();
		void set_shape_ptr(RectangleShape*);
		//hitbox functions
		float get_hitbox_x();
		float get_hitbox_y();
		void set_hitbox_x(float);
		void set_hitbox_y(float);
		Vector2f get_offset();
		

	private:
		RectangleShape* shape_ptr;
		float hitbox_x;
		float hitbox_y;
		Vector2f offset;
};

