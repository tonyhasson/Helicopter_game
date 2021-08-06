#include "game.h"


game::game()
{
   
}

game::game(helicopter* h, RenderWindow* w)
{
    lose = false;
	heli = h;
	window = w;
    //init queue_offset 
    Vector2f tmp(-10, 0);
    queue_offset = tmp;
    queue_gap_counter = 0;
    queue_gap_max = 500;
   
}

game::~game()
{
    //need to free queue objects
}




void game::gameloop()
{
    
    while ((*window).isOpen() && !lose)
    {
        Event event;
        while ((*window).pollEvent(event))
        {
            switch (event.type)
            {
            case Event::Closed://if clicked close window
                (*window).close();
                break;
            }

        }

        update_game();


    }
    if (lose)
    {
        cout << "you lose!!" << endl;
    }
}


void game::update_game()
{
    (*window).clear();//clear window

    (*heli).set_con_fail(Mouse::isButtonPressed(Mouse::Left));//check if mouse is clicked
    (*heli).sprite_move();//move sprite

 
    create_queue_obj();//create new object and insert into queue

    update_queue();//move queue
    
    draw_queue();//draw queue

    (*window).draw((*heli).my_shape());//draw heli
    cout << (*heli).my_shape().getPosition().x << " " << (*heli).my_shape().getPosition().y << endl;//display position of sprite
    (*window).display();//display window

    lose = collision();//update if lost or not
    (*window).setFramerateLimit(60);//frame rate
    //sleep(seconds(0.01));
    
}

//create random height for the two objects that are coming in front of the helicopter
void game::create_random(float* lo1, float* hi2)
{
    int safety_gap=200,num1,num2;
    num1 = rand() % (BOTTOM-safety_gap+1);
    num2 = rand() % (BOTTOM-(num1 +safety_gap)+1)+(num1 +safety_gap);
    *lo1 = num1;
    *hi2 = num2;
}

void game::create_queue_obj()
{
    if (obs_queue.empty() || queue_gap_counter >= queue_gap_max)
    {
        queue_gap_counter = 0;
        //create new obstacle
        obstacles* tmp_obs = new obstacles;
        //lo1=the bottom of the upper_obs,hi2=the top of the lower_obs
        float lo1, hi2;

        create_random(&lo1, &hi2);

        //upper_shape and lower_shape
        RectangleShape shape1(Vector2f(5.f, lo1));
        RectangleShape shape2(Vector2f(5.f, BOTTOM - hi2));
         
        
        RectangleShape* shape1_ptr = new RectangleShape;//added new
        RectangleShape* shape2_ptr = new RectangleShape;

        //set upper_shape
        shape1.setFillColor(Color::Red);
        shape1.setPosition(R_SIDE, TOP);

        //set lower_shape
        shape2.setFillColor(Color::Red);
        shape2.setPosition(R_SIDE, hi2);

        //put shape into pointers
        *shape1_ptr = shape1;
        *shape2_ptr = shape2;

        //add obstacles to struct object
        tmp_obs->upper_obs.set_shape_ptr(shape1_ptr);
        tmp_obs->lower_obs.set_shape_ptr(shape2_ptr);

        //set hitboxes
        tmp_obs->upper_obs.set_hitbox_x(tmp_obs->upper_obs.my_shape().getSize().x);
        tmp_obs->upper_obs.set_hitbox_y(tmp_obs->upper_obs.my_shape().getSize().y);

        tmp_obs->lower_obs.set_hitbox_x(tmp_obs->lower_obs.my_shape().getSize().x);
        tmp_obs->lower_obs.set_hitbox_y(tmp_obs->lower_obs.my_shape().getSize().y);

        //push into queue
        obs_queue.push(tmp_obs);
    }
    else
    {
        queue_gap_counter -= queue_offset.x;
    }
}

void game::update_queue()
{
    //delete front object if after desired pos
    if(obs_queue.front()->lower_obs.my_shape_ptr()->getPosition().x < L_SIDE - 80)//added 80 to delete outside of screen
    {
       
        obs_queue.pop();

    }
    
    queue<obstacles*> tmp_queue=obs_queue;
   
    while (tmp_queue.size()>0)//run through the entire queue to change pos of x
    {

        

        tmp_queue.front()->upper_obs.my_shape_ptr()->move(queue_offset);
        tmp_queue.front()->lower_obs.my_shape_ptr()->move(queue_offset);
  
        tmp_queue.pop();
        
    }
   
    
}

void game::draw_queue()
{
    queue<obstacles*> tmp_queue=obs_queue;
    RectangleShape* tmp ;
   
    while (tmp_queue.size()>0)
    {
     
        //draw upper
       
        tmp = tmp_queue.front()->upper_obs.my_shape_ptr();
        (*window).draw(*tmp);
        //draw lower
        
        tmp = tmp_queue.front()->lower_obs.my_shape_ptr();
        (*window).draw(*tmp);
        tmp_queue.pop();
        
    }
}

bool game::collision()//continue here
{
    queue<obstacles*> tmp_queue = obs_queue;
    float heli_y = (*heli).my_shape().getPosition().y, heli_x = (*heli).my_shape().getPosition().x;
    
    while (tmp_queue.size() > 0)
    {
        //enough to check x for one of the obstacles because x is the same for upper and lower
        if (heli_x == tmp_queue.front()->upper_obs.my_shape_ptr()->getPosition().x)//need to add hitbox like in meteor game
        {
            
          
            if (heli_y >= TOP && heli_y <= tmp_queue.front()->upper_obs.my_shape_ptr()->getSize().y || heli_y <= BOTTOM && heli_y >= tmp_queue.front()->lower_obs.my_shape_ptr()->getPosition().y)
            {
                return true;
            }
        }
        tmp_queue.pop();
    }
    return false;
}


