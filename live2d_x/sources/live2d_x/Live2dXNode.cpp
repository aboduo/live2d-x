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
    grid->setPosition(ccp(400, 400));
//    grid->setScale(1.4);
//    grid->setRotation(30);
    grid->setAnchorPoint(ccp(0.5, 0.5));
    this->addChild(grid);
}

Live2dXNode::~Live2dXNode()
{
    for (vector<CCTexture2D*>::iterator iter = m_textures.begin();
         iter != m_textures.end(); ++iter)
    {
        (*iter)->release();
    }
//    CC_SAFE_DELETE(m_touch_animation);
//    for (map<string,Live2dXAnimation*>::iterator iter = m_animations.begin();
//         iter != m_animations.end(); ++iter)
//    {
//        delete iter->second;
//    }
//    for (vector<Live2dXUnitAnimation*>::iterator iter = m_all_unit_animations.begin();
//         iter != m_all_unit_animations.end(); ++iter)
//    {
//        delete *iter;
//    }
}

bool Live2dXNode::initWithFile(const char* path)
{
    string fullpath = CCFileUtils::sharedFileUtils()->fullPathForFilename(path);
    string::size_type pos = fullpath.rfind("/");
    m_config_path = fullpath.substr(0,pos+1);
    CCDictionary* config = CCDictionary::createWithContentsOfFile(fullpath.c_str());
    return initWithConfig(config);
}

bool Live2dXNode::initWithConfig(CCDictionary* config)
{
    typeAt(CCDictionary, property, config);
    typeAt(CCArray, texture, property);
    for (int i = 0 ; i < texture->count(); ++i)
    {
        string path = ((CCString*)texture->objectAtIndex(i))->m_sString;
        path = m_config_path + path;
        CCTexture2D* tex = CCTextureCache::sharedTextureCache()->addImage(path.c_str());
        tex->retain();
        m_textures.push_back(tex);
    }
    typeAt(CCArray,grid_tree,config);
    for (int i = 0; i < grid_tree->count(); ++i)
    {
        Live2dXGrid* grid = Live2dXGrid::create((CCDictionary*)grid_tree->objectAtIndex(i),this);
        if (grid)
        {
            this->addChild(grid);
        }
    }
    return true;
}

void Live2dXNode::stopAllAnimations()
{
    
}

void Live2dXNode::reset()
{
    
}
