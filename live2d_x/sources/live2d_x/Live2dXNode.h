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
using namespace cocos2d;

class Live2dXNode:public CCNode
{
public:
    Live2dXNode();
    ~Live2dXNode();
public:
    void visit();
public:
    void runAnimation(const string& anim_name);
private:
    vector<Live2dXGrid*> m_all_grid;
    map<string,int> m_grid_for_key;
};

#endif /* defined(__live2d_x__Live2dXNode__) */