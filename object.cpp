#include "object.h"


object::object()
{
    shape_ptr = NULL;
    Vector2f tmp(0, 0);
    offset = tmp;
    hitbox_x = 0;
    hitbox_y = 0;
}

object::object(RectangleShape* shape, Vector2f offset) 
{
    shape_ptr = shape;
    this->offset = offset;
    hitbox_x = (*shape_ptr).getSize().x;
    hitbox_y = (*shape_ptr).getSize().y;
}

object::~object()
{

}


RectangleShape object::my_shape()
{
    return *shape_ptr;
}

RectangleShape* object::my_shape_ptr()
{
    return shape_ptr;
}


float object::get_hitbox_x()
{
    return hitbox_x;
}

float object::get_hitbox_y()
{
    return hitbox_y;
}

Vector2f object::get_offset()
{
    return offset;
}

void object::set_shape_ptr(RectangleShape* ptr)
{
    shape_ptr = ptr;
}

void object::set_hitbox_x(float tmp)
{
    hitbox_x = tmp;
}
void object::set_hitbox_y(float tmp)
{
    hitbox_y = tmp;
}