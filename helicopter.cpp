#include "helicopter.h"

helicopter::helicopter()
{
    continue_fall = false;
}



helicopter::helicopter(RectangleShape* shape, Vector2f offset) :object(shape,offset)
{
    continue_fall = false;
   
}

helicopter::~helicopter()
{

}
void helicopter::sprite_move()
{
    //add collision to bottom and top of screen
    switch (continue_fall)
    {
        case true://go up
        {
          
            if (this->my_shape().getPosition().y > TOP)
            {
                this->my_shape_ptr()->move(-this->get_offset());
            }
            break;
        }
        case false://go down
        {
          
            if ((this->my_shape()).getPosition().y < BOTTOM - 40)//40 is size of heli shape
            {
                this->my_shape_ptr()->move(this->get_offset());
                
            }
            break;
        }
    }
}


void helicopter::set_con_fail(bool tf)
{
    continue_fall = tf;
}


