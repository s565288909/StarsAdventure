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
    blockCollusion = false;
    cameraMove = false;
    level = 1;
    floorsNum = 8;
    floorNowNum = 1;
    
    ui_cam = Camera::create();
    ui_cam->setCameraFlag(CameraFlag::USER1);
    
    //    auto whitelayer = CCLayerColor::create(ccc4(255, 251, 240, 255));
    //    this->addChild(whitelayer);
    
    auto rootnode = CSLoader::createNode("Scene/GameScene.csb");
    this->addChild(rootnode);
    rootnode->getChildByName("gamebg")->setGlobalZOrder(-10);
    
    player = Player::Create(CSLoader::createNode("Node/PlayerNode.csb"));
    //player->initData();
    rootnode->addChild(player->getNode());
    
    auto monster1 = rootnode->getChildByName("Alien_1");
    monster1->getChildByName("Alien_Left")->setVisible(false);
    monster1->getChildByName("Alien_Right")->setVisible(true);
    auto _action1 = CSLoader::createTimeline("Node/Alien.csb");
    monster1->runAction(_action1);
    
    auto monster2 = rootnode->getChildByName("Alien_2");
    monster2->getChildByName("Alien_Left")->setVisible(true);
    monster2->getChildByName("Alien_Right")->setVisible(false);
//    monster2->runAction(_action1);
    
    n_GameUI = rootnode->getChildByName("UILayer");
    n_GameUI->setCameraMask(2);
    rootnode->addChild(ui_cam);
    
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
    cameraMoveTo();
    CCLOG("%f,%f,%f",Camera::getDefaultCamera()->getPositionX(),Camera::getDefaultCamera()->getPositionY(),Camera::getDefaultCamera()->getPositionZ());
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
    //player->setZOrder(10);
    
    m_floorsNode->setZOrder(50);
    
    n_GameUI->setZOrder(100);
}

void GameScene::checkNowFloor(){
    auto _floornum = 1;
    for (auto floor : m_floorsNode->getChildren())
    {
        if (player->getDropRect().getMidY() > floor->getBoundingBox().getMaxY())
        {
            int _floornumTem = Value(floor->getName().substr(6, 7)).asInt();
            if (_floornumTem > _floornum) _floornum = _floornumTem;
        }
    }
    if (floorNowNum!=_floornum)
    {
        floorNowNum = _floornum;
        cameraMove = true;
        CCLOG("floorNowNum:%d", floorNowNum);
    }
}

void GameScene::collisionWithFloors(){
    //auto playerRect = player->getNowNode()->getBoundingBox();
    auto playerRect = Rect(player->getNode()->convertToWorldSpace(player->getNowNode()->getBoundingBox().origin), player->getNowNode()->getBoundingBox().size);
    auto bottomRect = m_bottomNode->getBoundingBox();
    //collison with bottom
    if (floorNowNum == 1)
    {
        if (player->m_State != Player::State::JumpDown && player->m_State != Player::State::JumpUp && !playerRect.intersectsRect(bottomRect)) {
            CCLOG("not collision with the bottomrect,jump down");
            player->Jumps(false,true);
        }
        //左右边界检测
        if ( player->getNode()->getPositionX() - playerRect.size.width/2 < 0 )
        {
            player->getNode()->setPositionX(playerRect.size.width / 2);
        }
        else if (player->getNode()->getPositionX() + playerRect.size.width / 2 > bottomRect.size.width)
        {
            player->getNode()->setPositionX(bottomRect.size.width - playerRect.size.width / 2);
        }
        //下边界检测
        if (playerRect.intersectsRect(bottomRect)) {
            //向上跳跃时不检测
            if (player->m_State != Player::State::JumpUp) player->getNode()->setPositionY(bottomRect.getMidY() + bottomRect.size.height / 2 + playerRect.size.height / 2);
            if (player->m_State == Player::State::JumpDown){
                CCLOG("collision bottom");
                player->KeepIdle();
                player->getNode()->setPositionY(bottomRect.getMidY() + bottomRect.size.height / 2 + playerRect.size.height / 2 - 1);
            }
        }
    }
    
    //collision with floors
    for (auto floornode : m_floorsNode->getChildren())
    {
        int checknum = Value(floornode->getName().substr(6, 7)).asInt();
        if (checknum == floorNowNum - 1 || checknum == floorNowNum)
        {
            for (auto blockSprite : floornode->getChildren())
            {
                if (blockSprite->getName().find("block_") != std::string::npos || blockSprite->getName().find("board_") != std::string::npos){
                    //				if (!blockSprite->isVisible()) continue;
                    auto blockRectWorld = Rect(floornode->convertToWorldSpace(blockSprite->getBoundingBox().origin).x, floornode->convertToWorldSpace(blockSprite->getBoundingBox().origin).y, blockSprite->getBoundingBox().size.width, blockSprite->getBoundingBox().size.height);
                    
                    if (player->getDropRect().intersectsRect(blockRectWorld)){
                        blockCollusion = true;
                        //collision with downfloor
                        if ( floorNowNum>1 && (player->m_State == Player::State::Idle || player->m_State == Player::State::Walk))
                        {
                            player->getNode()->setPositionY(blockRectWorld.getMaxY() + player->getDropRect().size.height/2 - 4);
                            
                        }
                        else if (player->m_State == Player::State::JumpUp || player->m_State == Player::State::JumpDown)
                        {
                            if (player->getDropRect().intersectsRect(blockRectWorld)){
                                float rectW = std::min(player->getDropRect().getMaxX(), blockRectWorld.getMaxX()) - std::max(player->getDropRect().getMinX(), blockRectWorld.getMinX());
                                float rectH = std::min(player->getDropRect().getMaxY(), blockRectWorld.getMaxY()) - std::max(player->getDropRect().getMinY(), blockRectWorld.getMinY());
                                CCLOG("W:%f,H:%f",rectW,rectH);
                                if (rectW >= rectH)
                                {
                                    if (player->m_State == Player::State::JumpUp)
                                    {
                                        if (checknum == floorNowNum) {
                                        if (blockSprite->getName().find("block_") != std::string::npos) {
                                            floornode->removeChildByName(blockSprite->getName());
                                        }
                                        player->m_State = Player::State::Idle;
                                        player->getNode()->stopActionByTag(1);
                                        player->Jumps(true, false);
                                        }
                                    }
                                    else if (player->m_State == Player::State::JumpDown )
                                    {
                                        if(checknum == floorNowNum - 1){
                                            CCLOG("jumpdown");
                                            player->getNode()->setPositionY(blockRectWorld.getMaxY() + playerRect.size.height / 2 - 10);
                                            player->KeepIdle();
                                        }
                                    }
                                }
                                else
                                {
                                    //left
                                    if (playerRect.getMaxX() <= blockRectWorld.getMidX())
                                    {
                                        player->getNode()->setPositionX(blockRectWorld.getMinX() - player->getDropRect().size.width / 2);
                                    }
                                    //right
                                    else if (playerRect.getMinX() > blockRectWorld.getMidX())
                                    {
                                        player->getNode()->setPositionX(blockRectWorld.getMaxX() + player->getDropRect().size.width / 2);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    //collision 
    if ( floorNowNum>1 && !blockCollusion && player->m_State == Player::State::Walk) {
        player->Jumps(false, true);
    }
    blockCollusion = false;
}

void GameScene::cameraMoveTo(){
    if (cameraMove) {
        cameraMove = false;
        Camera::getDefaultCamera()->runAction(EaseSineOut::create(MoveTo::create(0.5f, Vec3(Camera::getDefaultCamera()->getPositionX(),320+(floorNowNum-1)*279,Camera::getDefaultCamera()->getPositionZ()))));
    }
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
    player->Jumps(false,false);
}
