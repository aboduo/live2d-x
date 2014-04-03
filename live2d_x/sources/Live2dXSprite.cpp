//
//  Live2dXSprite.cpp
//  live2d_x
//
//  Created by 血染的玩偶 on 14-4-1.
//  Copyright (c) 2014年 qeeplay.com. All rights reserved.
//

#include "Live2dXSprite.h"

Live2dXSprite::Live2dXSprite()
{

}

Live2dXSprite::~Live2dXSprite()
{

}

Live2dXSprite* Live2dXSprite::create(const char* pictruePath, const char* configPath)
{
    Live2dXSprite *pobSprite = new Live2dXSprite();
    if (pobSprite && pobSprite->initWithFile(pictruePath,configPath))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

bool Live2dXSprite::initWithFile(const char* pictruePath, const char* configPath)
{
    CCDictionary* dict = CCDictionary::createWithContentsOfFile(configPath);
    return initWithConfig(pictruePath, dict);
}

bool Live2dXSprite::initWithConfig(const char* pictruePath,CCDictionary* config)
{
    convertDictToConfig(config);
    return cocos2d::CCSprite::initWithFile(pictruePath);
}

void Live2dXSprite::draw()
{
    CC_PROFILER_START_CATEGORY(kCCProfilerCategorySprite, "CCSprite - draw");
    
    CCAssert(!m_pobBatchNode, "If CCSprite is being rendered by CCSpriteBatchNode, CCSprite#draw SHOULD NOT be called");
    
    CC_NODE_DRAW_SETUP();
    
    ccGLBlendFunc( m_sBlendFunc.src, m_sBlendFunc.dst );
    
    ccGLBindTexture2D( m_pobTexture->getName() );
    ccGLEnableVertexAttribs( kCCVertexAttribFlag_PosColorTex );
    
#define Live2dX_Vertex_Size sizeof(Live2dX_Vertex)
#define Live2dX_UV_Size sizeof(Live2dX_UV)
#define Live2dX_Color_Size sizeof(Live2dX_Color)
    
    // vertex
    glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, Live2dX_Vertex_Size, (void*)m_nowVertex.data());
    
    // texCoods
    glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, Live2dX_UV_Size, (void*)m_orginUV.data());
    
    // color
//    diff = offsetof( ccV3F_C4B_T2F, colors);
    glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, Live2dX_Color_Size, (void*)m_orginColor.data());
    
    
    glDrawArrays(GL_TRIANGLES, 0, (int)m_nowVertex.size());
    
    CHECK_GL_ERROR_DEBUG();
    
    CC_INCREMENT_GL_DRAWS(1);
    
    CC_PROFILER_STOP_CATEGORY(kCCProfilerCategorySprite, "CCSprite - draw");
}

void Live2dXSprite::convertDictToConfig(CCDictionary* config)
{
    CCDictionary* property = (CCDictionary*)config->objectForKey("property");
    m_baseSize.width = property->valueForKey("width")->intValue();
    m_baseSize.height = property->valueForKey("height")->intValue();
    
    CCDictionary* unit_list = (CCDictionary*)config->objectForKey("unit_list");
    CCArray* unit_names = unit_list->allKeys();
    for (int i = 0; i < unit_names->count(); ++i)
    {
        CCString* unit_name = (CCString*)unit_names->objectAtIndex(i);
        CCDictionary* unit = (CCDictionary*)unit_list->objectForKey(unit_name->m_sString);
        CCArray* point = (CCArray*)unit->objectForKey("point");
        
        CCArray* triangle = (CCArray*)unit->objectForKey("triangle");
        Live2dX_TriangleList& triangle_list = m_all_units[unit_name->m_sString];
        for (int k = 0; k < triangle->count(); ++k)
        {
            CCArray* triangle_one = (CCArray*)triangle->objectAtIndex(k);
            int point_index[3];
            point_index[0] = intAtArray(0, triangle_one);
            point_index[1] = intAtArray(1, triangle_one);
            point_index[2] = intAtArray(2, triangle_one);
            Live2dX_Triangle config;
            
            for (int m = 0; m < 3; ++m)
            {
                CCArray* origin_points = (CCArray*)point->objectAtIndex(point_index[m]);
                Live2dX_UV uv = {floatAtArray(0,origin_points),floatAtArray(1,origin_points)};
                Live2dX_Vertex vertex = {floatAtArray(2,origin_points),m_baseSize.height-floatAtArray(3,origin_points),0};
                int point_id = (int)m_orginUV.size();
                m_orginUV.push_back(uv);
                m_orginVertex.push_back(vertex);
                m_nowVertex.push_back(vertex);
                m_orginColor.push_back(ccc4(0xff, 0xff,0xff, 0xff));
                config.point[m] = point_id;
            }
            triangle_list.push_back(config);
        }
        CCDictionary* animation = (CCDictionary*)unit->objectForKey("animation");
        if(animation)
        {
            
        }
    }
    
}
