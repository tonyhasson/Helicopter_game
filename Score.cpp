#include "Score.h"

Score::Score()
{
	max_score = 0;
	my_score = 0;
	offset = 0;
}

Score::~Score()
{

}

void Score::set_my_score(int x)
{
	my_score = x;
}

void Score::set_max_score(int x)
{
	max_score = x;
}


void Score::set_offset(int x)
{
	offset = x;
}

int Score::get_offset()
{
	return offset;
}

int Score::get_my_score()
{
	return my_score;
}

int Score::get_max_score()
{
	return max_score;
}

void Score::increase_score(int x)
{
	my_score += x;
}

void Score::check_max()
{
	if (my_score > max_score)
	{
		max_score = my_score;
	}
}
