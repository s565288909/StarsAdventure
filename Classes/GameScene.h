#pragma once

#include "cocos2d.h"
#include "Player.h"
#include "Floor.h"

class GameScene : public cocos2d::Layer
{
public:
	GameScene();
	~GameScene();

	static cocos2d::Scene* createScene();

	virtual bool init();
    
    virtual void update(float delta);

	CREATE_FUNC(GameScene);

private:
	cocos2d::Node* n_GameUI;
	Player* player;
  
    bool moveL,moveR;

	int level;
	int floorsNum;

	void genFloors(cocos2d::Node* node);
	void setAllZOrders();

    void BtLeftOnTouch(Ref *pSender,cocos2d::ui::Widget::TouchEventType type);
    void BtRightOnTouch(Ref *pSender,cocos2d::ui::Widget::TouchEventType type);
	void BtAttackOnClick(Ref *pSender);
	void BtJumpOnClick(Ref *pSender);
};

