//
//  Live2dXNode.cpp
//  live2d_x
//
//  Created by 血染的玩偶 on 14-4-11.
//  Copyright (c) 2014年 qeeplay.com. All rights reserved.
//

#include "Live2dXNode.h"
#include "Live2dXAnimManager.h"
#include "Live2dXGrid.h"

Live2dXNode::Live2dXNode()
{
    Live2dXGrid* grid = new Live2dXGrid();
    grid->setPosition(ccp(200, 200));
    grid->setScale(1.4);
    grid->setRotation(30);
    grid->setAnchorPoint(ccp(0.5, 0.5));
    this->addChild(grid);
}

Live2dXNode::~Live2dXNode()
{
    CC_SAFE_DELETE(m_touch_animation);
    for (map<string,Live2dXAnimation*>::iterator iter = m_animations.begin();
         iter != m_animations.end(); ++iter)
    {
        delete iter->second;
    }
    for (vector<Live2dXUnitAnimation*>::iterator iter = m_all_unit_animations.begin();
         iter != m_all_unit_animations.end(); ++iter)
    {
        delete *iter;
    }
}

void Live2dXNode::stopAllAnimations()
{
    
}

void Live2dXNode::reset()
{
    
}
