//
//  Live2dXGrid.cpp
//  live2d_x
//
//  Created by 血染的玩偶 on 14-4-11.
//  Copyright (c) 2014年 qeeplay.com. All rights reserved.
//

#include "Live2dXGrid.h"
#include "Live2dXNode.h"
#include "Live2dXUnit.h"

Live2dXGrid* Live2dXGrid::create(CCDictionary* config,Live2dXNode* orginNode)
{
    Live2dXGrid* pRet = new Live2dXGrid();
    if (pRet && pRet->initWithConfig(config,orginNode))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return pRet;
}

Live2dXGrid::Live2dXGrid()
:m_bind_unit(NULL)
{
    m_bind_unit = new Live2dXUnit();
    setContentSize(CCSizeMake(400, 400));
}

Live2dXGrid::~Live2dXGrid()
{
    if(m_bind_unit)
        delete m_bind_unit;
}

bool Live2dXGrid::initWithConfig(CCDictionary* config,Live2dXNode* orginNode)
{
    orginNode->m_all_grid[config->valueForKey("name")->m_sString] = this;
    typeAt(CCDictionary, unit, config);
    m_bind_unit = new Live2dXUnit();
    m_bind_unit->initWithConfig(unit,orginNode);
    typeAt(CCDictionary, property, config);
    m_width_count = property->valueForKey("width_count")->intValue();
    m_height_count = property->valueForKey("height_count")->intValue();
    float x = property->valueForKey("x")->floatValue();
    float y = property->valueForKey("y")->floatValue();
    this->setPosition(x,y);
    typeAt(CCArray, children, config);
    for (int i = 0; i < children->count(); ++i)
    {
        CCDictionary* obj = (CCDictionary*)children->objectAtIndex(i);
        Live2dXGrid* grid = Live2dXGrid::create(obj, orginNode);
        this->addChild(grid);
    }
    return true;
}

void Live2dXGrid::draw()
{
    if(m_bind_unit)
    {
        
        CCGLProgram* program = CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColor);
        program->use();
        program->setUniformsForBuiltins();
        
        ccGLBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
        
        m_bind_unit->draw();
    }
}