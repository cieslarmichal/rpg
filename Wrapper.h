#pragma once
#include "Rect.h"
#include "Sprite.h"
#include "Animation.h"
#include <memory>
#include "TimeHandler.h"

class Wrapper
{
public:
	Wrapper(std::unique_ptr<Rect>, std::unique_ptr<Sprite>, int a=0);
	std::unique_ptr<Rect> rect;
	std::unique_ptr<Sprite> sprite;
	std::unique_ptr<Animation> animation;
	TimeHandler timing;
};
