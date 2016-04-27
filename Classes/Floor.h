#pragma once

#include "cocos2d.h"

class Floor : public cocos2d::Node{
public:
	Floor();
	~Floor();
	cocos2d::Vector<cocos2d::Rect> getWalls();
	
private:
    cocos2d::Vector<cocos2d::Rect> wallRects;
};