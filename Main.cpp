#include "game.h"






int main()
{   
    //start random time
    srand(time(NULL));
    //window settings
    RenderWindow window(VideoMode(R_SIDE,BOTTOM), "helicopter game");
   
    //helicopter settings
    RectangleShape shape(Vector2f(20.f, 40.f));
    shape.setFillColor(Color::Green);
    shape.setPosition(200, 100);
    Vector2f offset(0, 10.f);

    //create helicopter
    helicopter heli(&shape, offset);

    //create game object
    game gm(&heli,&window);
    
    gm.gameloop();

   

    return 0;
}