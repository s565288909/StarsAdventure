#include "Floor.h"

USING_NS_CC;

Floor::Floor(){}

Floor::~Floor(){}

Vector<Rect> Floor::getWalls(){
    Vector<Rect> vec;
    vec.pushBack(this->getChildByName("wall_1")->getBoundingBox());
    vec.pushBack(this->getChildByName("wall_2")->getBoundingBox());
    return vec;
}