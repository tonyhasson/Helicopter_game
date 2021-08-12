#include "object.h"//include for all in the includes in object.h

class Score
{
public:
	Score();
	~Score();
	void set_my_score(int);
	void set_max_score(int);
	void increase_score(int);
	int get_my_score();
	int get_max_score();
	int get_offset();
	void set_offset(int);
	void check_max();


private:
	int my_score;
	int max_score;
	int offset;
};


