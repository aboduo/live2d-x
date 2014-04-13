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

Live2dXGrid::Live2dXGrid()
:m_bind_unit(NULL)
{
    m_bind_unit = new Live2dXUnit();
    setContentSize(CCSizeMake(122, 128));
}

Live2dXGrid::~Live2dXGrid()
{
    if(m_bind_unit)
        delete m_bind_unit;
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