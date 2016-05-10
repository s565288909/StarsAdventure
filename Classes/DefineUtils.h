//
//  DefineUtils.h
//  StarsAdventure
//
//  Created by 史潇 on 16/5/1.
//
//

#ifndef DefineUtils_h
#define DefineUtils_h

#include <cocos2d.h>

USING_NS_CC;

#define JumpUpAction EaseSineOut::create(MoveBy::create(0.7f, Vec2(0, 350)))

#define JumpDownActions MoveBy::create(3,Vec2(0,-3000))

#define DropActions MoveBy::create(2,Vec2(0,-3000))


#endif /* DefineUtils_h */
