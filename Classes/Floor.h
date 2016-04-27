#pragma once

#include "cocos2d.h"

class Floor : public cocos2d::Node{
public:
	Floor();
	~Floor();
	getWalls();
	
private:
	cocos2d::Vector<Rect> rects;
};