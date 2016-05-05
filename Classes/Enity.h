#pragma once

#include "cocos2d.h"
#include <cocostudio/CocoStudio.h>

class Enity : public cocos2d::Node
{
public:
	Enity();
	~Enity();
	cocos2d::Node* getNowNode();
	void setTimeLineAction(cocostudio::timeline::ActionTimeline* action);
	
protected:
	int HP;
	int MP;
	bool isDead;
	cocos2d::Node* leftNode;
	cocos2d::Node* rightNode;
	enum Direction
	{
		Left,
		Right
	} m_Dir;
};