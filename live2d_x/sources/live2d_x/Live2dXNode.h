//
//  Live2dXNode.h
//  live2d_x
//
//  Created by 血染的玩偶 on 14-4-11.
//  Copyright (c) 2014年 qeeplay.com. All rights reserved.
//

#ifndef __live2d_x__Live2dXNode__
#define __live2d_x__Live2dXNode__

#include <iostream>
#include <map>
#include <string>
using namespace std;

#include "cocos2d.h"
#include "Live2dXGrid.h"
#include "Live2dXUnitAnimation.h"
#include "Live2dXAnimation.h"
#include "Live2dXTouchAnimation.h"
using namespace cocos2d;

class Live2dXUnit;
class Live2dXNode:public CCNode
{
public:
    Live2dXNode();
    ~Live2dXNode();
    bool initWithFile(const char* path);
    bool initWithConfig(CCDictionary* config);
    void stopAllAnimations();
    void reset();
private:
    map<string,Live2dXGrid*> m_all_grid;
    Live2dXTouchAnimation* m_touch_animation;
    map<string,Live2dXAnimation*> m_animations;
    vector<CCTexture2D*> m_textures;
    string m_config_path;
    
    friend class Live2dXGrid;
    friend class Live2dXUnit;
};

#endif /* defined(__live2d_x__Live2dXNode__) */
