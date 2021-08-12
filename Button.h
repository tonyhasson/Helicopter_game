#include "object.h"

class Button:public object
{
public:
	Button();
	Button(string,string,RectangleShape*, Vector2f);
	~Button();

	Text get_text();
	Text* get_text_ptr();
	void set_on_button(bool);
	bool get_on_button();
	

private:
	Text* txt;//text
	Font fnt;//font
	bool on_button;



};

