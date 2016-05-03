#include "GameScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;


GameScene::GameScene()
{
}


GameScene::~GameScene()
{
}

Scene* GameScene::createScene(){
	auto scene = Scene::create();
	auto layer = GameScene::create();
	scene->addChild(layer);
	return scene;
}

bool GameScene::init(){
	if (!Layer::init())
	{
		return false;
	}
    moveL = moveR = false;
	level = 1;
	floorsNum = 8;
	floorNowNum = 1;
    
//    auto whitelayer = CCLayerColor::create(ccc4(255, 251, 240, 255));
//    this->addChild(whitelayer);
    
	auto rootnode = CSLoader::createNode("Scene/GameScene.csb");
	this->addChild(rootnode);
    rootnode->getChildByName("gamebg")->setGlobalZOrder(-10);
    CCLOG("%f",rootnode->getChildByName("gamebg")->getGlobalZOrder());

	player = Player::Create(rootnode->getChildByName("Player"));

	n_GameUI = rootnode->getChildByName("UILayer");
    
    m_bottomNode = rootnode->getChildByName("BottomBg");

	m_floorsNode = Node::create();

	genFloors(m_floorsNode);
	rootnode->addChild(m_floorsNode);
    
    setAllZOrders();

	auto bt_Left = (Button*)n_GameUI->getChildByName("Bt_Left");
	auto bt_Right = (Button*)n_GameUI->getChildByName("Bt_Right");
	auto bt_Attack = (Button*)n_GameUI->getChildByName("Bt_Attack");
	auto bt_Jump = (Button*)n_GameUI->getChildByName("Bt_Jump");

    bt_Left->addTouchEventListener(CC_CALLBACK_2(GameScene::BtLeftOnTouch, this));
    bt_Right->addTouchEventListener(CC_CALLBACK_2(GameScene::BtRightOnTouch, this));
	bt_Attack->addClickEventListener(CC_CALLBACK_1(GameScene::BtAttackOnClick, this));
	bt_Jump->addClickEventListener(CC_CALLBACK_1(GameScene::BtJumpOnClick, this));

    this->scheduleUpdate();
	return true;
}

void GameScene::update(float delta){
    if (moveL) {
        player->MoveLeft();
    }else if (moveR){
        player->MoveRight();
    }
	checkNowFloor();
	collisionWithFloors();
}

void GameScene::genFloors(Node* node){
    Floor* firstFloor = (Floor*)CSLoader::createNode("Node/FirstFloor.csb");
    firstFloor->setName("Floor_1");
    firstFloor->setPosition(0,135);
    firstFloor->setZOrder(0);
    node->addChild(firstFloor);
	for (int i = 0; i < floorsNum-1; i++)
	{
		Floor* floor = (Floor*)CSLoader::createNode("Node/Floor.csb");
		floor->setName("Floor_"+Value(i+2).asString());
		floor->setPosition(0, 135 + 279*(i+1));
		floor->setZOrder(i+1);
        floor->getChildByName("househole_1")->setGlobalZOrder(-5);
        floor->getChildByName("househole_2")->setGlobalZOrder(-5);
		node->addChild(floor);
	}
}

void GameScene::setAllZOrders()
{
	//人物等Zorder值:10-49
	//Floor的Zorder值：50-99
	//场景的UILayer等：100- 
	player->getNode()->setZOrder(10);

	m_floorsNode->setZOrder(50);

	n_GameUI->setZOrder(100);
}

void GameScene::checkNowFloor(){
	int _floornum = 1;
	for (auto floor : m_floorsNode->getChildren())
	{
		if (player->getNode()->getPositionY() > floor->getPositionY()+floor->getContentSize().height/2)
		{
			int _floornumTem = Value(floor->getName().substr(6, 7)).asInt;
			if (_floornumTem > _floornum) _floornum = _floornumTem;
		}
	}
	floorNowNum = _floornum;
}

void GameScene::collisionWithFloors(){
    auto playerRect = player->getNowNode()->getBoundingBox();
	auto bottomRect = m_bottomNode->getBoundingBox();
	//collison with bottom
	if ( floorNowNum==1 && (player->m_State == Player::State::Idle || player->m_State == Player::State::Walk) )
	{
        if (!playerRect.intersectsRect(bottomRect)) {
			CCLog("jump");
			player->Jumps(true);
        }
		//边界检测
		if ( player->getNode()->getPositionX() - player->getNode()->getContentSize().width/2 < 0 )
		{
			player->getNode()->setPositionX(player->getNode()->getContentSize().width / 2);
		}
		else if (player->getNode()->getPositionX() + player->getNode()->getContentSize().width / 2 > m_bottomNode->getContentSize().width)
		{
			player->getNode()->setPositionX(m_bottomNode->getContentSize().width - player->getNode()->getContentSize().width / 2);
		}
    }
	else if (floorNowNum == 1 && player->m_State == Player::State::JumpDown)
	{
		if (playerRect.intersectsRect(bottomRect)) {
			player->getNode()->setPositionY(m_bottomNode->getPositionY() + m_bottomNode->getContentSize().height / 2 + player->getNode()->getContentSize().height/2);
			player->KeepIdle();
		}
	}
    
	//collision with floors
	for (auto floornode : m_floorsNode->getChildren())
	{
		int checknum = Value(floornode->getName().substr(6, 7)).asInt;
		if (checknum == floorNowNum - 1 || checknum == floorNowNum || checknum == floorNowNum+1)
		{
			for (auto blockSprite : ((Floor*)floornode)->getBlocksSprites())
			{
				if (player->getDropRect().intersectsRect(blockSprite->getBoundingBox())){
					if (player->m_State == Player::State::Idle || player->m_State == Player::State::Walk)
					{

					}
					else if (player->m_State == Player::State::JumpUp)
					{

					}
				}
			}
		}

	}

	//collision with blocks
	
}

void GameScene::BtLeftOnTouch(Ref *pSender, Widget::TouchEventType type)
{
    switch (type) {
        case Widget::TouchEventType::BEGAN:
            if(!moveR) moveL = true;
            break;
        case Widget::TouchEventType::ENDED:
            if(!moveR){
                moveL = false;
                player->StopMove();
            }
            break;
        case Widget::TouchEventType::CANCELED:
            if(!moveR){
                moveL = false;
                player->StopMove();
            }
            break;
        default:
            break;
    }
}

void GameScene::BtRightOnTouch(Ref *pSender, Widget::TouchEventType type)
{
    switch (type) {
        case Widget::TouchEventType::BEGAN:
            if(!moveL) moveR = true;
            break;
        case Widget::TouchEventType::ENDED:
            if(!moveL){
                moveR = false;
                player->StopMove();
            }
            break;
        case Widget::TouchEventType::CANCELED:
            if(!moveL){
                moveR = false;
                player->StopMove();
            }
            break;
        default:
            break;
    }
}

void GameScene::BtAttackOnClick(Ref *pSender){
    player->Attacks();
}

void GameScene::BtJumpOnClick(Ref *pSender){
    player->Jumps(false);
}
