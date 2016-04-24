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
    moveSpeed = 3;
    jumpSpeed = 3;
    m_action = CSLoader::createTimeline("Node/PlayerNode.csb");
    m_Node->runAction(m_action);
	leftNode = m_Node->getChildByName("Player_Left");
	rightNode = m_Node->getChildByName("Player_Right");
	leftNode->setVisible(false);
	rightNode->setVisible(false);
	m_Dir = Dir::Left;
	switch (m_Dir)
	{
	case Enity::Left:
		leftNode->setVisible(true);
		break;
	case Enity::Right:
		rightNode->setVisible(true);
		break;
	}
    m_action->play("P_Idle", true);
	m_State = State::Idle;
}

void Player::MoveLeft()
{
    if (m_State==State::Idle) {
        if (m_Dir != Dir::Left) {
            m_Dir = Dir::Left;
            leftNode->setVisible(true);
            rightNode->setVisible(false);
        }
        m_action->play("P_Walk", true);
        m_State = State::Walk;
    }
    m_Node->setPositionX(m_Node->getPositionX()-moveSpeed);
}

void Player::MoveRight()
{
    if (m_State==State::Idle) {
        if (m_Dir != Dir::Right) {
            m_Dir = Dir::Right;
            leftNode->setVisible(false);
            rightNode->setVisible(true);
        }
        m_action->play("P_Walk", true);
        m_State = State::Walk;
    }
    m_Node->setPositionX(m_Node->getPositionX()+moveSpeed);
}

void Player::StopMove(){
    m_action->play("P_Idle", true);
    m_State = State::Idle;
}

void Player::Jump(){
    if (m_State!=State::Jump && m_State!=State::Attack) {
        m_action->play("P_Jump", false);
        m_action->setAnimationEndCallFunc("P_Jump", [&]{
            m_action->play("P_Idle", true);
            m_State = State::Idle;
        });
    }
}

void Player::Attack()
{
    if (m_State!=State::Jump) {
        m_action->play("P_Attack", false);
        
        m_action->setAnimationEndCallFunc("P_Attack", [&]{
            m_action->play("P_Idle", true);
            m_State = State::Idle;
        });
        m_State = State::Jump;
    }

}
