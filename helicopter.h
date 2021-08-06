

#include "object.h"

class helicopter: public object
{
	public:
		helicopter();
		helicopter(RectangleShape*,Vector2f);
		~helicopter();
		void sprite_move();
		void set_con_fail(bool);
		
		
	private:
        bool continue_fall;


};
	
