#include "game.h"


game::game()
{
   
}

game::game(helicopter* h, RenderWindow* w)
{
    lose = false;
    score_obj.set_offset(1);//set how much to increase score each iteration of update game
	heli = h;
	window = w;
    //init queue_offset 
    Vector2f tmp(-10, 0);
    queue_offset = tmp;
    queue_gap_counter = 0;
    queue_gap_max = 575;
    safety_gap = 200;

    if (!font.loadFromFile("arial.ttf"))//load font
    {
        cout << "error loading font!" << endl;
    }
   
}

game::~game()
{
    //need to free queue objects
}


void game::menu()
{

    //set up shape for button
    RectangleShape shape1(Vector2f(160, 40));


    RectangleShape* shape1_ptr = new RectangleShape;

    
    shape1.setFillColor(Color::Green);
    shape1.setPosition(R_SIDE/2.5, BOTTOM/6+100);
    Vector2f nada(0, 0);
   
    *shape1_ptr = shape1;

    Button btn("Start Game!", "arial.ttf", shape1_ptr, nada);
    //end button setup

    //Text text;//text for hello player!
    Text score_text;//text for score;
    //Font font;//font for text

    bool start_game = false;

    //if (!font.loadFromFile("arial.ttf"))//load font
    //{
    //    cout << "error loading font!" << endl;
    //}
    while (!start_game)
    {
        ////for text

        // select the font
        text.setFont(font); // font is a sf::Font

        // set the string to display
        text.setString("Hello Player!");

        // set the character size
        text.setCharacterSize(36); // in pixels, not points!

        // set the color
        text.setFillColor(Color::Red);

        // set the text style
        text.setStyle(Text::Bold);

        //set position of text
        text.setPosition(R_SIDE / 2.5, BOTTOM / 6);

        ////end text



  

        ////for score_text

        // select the font
        score_text.setFont(font); // font is a sf::Font

        // set the string to display
        score_text.setString("this round:" + to_string(score_obj.get_my_score())+"\nmax score:"+ to_string(score_obj.get_max_score()));

        // set the character size
        score_text.setCharacterSize(36); // in pixels, not points!

        // set the color
        score_text.setFillColor(Color::Yellow);

        // set the text style
        score_text.setStyle(Text::Bold);

        //set position of text
        score_text.setPosition(R_SIDE - 400, TOP + 200);

        ////end score_text

        //game button

        btn.get_text_ptr()->setCharacterSize(24);
        btn.get_text_ptr()->setFillColor(Color::Blue);
        btn.get_text_ptr()->setStyle(Text::Bold);


        //event handler
        Event event;
        while ((*window).pollEvent(event))
        {
            switch (event.type)
            {
            case Event::Closed://if clicked close window
                (*window).close();
                break;
            }

            //check if mouse is in button zone
            if (Mouse::getPosition(*window).x >= btn.my_shape().getPosition().x && Mouse::getPosition(*window).x <= btn.my_shape().getPosition().x + btn.get_hitbox_x())
            {

                if (Mouse::getPosition(*window).y >= btn.my_shape().getPosition().y && Mouse::getPosition(*window).y <= btn.my_shape().getPosition().y + btn.get_hitbox_y())
                {
                    if (btn.get_on_button() == false)//change color if you're on the button
                    {
                        btn.my_shape_ptr()->setFillColor(Color::Red);
                        btn.set_on_button(true);
                    }
                    if (Mouse::isButtonPressed(Mouse::Left))//check if clicked on button
                    {
                        start_game = true;
                    }
                   
                }
                else//change back to green color if not on button
                {
                    btn.my_shape_ptr()->setFillColor(Color::Green);
                    btn.set_on_button(false);
                }
               
            }
            else//change back to green color if not on button
            {
                btn.my_shape_ptr()->setFillColor(Color::Green);
                btn.set_on_button(false);
            }
          
        }
       



        (*window).clear();
        (*window).draw(text);
        (*window).draw(score_text);
        (*window).draw(btn.my_shape());
        (*window).draw(btn.get_text());
        (*window).display();
    }
}

void game::gameloop()
{
   
    reset_game();//reset game
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
        increase_difficulty();


    }
    if (lose)
    {
        cout << "you lose!!" << endl;
        score_obj.check_max();//check if passed max score
       // cout <<"speed is: "<< queue_offset.x << endl;
    }
}

void game::reset_game()
{

    lose = false;//reset lose
    score_obj.set_my_score(0);//reset score
    (*window).clear();//clear window
    obs_queue = queue<obstacles*>();//clear obs_queue
    (*heli).my_shape_ptr()->setPosition(200, 100);//reset position of helicopter

    //reset queue variables
    Vector2f tmp(-10, 0);
    queue_offset = tmp;
    queue_gap_counter = 0;
    queue_gap_max = 575;
    safety_gap = 200;
}

void game::update_game()
{
    (*window).clear();//clear window

    (*heli).set_con_fail(Mouse::isButtonPressed(Mouse::Left));//check if mouse is clicked
    (*heli).sprite_move();//move sprite

 
    create_queue_obj();//create new object and insert into queue

    update_queue();//move queue
    
    draw_queue();//draw queue

    score_obj.increase_score(score_obj.get_offset());//increase score

    (*window).draw((*heli).my_shape());//draw heli
   // cout << (*heli).my_shape().getPosition().x << " " << (*heli).my_shape().getPosition().y << endl;//display position of sprite
    //cout << "score:" << score_obj.get_my_score() << endl;//print score


    //start text

    text.setFont(font); // font is a sf::Font

       // set the string to display
    text.setString("score:" + to_string(score_obj.get_my_score()));

    // set the character size
    text.setCharacterSize(36); // in pixels, not points!

    // set the color
    text.setFillColor(Color::Yellow);

    // set the text style
    text.setStyle(Text::Bold);

    //set position of text
    text.setPosition(R_SIDE - 300, TOP);

    //end text

    (*window).draw(text);//draw current score


    (*window).display();//display window

    lose = collision();//update if lost or not
    (*window).setFramerateLimit(60);//frame rate
    //sleep(seconds(0.01));
    
}

//create random height for the two objects that are coming in front of the helicopter
void game::create_random(float* lo1, float* hi2)
{

    int num1,num2;
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
    float tmp_obs_x, tmp_obs_upper_y, tmp_obs_lower_y, tmp_obs_hitbox_x, tmp_obs_upper_hitbox_y, tmp_obs_lower_hitbox_y;
    RectangleShape* tmp_upper_ptr,* tmp_lower_ptr;

    //if heli touches border of screen 
    if (heli_y == TOP || heli_y + (*heli).get_hitbox_y() == BOTTOM)
    {
        return true;
    }
    
    //run through queue to check if there is collision
    while (tmp_queue.size() > 0)
    {
       
            //pointer for upper and lower obstacles
            tmp_upper_ptr = tmp_queue.front()->upper_obs.my_shape_ptr();
            tmp_lower_ptr = tmp_queue.front()->lower_obs.my_shape_ptr();

            //x position
            tmp_obs_x = tmp_upper_ptr->getPosition().x;//x is same for upper and lower

            //y position
            tmp_obs_upper_y = tmp_upper_ptr->getPosition().y;
            tmp_obs_lower_y = tmp_lower_ptr->getPosition().y;

            //hitbox x
            tmp_obs_hitbox_x = tmp_queue.front()->upper_obs.get_hitbox_x();

            //hitbox upper
            tmp_obs_upper_hitbox_y = tmp_queue.front()->upper_obs.get_hitbox_y();

            //hitbox lower
            tmp_obs_lower_hitbox_y = tmp_queue.front()->lower_obs.get_hitbox_y();




            //enough to check x for one of the obstacles because x is the same for upper and lower
            if (heli_x >= tmp_obs_x && heli_x <= tmp_obs_x + tmp_obs_hitbox_x || heli_x + (*heli).get_hitbox_x() >= tmp_obs_x && heli_x+(*heli).get_hitbox_x() <= tmp_obs_x + tmp_obs_hitbox_x)
            {
                //check collision for top of heli
                if (heli_y >= TOP && heli_y <= tmp_obs_upper_hitbox_y || heli_y <= BOTTOM && heli_y >= tmp_obs_lower_y)
                {
                    return true;
                }
                //check collision for bot of heli
                if (heli_y + (*heli).get_hitbox_y() >= TOP && heli_y + (*heli).get_hitbox_y() <= tmp_obs_upper_hitbox_y || heli_y + (*heli).get_hitbox_y() <= BOTTOM && heli_y + (*heli).get_hitbox_y() >= tmp_obs_lower_y)
                {
                    return true;
                }
            }
            tmp_queue.pop();
        
    }
    return false;
}

void game::increase_difficulty()//need to adjust and have a limit for decreasing,and need to make same thing for gap between the upper and lower obstacle
{
    if (score_obj.get_my_score() % 100 == 0&& queue_gap_max>500)//make gaps between obstacles tinier(width wise)
    {
        queue_gap_max -= 1;
        cout << "gap:" << queue_gap_max << endl;
    }
    if (score_obj.get_my_score() % 100 == 0&&queue_offset.x>-15)//increase "speed" of the game
    {
        queue_offset.x -= 0.25;
        cout << "speed:" << queue_offset.x << endl;
    }
    if (score_obj.get_my_score() % 100 == 0&& safety_gap>180)//make gaps between obstacles tinier(height wise)
    {
        safety_gap -= 1;
        cout << "safety_gap:" << safety_gap << endl;
    }

}


