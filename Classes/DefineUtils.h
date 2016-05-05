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

#define JumpUpAction EaseSineOut::create(MoveBy::create(0.5f, Vec2(0, 300)))
#define JumpDownAction EaseSineIn::create(MoveBy::create(10, Vec2(0, -5000)))




#endif /* DefineUtils_h */
