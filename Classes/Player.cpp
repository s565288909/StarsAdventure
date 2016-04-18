#include "Player.h"


USING_NS_CC;
using namespace cocostudio;

Player::Player(){}

Player::~Player(){}

Player* Player::Create(Node* node){
	Player *pRet = new(std::nothrow) Player();
	if (pRet) 
	{ 
		pRet->setNode(node);
		pRet->initData();
		pRet->retain();
		return pRet; 
	} 
	else 
	{ 
		delete pRet; 
		pRet = nullptr; 
		return nullptr; 
	} 
}

void Player::initData(){
	isDead = false;
	HP = 100;
	MP = 0;
	auto leftnode = m_Node->getChildByName("Player_Left");
	auto rightnode = m_Node->getChildByName("Player_Right");
	leftnode->setVisible(false);
	rightnode->setVisible(false);
	m_Dir = Dir::Left;
	switch (m_Dir)
	{
	case Enity::Left:
		leftnode->setVisible(true);
		break;
	case Enity::Right:
		rightnode->setVisible(true);
		break;
	}
	m_State = State::Idle;
	arm = (Armature*)m_Node;
	arm->getAnimation()->play("P_Idle", true);
}
