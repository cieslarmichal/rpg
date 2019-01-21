#include "Wrapper.h"


Wrapper::Wrapper(std::unique_ptr<Rect> r, std::unique_ptr<Sprite> s, int a)
{
	rect = std::move(r);
	sprite = std::move(s);
	if (a == 0)
	{
		animation = std::make_unique<Animation>(Animation(*sprite));
	}
	else
	{
		animation = std::make_unique<Animation>(Animation(*sprite, a));
	}
}


