#include "Wrapper.h"



Wrapper::Wrapper(std::unique_ptr<Rect> r, std::unique_ptr<Sprite> s, int a)
{
	rect = std::move(r);
	sprite = std::move(s);
	if (a == 0)
	{
		animation = std::unique_ptr<Animation>(new Animation(*sprite));
	}
	else
	{
		animation = std::unique_ptr<Animation>(new Animation(*sprite, a));
	}
}
