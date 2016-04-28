#pragma once

#include "cocos2d.h"

class Floor : public cocos2d::Node{
public:
	Floor();
	~Floor();
	cocos2d::Vector<cocos2d::Rect> getWallsRects();
	cocos2d::Vector<cocos2d::Sprite*> getBlocksSprites();
private:
    cocos2d::Vector<cocos2d::Rect> wallRects;
};