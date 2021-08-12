#include "Button.h"

Button::Button()
{

}

Button::Button(string t, string f, RectangleShape* r, Vector2f v):object(r,v)
{
    if (!fnt.loadFromFile(f))//load font
    {
        cout << "error loading font!" << endl;
    }
    txt = new Text;
    txt->setFont(fnt);
    txt->setString(t);
    txt->setPosition(r->getPosition());
    on_button = false;
}

Button::~Button()
{
    delete txt;
}

Text Button::get_text()
{
    return *txt;
}

Text* Button::get_text_ptr()
{
    return txt;
}

void Button::set_on_button(bool tf)
{
    on_button = tf;
}

bool Button::get_on_button()
{
    return on_button;
}

