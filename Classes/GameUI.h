#pragma once

#include "cocos2d.h"

class GameUI
{
public:
	GameUI();
	~GameUI();
	void setNode(cocos2d::Node* node);

private:
	cocos2d::Node* m_node;

};

